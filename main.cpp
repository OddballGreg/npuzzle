#include "npuzzle.h"

using namespace std;

Node *g_sol; // Solution
vector<Node *> g_osets; // Open Sets
vector<Node *> g_csets; // Closed Sets
vector<string> g_checked;
int g_idc = 0; // ID counter
int g_size = 3;
int g_hstc = -1;
int g_algo = -1;
int g_verb = -1;
int g_penilty = 0;

int main(int ac, char **argv) {

    if (argv[1] && file_exists(argv[1]) == true) {
        g_osets.push_back(new Node (g_idc++, -1, parse(argv[1]), g_size, 0, ""));
    } else {
        cout << "Invalid file or no puzzle given, automatically generating random 3x3 puzzle\n";
        g_size = 3;
        string puz = genPuzzle(g_size);
        g_osets.push_back(new Node (g_idc++, -1, puz, g_size, 0, ""));
        cout << "generated puzel" << endl;
        g_osets.at(0)->printGrid();
    }
    if (isSolvable(g_osets.at(0)->getGrid())) {
        cout << "can be solved\n";
        int lineIn;
        cout << "there are " << penilty(g_osets.at(0)->getGrid()) << " penilty in the puzzel"<< endl;
        g_sol = new Node(-1, -1, g_osets.at(0)->getHash(), g_size, 0, "");
        g_sol->setGoal();
        g_sol->printGrid();
        cout << "goal hash " << g_sol->getHash() << endl;
        printf("testing mem pointer %p\n", g_sol->getGrid());

        cout << "\nPlease select the algorithm you would like to use to solve this puzzle...";
        cout << "\n(1) AStar\n(2) Greedy\n(3) Breadth-First\n(4) Depth-First\n";

        GETALGO:
        if (cin >> lineIn) {
            // It worked (input is now in a good state)
            if (lineIn == 1) {
                g_algo = ASTAR;
                goto ENDALGO;
            } else if (lineIn == 2) {
                g_algo = GREEDY;
                goto ENDALGO;
            } else if (lineIn == 3) {
                g_algo = BREADTHFIRST;
                goto ENDALGO;
            } else if (lineIn == 4) {
                g_algo = DEPTHFIRST;
                goto ENDALGO;
            } else {
                cout << "Please enter either 1, 2, 3 or 4\n";
                cin.clear();
                goto GETALGO;
            }
        } else {

            cout << "Please enter either 1, 2, 3 or 4\n";
            cin.clear();

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto GETALGO;
        }
        ENDALGO:

        cout << "\nPlease select the heuristic you would like to use to solve this puzzle...";
        cout << "\n(1) Hamming Distance Heuristic\n(2) Manhattan Distance Heuristic\n(3) Euclidean Distance Heuristic\n";

        GETHUR:
        if (cin >> lineIn)
        {
            // It worked (input is now in a good state)
            if (lineIn == 1)
                g_hstc = HAMMING;
            else if (lineIn == 2)
                g_hstc = MANHATTAN;
            else if (lineIn == 3)
                g_hstc = EUCLIDEAN;
            else {
                cout << "Please enter either 1, 2, or 3\n";
                goto GETHUR;
            }
        }
        else
        {
            cout << "Please enter either 1, 2, or 3\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto GETHUR;
        }

        cout << "\nWould you like to use line peniltys.";
        cout << "\n(1) Yes\n(2) No\n";

        GETPEN:
        if (cin >> lineIn)
        {
            if (lineIn == 1)
                g_penilty = 1;
            else if (lineIn == 2)
                g_penilty = 0;
            else {
                cout << "Please enter either 1 or 2\n";
                goto GETPEN;
            }
        }
        else
        {
            cout << "Please enter either 1 or 2\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto GETPEN;
        }

        cout << "\nWould you like the nodes to be represented verbosely? This may slow the algorithm slightly.";
        cout << "\n(1) Yes\n(2) No\n";

        GETVER:
        if (cin >> lineIn)
        {
            if (lineIn == 1)
                g_verb = 1;
            else if (lineIn == 2)
                g_verb = 0;
            else {
                cout << "Please enter either 1 or 2\n";
                goto GETVER;
            }
        }
        else
        {
            cout << "Please enter either 1 or 2\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            goto GETVER;
        }

        g_osets.at(0)->setCost();
        g_sol->setCost(0);
        cout << "\n" << g_osets.at(0)->toString() << "\n";
        cout << g_sol->toString() << "\n\n";

        solve();
    } else
        cout << "puzzle is unsolvable\n";
    return 0;
}

