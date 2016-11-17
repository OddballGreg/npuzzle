//
// Created by Robert JONES on 2016/11/16.
//

#include "suportFunctions.h"
#include "npuzzle.h"

std::vector<std::string> explode(std::string const &s, char delim) {
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim);) {
        result.push_back(std::move(token));
    }

    return result;
}

bool file_exists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

bool in_array(int val, int *arr, int size) {
    int iter = -1;
    while (++iter < size) {
        if (arr[iter] == val) {
            return true;
        }
    }
    return false;
}

string genPuzzle(int size) {
    cout << "gen puzzel called" << endl;
    int max = size * size;
    int used[max];
    int iter = 0;
    string hash;

    for (int xiter = 0; xiter < g_size; xiter++) {
        for (int yiter = 0; yiter < g_size; yiter++) {
            int newNum = rand() % max;
            while (in_array(newNum, used, iter)) {
                newNum = rand() % max;
            }
            used[iter++] = newNum;
            hash += (newNum + '0');
            if (yiter != g_size - 1)
                hash += ' ';
        }
        if (xiter != g_size - 1)
            hash += ',';
    }
    cout << " gen puzzel exiting" << endl;
    return (hash);
}

bool isSolvable(int **grid) {
    int max = g_size * g_size - 1;
    int inversions = 0;
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
    int blank;
    // find state
    while (count < cap) {
        if (dir == 1) {
            while (yiter < ymax) {
                if (grid[xiter][yiter] != 0)
                    line[count++] = grid[xiter][yiter];
                else {
                    blank = xiter;
                }
                yiter++;
            }
            xiter++;
            yiter--;

            while (xiter < xmax) {
                if (grid[xiter][yiter] != 0)
                    line[count++] = grid[xiter][yiter];
                else {
                    blank = xiter;
                    count++;
                }
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
                else {
                    blank = xiter;
                    count++;
                }
                yiter--;
            }

            yiter++;
            xiter--;

            while (xiter > xmin) {
                if (grid[xiter][yiter] != 0)
                    line[count++] = grid[xiter][yiter];
                else {
                    blank = xiter;
                    count++;
                }
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
    for (int i = 0; i < max; i++) {
        for (int j = i + 1; j < max; j++) {
            if (line[i] > line[j]) {
                inversions++;
            }
        }
    }
    cout << "num inversions " << inversions << "\n";
    cout << "blank odd even " << ((g_size - blank) % 2) << " actual value " << (g_size - blank) << " blank " << blank
         << "\n";
    if ((g_size % 2 == 1 && inversions % 2 == 0)) {
        cout << "odd puzel even inverces\n";
        return true;
    }
    if (g_size % 2 == 0 && ((g_size - blank) % 2 == inversions % 2)) {
        cout << "even puzzel " << (g_size - blank) % 2 << "\n";
        return true;
    }
    return false;
}