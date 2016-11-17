#include <vector>//
// Created by Robert JONES on 2016/11/16.
//

#ifndef NPUZZELC_NPUZZLE_H
#define NPUZZELC_NPUZZLE_H

# define HAMMING  1
# define MANHATTAN  2
# define EUCLIDEAN  3
# define ASTAR  1
# define GREEDY  2
# define BREADTHFIRST 3
# define DEPTHFIRST 4

#include <math.h>
#include "suportFunctions.h"


typedef struct s_point {
    int x;
    int y;
} t_point;

using namespace std;


extern int g_idc; // ID counter
extern int g_size;
extern int g_hstc;
extern int g_algo;
extern int g_verb;

class Node {
private:
    string _parentHash;
public:
    Node();

private:
    string _hash;
    int **_grid;
    int _parentID;
    int _id;
    int _size;
    int _dist;
    int _estcost;
    struct s_point _emptyxy;
public:
    Node(int id, int parent, string hash, int size, int dist, string parentHash);

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

    void printGrid();

    void makeMove(int x,int y ,vector<Node> *moves);

    string makeHash(int **grid);

    string toString();
};

extern Node *g_sol; // Solution
extern vector<Node> g_osets; // Open Sets
extern vector<Node> g_csets; // Closed Sets
extern vector<string> g_checked;

int hamming(Node *node);

int manhattan(Node *node);

int euclidean(Node *node);

void solve();

t_point findxy(int **grid, int number);

string parse(std::string fileName);

void printSolution(Node *endNode);

#endif //NPUZZELC_NPUZZLE_H
