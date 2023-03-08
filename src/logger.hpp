#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Logger {
private:
    string logs_path;
    ofstream log_file;
public:
    Logger(string _logs_path);
    ~Logger();
    void log(string _log_file_name, string _message);
    string current_time();
};

#endif