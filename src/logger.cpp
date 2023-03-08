#include "logger.hpp"

Logger::Logger(string log_file_name){
    this->log_file_name = log_file_name;
}

Logger::~Logger(){
    // TODO
}

void Logger::log(string message){
    log_file.open(log_file_name, ios::app);
    log_file << "[" << current_time() << "] " << message << endl;
    log_file.close();
}

string Logger::current_time(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string time = to_string(ltm->tm_year + 1900) + "-" + to_string(ltm->tm_mon + 1) + "-" + to_string(ltm->tm_mday) + " " +
                to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    return time;
}

