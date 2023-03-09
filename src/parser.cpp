#include "parser.hpp"
// #include "utils.hpp"
#include <iostream>


Parser::Parser(string configs_path) {
    this->configs_path = configs_path;
}

Parser::~Parser() {
    // TODO
}

void Parser::parse_config(string config_file_name, string &hostName, int &port) {
    std:ifstream config_file;
    config_file.open(configs_path + "/" + config_file_name, std::ifstream::in);
    nlohmann::json j;
    config_file >> j;
    hostName = j["hostName"];
    port = j["commandChannelPort"];
    config_file.close();
    return;
}


vector<User*> Parser::parse_users(string users_file_name) {
    std::ifstream users_file;
    users_file.open(configs_path + "/" + users_file_name, std::ifstream::in);
    nlohmann::json j;
    users_file >> j;
    vector<User*> users;
    for (auto user_info : j["users"]) {
        if (user_info["admin"] == "true") {
            User* user = new User(user_info["id"], user_info["user"], user_info["password"], true);
            users.push_back(user);
        } else {
            User* user = new User(user_info["id"], user_info["user"], user_info["password"], false, user_info["purse"], user_info["phoneNumber"], user_info["address"]);
            users.push_back(user);
        }
    }
    users_file.close();
    return users;
}


vector<string> Parser::split_string(const string& input, char delimiter){
    vector<string> words;
    string substring;
    for (char c : input){
        if (c == delimiter){
            words.push_back(substring);
            substring.clear();
        }
        else{
            substring += c;
        }
    }
    if (!substring.empty()){
        words.push_back(substring);
    }
    return words;
}