//
// Created by Robert JONES on 2016/11/16.
//

#include "suportFunctions.h"

std::string parse(std::string fileName) {
    std::ifstream infile(fileName);
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
}