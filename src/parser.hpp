#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
#include "user.hpp"
using namespace std;

class Parser {
private:
    string configs_path;
public:
    Parser(string configs_path);
    ~Parser();
    void parse_config(string config_file, string &hostName, int &port);
    vector<User*> parse_users(string users_file);
    
};


#endif