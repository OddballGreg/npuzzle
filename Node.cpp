//
// Created by Robert JONES on 2016/11/16.
//

#include "npuzzle.h"


//id of -1 representes a solution state

Node::Node(int id, int parentID, string hash, int size, int dist, string parentHash) {
    this->_id = id;
    this->_parentID = parentID;
    this->_size = size;
    this->_dist = dist;
    this->_parentHash = parentHash;
    this->_grid = (int **) malloc(sizeof(int *) * size);
    this->_hash = hash;
    vector<string> rows = explode(hash, (char*)(","));
    int x = -1;
    while (++x < size) {
        int y = -1;
        vector<string> cols = explode(rows.at(x), (char*)(" "));
        this->_grid[x] = (int *) malloc(sizeof(int) * size);
        while (++y < size && y < cols.size()) {
            this->_grid[x][y] = atoi(cols.at(y).c_str());
            if (this->_grid[x][y] == 0) {
                this->_emptyxy.x = x;
                this->_emptyxy.y = y;
            }
        }
    }
    if (this->_id != -1 && this->_id !=
                           0) // Cost setting is dependent on the solution existing. The solution is derived from the initial state.
        setCost();
}

void Node::setCost(int *cost) {
    if (cost != NULL)
        this->_estcost = *cost;
    else {
        if (g_hstc == MANHATTAN) {
            this->_estcost = manhattan(this);
        } else if (g_hstc == EUCLIDEAN) {
            this->_estcost = euclidean(this);
        } else {
            this->_estcost = hamming(this);
        }
        if (g_penilty == 1)
            this->_estcost += penilty(this->_grid);
    }
}

void Node::makeMove(int x, int y, vector<Node*> *moves) {
    int **grid;

    string hash;
    bool check;
    if (!(grid = (int **) malloc(sizeof(int *) * g_size)))
        return;
    for (int x = 0; x < g_size; x++) {
        if (!(grid[x] = (int *) malloc(sizeof(int) * g_size)))
            return;
        for (int y = 0; y < g_size; y++) {
            grid[x][y] = this->_grid[x][y];
        }
    }

    if (_emptyxy.x + x < g_size && _emptyxy.y + y < g_size && _emptyxy.x + x > -1 && _emptyxy.y + y > -1) {
        grid[_emptyxy.x][_emptyxy.y] = this->_grid[_emptyxy.x + x][_emptyxy.y + y];
        grid[_emptyxy.x + x][_emptyxy.y + y] = this->_grid[_emptyxy.x][_emptyxy.y];
        hash = this->makeHash(grid);
        check = false;
        if ((std::find(g_checked.begin(), g_checked.end(), hash) != g_checked.end()))
            check = true;
        if (strcmp(this->_parentHash.c_str(), hash.c_str()) != 0 && !check) {
            //cout << "adding: " << hash << endl;
            moves->push_back(new Node (g_idc++, this->_id, hash, g_size, this->_dist + 1, this->_hash));
        }
    }
    for (int x = 0; x < g_size; x++) {
        delete[] grid[x];
    }
    delete[] grid;
}

vector<Node*> Node::genMoves() {
    vector<Node*> moves;

    makeMove(1, 0, &moves);
    makeMove(0, 1, &moves);
    makeMove(0, -1, &moves);
    makeMove(-1, 0, &moves);

    return (moves);
}

void Node::setGoal() {
    int size = this->_size;
    int xiter = 0;
    int yiter = 0;
    int dir = 1;
    int xmax = size;
    int ymax = size;
    int xmin = -1;
    int ymin = -1;
    int count = 1;
    int cap = size * size;

    while (count < cap) {
        if (dir == 1) {
            while (yiter < ymax) {
                this->_grid[xiter][yiter] = count;
                yiter++;
                count++;
            }

            xiter++;
            yiter--;

            while (xiter < xmax) {
                this->_grid[xiter][yiter] = count;
                xiter++;
                count++;
            }
            xiter--;
            yiter--;
            xmin++;
            ymax--;
            dir = -1;
        } else {
//swich direction

            while (yiter > ymin) {
                this->_grid[xiter][yiter] = count;
                yiter--;
                count++;
            }

            yiter++;
            xiter--;

            while (xiter > xmin) {
                this->_grid[xiter][yiter] = count;
                xiter--;
                count++;
            }

            xiter++;
            yiter++;
            xmax--;
            ymin++;

            dir = 1;
        }
    }

    this->_grid[xiter][yiter] = 0;

    this->_hash = this->makeHash(this->_grid);
}

string Node::makeHash(int **grid) {
    string hash;

    for (int xiter = 0; xiter < g_size; xiter++) {
        for (int yiter = 0; yiter < g_size; yiter++) {
            hash += to_string(grid[xiter][yiter]);
            if (yiter != g_size - 1)
                hash += ' ';
        }
        if (xiter != g_size - 1)
            hash += ',';
    }
    return (hash);
}

void Node::printGrid() {
    for (int x = 0; x < g_size; x++) {
        for (int y = 0; y < g_size; ++y) {
            cout << this->_grid[x][y] << " ";
        }
        cout << endl;
    }
}

string Node::toString() {
    char line[300];
    sprintf(line, "ID: %6d \tHash: %s \tDistance Travelled: %3d \tEstCost: %3d tFofX: %3d\tParentID: %10d\n",
            this->_id, this->_hash.c_str(), this->_dist, this->_estcost, this->_estcost + this->_dist, this->_parentID);
    string re(line);
    return (re);
}

Node::Node() {}

Node::~Node() {
    for (int i = 0; i < _size; ++i) {
        delete[] _grid[i];
    }
    delete[] _grid;
}
