#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <string>
using namespace std;

class Parser {
private:
    string configs_path;
public:
    Parser(string configs_path);
    ~Parser();
    void parse_config(string config_file, string &hostName, int &port);
};


#endif