//
// Created by Robert JONES on 2016/11/16.
//

#ifndef NPUZZELC_NODE_H
#define NPUZZELC_NODE_H

#include <iostream>
#include "suportFunctions.h"
#include "npuzzle.h"


using namespace std;

class Node {
private:


    string _parentHash;
    string _hash;
    int **_grid;
    int _parentID;
    int _id;
    int _size;
    int _dist;
    int _estcost;
    t_point _emptyxy = {0, 0};
public:
    Node(int id, int parent, string hash, int size, int dist, const string &parentHash);

    string getHash() {
        return (this->_hash);
    }

    int **getGrid() {
        return (this->_grid);
    }

    int getParent() {
        return (this->_parentID);
    }

    int getId() {
        return (this->_id);
    }

    int getFofX() {
        return (this->_dist + this->_estcost);
    }

    int getCost() {
        return (this->_estcost);
    }

    int getDist() {
        return (this->_dist);
    }

    void setCost(int *cost = NULL);

    vector<Node> genMoves();

    void setGoal();

    string makeHash(int **grid);

    string toString();
};


#endif //NPUZZELC_NODE_H

