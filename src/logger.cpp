#include "logger.hpp"

Logger::Logger(string log_file_name){
    this->log_file_name = log_file_name;
}

Logger::~Logger(){
    // TODO
}

void Logger::log(string message){
    log_file.open(log_file_name, ios::app);
    log_file << message << endl;
    log_file.close();
}

