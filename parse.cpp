//
// Created by Robert JONES on 2016/11/16.
//

#include "npuzzle.h"

void processLine(string *build, string line, int lineCount) {
    vector<string> col = explode(line, ' ');
    if (col.size() != g_size) {
        cout << "the number of colums in lin '" << line << "' is incorect" << endl;
        exit(EXIT_SUCCESS);
    }
    for (vector<string>::iterator it = col.begin(); it < col.end(); it++) {
        //if (strstr(build->c_str(), it->c_str()) == NULL) {
            (*build) += *it;
            if (it != col.end() - 1)
                (*build) += ' ';
        //} else {
          //  cout << "duplicate number " << *it << " invalid puzzel" << endl;
            //exit(EXIT_SUCCESS);
        //}
    }
    if (lineCount != g_size)
        (*build) += ',';
}

string parse(string fileName) {
    string re;
    ifstream infile(fileName);
    string line;
    char *comptr;
    int lineCount = 0;

    while (std::getline(infile, line)) {
        if (!line.empty() && line.find_first_not_of(" \t") != std::string::npos) {
            line = line.substr(line.find_first_not_of(" \t"), line.length());
            comptr = strchr(line.c_str(), '#');
            if (comptr != line.c_str()) {
                std::cout << line << std::endl;
                lineCount++;
                if (comptr == NULL) {
                    if (lineCount == 1) {
                        g_size = atoi(line.c_str());
                        if (g_size < 3) {
                            cout << "the puzzel is to small it should be at least 3x3" << endl;
                            exit(EXIT_SUCCESS);
                        }
                    } else
                        processLine(&re, line, lineCount - 1);
                } else {
                    line = line.substr(0, line.find_first_of('#'));
                    processLine(&re, line, lineCount - 1);
                }

            }
        }
    }
    if (lineCount - 1 != g_size) {
        cout << "the number of lines given dous not match the puzel size" << endl;
        exit(EXIT_SUCCESS);
    }
    cout << "there are " << lineCount << " lines puzel size is " << g_size << endl;
    cout << "hash: " << re << endl;
    return re;
}