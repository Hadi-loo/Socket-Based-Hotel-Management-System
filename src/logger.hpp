#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Logger {
private:
    string log_file_name;
    ofstream log_file;
public:
    Logger(string);
    ~Logger();
    void log(string);
    string current_time();
};

#endif