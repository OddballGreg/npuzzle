//
// Created by Robert JONES on 2016/11/16.
//

#include "Node.h"


//id of -1 representes a solution state

Node::Node(int id, int parentID, string hash, int size, int dist ,const string &parentHash)
{
    this->_id = id;
    this->_parentID = parentID;
    this->_size = size;
    this->_dist = dist;
    this->_parentHash = parentHash;
    this->_grid = (int**)malloc(sizeof(int) * size*size);
    this->_hash = hash;
    vector<string> rows = explode(hash, ',');
    int x = -1;
    while (++x < size)
    {
        int y = -1;
        vector<string> cols = explode(rows.at(x), ' ');
        while (++y < size)
            _grid[x][y] = atoi(cols.at(y).data());
            if (this->_grid[x][y] == 0)
            {
                this->_emptyxy.x = x;
                this->_emptyxy.y = y;
            }
    }

    if (this->_id != -1 && this->_id != 0) // Cost setting is dependent on the solution existing. The solution is derived from the initial state.
        setCost();
}

void Node::setCost(int *cost = NULL){
    if (cost != NULL)
        this->_estcost = *cost;
    else
    {
        if (g_hstc == MANHATTAN){
            this->_estcost = manhattan(this, g_sol);
        }
        else if (g_hstc == EUCLIDEAN){
            this->_estcost = euclidean(this, g_sol);
        }
        else{
            this->_estcost = hamming(this, g_sol);
        }
    }
}

vector<Node> Node::genMoves()
{
    vector<Node> moves;
    int **grid = this->_grid;
    int temp;
    string hash;
    bool check;
    
    if (_emptyxy.x + 1 < g_size)
    {
        temp = grid [this->_emptyxy.x + 1] [this->_emptyxy.y];
        grid [this->_emptyxy.x + 1] [this->_emptyxy.y] = grid [this->_emptyxy.x] [this->_emptyxy.y];
        grid [this->_emptyxy.x] [this->_emptyxy.y] = temp;
        hash = this->makeHash(grid);
        check = false;
        if((std::find(g_checked.begin(), g_checked.end(), hash) != g_checked.end()))
            check = true;
        if (strcmp(this->_parentHash, hash) != 0 && check == false)
            moves.push_back((const Node &) new Node(g_idc++, this->_id, hash, g_size, this->_dist + 1, this->_hash));
    }
    grid = this->_grid;
    if (this->_emptyxy.x - 1 > -1)
    {
        temp = grid [this->_emptyxy.x - 1] [this->_emptyxy.y];
        grid [this->_emptyxy.x - 1] [this->_emptyxy.y] = grid [this->_emptyxy.x] [this->_emptyxy.y];
        grid [this->_emptyxy.x] [this->_emptyxy.y] = temp;
        hash = this->makeHash(grid);
        check = false;
        if((std::find(g_checked.begin(), g_checked.end(), hash) != g_checked.end()))
            check = true;
        if (strcmp(this->_parentHash, hash) != 0 && check == false)
            moves.push_back((const Node &) new Node(g_idc++, this->_id, hash, g_size, this->_dist + 1, this->_hash));
    }
    grid = this->_grid;
    if (this->_emptyxy.y + 1 < g_size)
    {
        temp = grid [this->_emptyxy.x] [this->_emptyxy.y  + 1];
        grid [this->_emptyxy.x] [this->_emptyxy.y  + 1] = grid [this->_emptyxy.x] [this->_emptyxy.y];
        grid [this->_emptyxy.x] [this->_emptyxy.y] = temp;
        hash = this->makeHash(grid);
        check = false;
        if((std::find(g_checked.begin(), g_checked.end(), hash) != g_checked.end()))
            check = true;
        if (strcmp(this->_parentHash, hash) != 0 && check == false)
            moves.push_back((const Node &) new Node(g_idc++, this->_id, hash, g_size, this->_dist + 1, this->_hash));
    }
    grid = this->_grid;
    if (this->_emptyxy.y - 1 > -1)
    {
        temp = grid [this->_emptyxy.x] [this->_emptyxy.y - 1];
        grid [this->_emptyxy.x] [this->_emptyxy.y  - 1] = grid [this->_emptyxy.x] [this->_emptyxy.y];
        grid [this->_emptyxy.x] [this->_emptyxy.y] = temp;
        hash = this->makeHash(grid);
        check = false;
        if((std::find(g_checked.begin(), g_checked.end(), hash) != g_checked.end()))
            check = true;
        if (strcmp(this->_parentHash, hash) != 0 && check == false)
            moves.push_back((const Node &) new Node(g_idc++, this->_id, hash, g_size, this->_dist + 1, this->_hash));
    }
    return(moves);
}

void Node::setGoal()
{
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

string Node::makeHash(int **grid)
{
    string hash;

    for (int xiter = 0; xiter < g_size; xiter++) {
        for (int yiter = 0; yiter < g_size; yiter++) {
            hash += (grid[xiter][yiter] + '0');
            if (yiter != g_size - 1)
                hash += ' ';
        }
        if (xiter != g_size - 1)
            hash += ',';
    }
    return (hash);
}

string Node::toString()
{
    char *line[300];
    sprintf(line, "ID: %d \tHash: %s \tDistance Travelled: %d \tEstCost: %d tFofX: %d\tParentID: %d\n" ,
            this->_id , this->_hash ,this->_dist, this->_estcost, this->_estcost + this->_dist, this->_parentID);
}