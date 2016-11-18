//
// Created by Robert JONES on 2016/11/16.
//

#ifndef NPUZZELC_SUPORTFUNCTIONS_H
#define NPUZZELC_SUPORTFUNCTIONS_H

#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

std::vector<std::string> explode(std::string const & s, char delim);
bool file_exists (const std::string& name);
std::string genPuzzle(int size);
bool isSolvable(int **grid);
bool in_array(int val, int *arr, int size);
std::string parse(std::string fileName);
void ft_exit(std::string msg, int exitcode);
#endif //NPUZZELC_SUPORTFUNCTIONS_H
