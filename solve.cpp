//
// Created by Robert JONES on 2016/11/16.
//

#include "npuzzle.h"

void printSolution(Node *endNode) {
    int pid = endNode->getParent();
    for (vector<Node>::iterator node = g_osets.begin(); node < g_osets.end(); node++) {
        int tid = node->getId();
        if (tid == pid)
            printSolution(&(*node));
    }
    for (vector<Node>::iterator node = g_csets.begin(); node < g_csets.end(); node++) {
        int tid = node->getId();
        if (tid == pid)
            printSolution(&(*node));
    }
    cout << endNode->toString();
}

void solve() {
    if (strcmp(g_osets.at(0).getHash().c_str(), g_sol->getHash().c_str()) == 0) {
        cout << "Puzzle is already solved.\n";
        exit(EXIT_SUCCESS);
    }

    //time = time();
    int iterations = 0;
    int nodes = 1;
    g_checked.push_back(g_osets.at(0).getHash());

    cout << "oset size: " << g_osets.size() << endl;

    while (1) {
        //get the chepest openset
        iterations++;
        Node *cheapest = NULL;
        for (vector<Node>::iterator node = g_osets.begin(); node < g_osets.end(); node++) {
            if (cheapest == NULL) {
                cheapest = &(*node);
            } else {
                if (g_algo == ASTAR) {
                    if (cheapest != NULL && node->getFofX() <= cheapest->getFofX()) {
                        cheapest = &(*node);
                    }
                } else if (g_algo == GREEDY) {
                    if (cheapest != NULL && node->getCost() < cheapest->getCost())
                        cheapest = &(*node);
                } else if (g_algo == DEPTHFIRST) {
                    cheapest = &(*g_osets.end());
                } else //breadthfirst
                    break;
            }
        }
        if (cheapest == NULL) {
            cout << "No open set found\n";
            exit(EXIT_SUCCESS);
        }
        //Get new moves from cheapest node, compare to solution and add to open sets
        vector<Node> newnodes = cheapest->genMoves();
        for (vector<Node>::iterator node = newnodes.begin(); node < newnodes.end(); node++) {
            if (strcmp(node->getHash().c_str(), g_sol->getHash().c_str()) == 0) {
                cout << "\n\nSolution Found:\n";
                cout << node->toString() << "\n";
                cout << "steps to solution:\n";
                printSolution(&(*node));
                //cout << "\nSolution found in " << (time() - time) << " second(s) after "<< iterations << " iteration(s).\n";
                cout << "{nodes} nodes were generated in order to find the " << node->getDist()
                     << " moves of the solution.\n";
                cout << "open list: " << g_osets.size() << " closed set " << g_csets.size() << " \n";
                cout << "\n";
                exit(EXIT_SUCCESS);
            }
        }


        for (vector<Node>::iterator newNode = newnodes.begin(); newNode < newnodes.end(); newNode++) {
            g_osets.push_back((*newNode));
            g_checked.push_back(newNode->getHash());
        }

        //Add cheapest to closed sets and remove from open sets
        g_csets.push_back(*cheapest);
        int index = -1;
        int max = g_osets.size();
        while (++index < max) {
            if (cheapest->getId() == g_osets.at(index).getId()) {
                g_osets.erase(g_osets.begin() + index);
                break;
            }
        }
        if (g_verb == 1)
            cout << cheapest->toString() << "\n";
        else if (iterations % 100 == 0)
            cout << ".";
    }
}

