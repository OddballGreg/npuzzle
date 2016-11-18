//
// Created by Robert JONES on 2016/11/16.
//

#include "npuzzle.h"

using namespace std;

int hamming(Node *node) {
    int **ngrid = node->getGrid();
    int **sgrid = g_sol->getGrid();
    int xindex = -1;
    int yindex;
    int cost = 0;
    while (++xindex < g_size) {
        yindex = -1;
        while (++yindex < g_size) {
            if (ngrid[xindex][yindex] != sgrid[xindex][yindex])
                cost++;
        }
    }
    return (cost);
}

int euclidean(Node *node) {
    int **ngrid = node->getGrid();
    int **sgrid = g_sol->getGrid();
    int xind = -1;
    int yind;
    t_point sxy;
    double cost = 0;

    while (++xind < g_size) {
        yind = -1;
        while (++yind < g_size) {
            if (ngrid[xind][yind] != 0) {
                sxy = findxy(sgrid, ngrid[xind][yind]);
                cost += sqrt(pow((sxy.x - xind), 2) + pow((sxy.y - yind), 2));
            }
        }

    }
    return ((int) (floor(cost)));
}

int manhattan(Node *node) {

    int **ngrid = node->getGrid();
    int **sgrid = g_sol->getGrid();
    int cost = 0;
    int xiter = -1;
    int yiter;
    int val;
    t_point sxy;

    while (++xiter < g_size) {
        yiter = -1;
        while (++yiter < g_size) {
            val = ngrid[xiter][yiter];
            if (val != 0) {
                sxy = findxy(sgrid, val);
                cost += abs(sxy.x - xiter) + abs(sxy.y - yiter);
            }
        }
    }
    return (cost);
}

int penilty(int **grid) {
    int max = g_size * g_size - 1;
    int peniltys = 0;
    int size = g_size;
    int xiter = 0;
    int yiter = 0;
    int dir = 1;
    int xmax = size;
    int ymax = size;
    int xmin = -1;
    int ymin = -1;
    int count = 0;
    int cap = size * size;
    int line[max];
    // find state
    while (count < max) {
        if (dir == 1) {
            while (yiter < ymax) {
                if (grid[xiter][yiter] != 0)
                    line[count++] = grid[xiter][yiter];
                yiter++;
            }
            xiter++;
            yiter--;

            while (xiter < xmax) {
                if (grid[xiter][yiter] != 0)
                    line[count++] = grid[xiter][yiter];
                xiter++;
            }
            xiter--;
            yiter--;
            xmin++;
            ymax--;
            dir = -1;
        } else {
//swich direction

            while (yiter > ymin) {
                if (grid[xiter][yiter] != 0)
                    line[count++] = grid[xiter][yiter];
                yiter--;
            }

            yiter++;
            xiter--;

            while (xiter > xmin) {
                if (grid[xiter][yiter] != 0)
                    line[count++] = grid[xiter][yiter];
                xiter--;
            }

            xiter++;
            yiter++;
            xmax--;
            ymin++;

            dir = 1;
        }
    }

    // eval state
    for (int i = 0; i < max ; i += g_size) {
        for (int x = i; x < (i + g_size - 1); x++){
            for (int y = x + 1; y < (i + g_size); y++)
            {
                if (line[x] > line[y])
                    peniltys++;
            }
        }
    }
    return peniltys;

}

t_point findxy(int **grid, int number) {
    t_point re = {-1, -1};
    int x = -1;
    int y;
    while (++x < g_size) {
        y = -1;
        while (++y < g_size) {
            if (grid[x][y] == number) {
                re = (t_point) {x, y};
                return (re);
            }
        }
    }
    return (re);
}