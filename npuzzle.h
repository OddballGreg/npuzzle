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
#include "Node.h"

typedef struct s_point {
    int x;
    int y;
} t_point;

Node *g_sol; // Solution
vector<Node> g_osets; // Open Sets
vector<Node> g_csets; // Closed Sets
vector<string> g_checked;
int g_idc = 0; // ID counter
int g_size = 3;
int g_hstc = -1;
int g_algo = -1;
int g_verb = -1;


int hamming(Node *node, Node *solution);

int manhattan(Node *node, Node *solution);

int euclidean(Node *node, Node *solution);

void solve();

t_point findxy(int grid[g_size][g_size], int number);


#endif //NPUZZELC_NPUZZLE_H
