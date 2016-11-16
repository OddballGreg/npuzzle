#include "npuzzle.h"

using namespace std;

int main(int ac, char **argv) {

    if (argv[1] && file_exists(argv[1]) == true)
        g_osets.push_back(new Node(g_idc++, -1, parse(argv[1]), g_size, 0, NULL));
    else {
        cout << "Invalid file or no puzzle given, automatically generating random 3x3 puzzle\n";
        g_size = 3;
        g_osets.push_back((const Node &) new Node(g_idc++, -1, genPuzzle(g_size), g_size, 0, NULL));
    }
    if (isSolvable(g_osets.at(0).getGrid())) {
        cout << "can be solved\n";
        int lineIn;
        g_sol = new Node(-1, -1, g_osets.at(0).getHash(), g_size, 0, NULL);
        g_sol->setGoal();
        g_hstc = HAMMING;

        cout << "\nPlease select the algorithm you would like to use to solve this puzzle...";
        cout << "\n(1) AStar\n(2) Greedy\n(3) Breadth-First\n(4) Depth-First\n";

        while (g_algo == -1) {
            cin >> lineIn;
            if (lineIn == 1)
                g_algo = ASTAR;
            else if (lineIn == 2)
                g_algo = GREEDY;
            else if (lineIn == 3)
                g_algo = BREADTHFIRST;
            else if (lineIn == 4)
                g_algo = DEPTHFIRST;
            else {
                cout << "Please enter either 1, 2, 3 or 4\n";
            }
        }

        cout << "\nPlease select the heuristic you would like to use to solve this puzzle...";
        cout
                << "\n(1) Hamming Distance Heuristic\n(2) Manhattan Distance Heuristic\n(3) Euclidean Distance Heuristic\n";
        while (g_hstc == -1) {
            cin >> lineIn;
            if (lineIn == 1)
                g_hstc = HAMMING;
            else if (lineIn == 2)
                g_hstc = MANHATTAN;
            else if (lineIn == 3)
                g_hstc = EUCLIDEAN;
            else {
                cout << "Please enter either 1, 2, or 3\n";
            }
        }

        cout << "\nWould you like the nodes to be represented verbosely? This may slow the algorithm slightly.";
        cout << "\n(1) Yes\n(2) No\n";
        while (g_verb) {
            cin >> lineIn;
            if (lineIn == 1)
                g_verb = 1;
            else if (lineIn == 2)
                g_verb = 0;
            else {
                cout << "Please enter either 1 or 2\n";
            }
        }

        g_osets.at(0).setCost();
        g_sol->setCost(0);
        cout << "\n" << g_osets.at(0).toString << "\n";
        cout << g_sol->toString <<"\n\n";

        solve();
    } else
        cout << "puzzle is unsolvable\n";
    return 0;
}