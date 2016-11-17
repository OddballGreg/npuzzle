//
// Created by Robert JONES on 2016/11/16.
//

#include "npuzzle.h"

string parse(string fileName) {
    string re;
    ifstream infile(fileName);
    string line;
    int lineCount = 0;

    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
        if (strchr(line.c_str(), '#') != line.c_str() && line.c_str() != NULL) {
            if (strchr(line.c_str(), '#') == NULL && lineCount == 0)
                g_size = atoi(line.c_str());
            lineCount++;
        }

    }
    return re;
}