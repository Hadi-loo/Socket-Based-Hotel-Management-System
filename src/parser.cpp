#include <fstream>
#include "parser.hpp"
#include "json.hpp"
#include "user.hpp"

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
    for (int i = 0; i < j["users"].size(); i++) {
        if (j[i]["admin"] == "true") {
            User* user = new User(j[i]["id"], j[i]["user"], j[i]["password"], true);
            users.push_back(user);
        }
        else {
            User* user = new User(j[i]["id"], j[i]["user"], j[i]["password"], false, j[i]["balance"], j[i]["phone"], j[i]["address"]);
            users.push_back(user);
        }
    }
    users_file.close();
    return users;
}