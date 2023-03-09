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


vector<Room*> Parser::parse_rooms(string rooms_file_name){
    std::ifstream rooms_file;
    rooms_file.open(configs_path + "/" + rooms_file_name, std::ifstream::in);
    nlohmann::json j;
    rooms_file >> j;
    vector<Room*> rooms;
    vector<Reservation*> reservations;
    for (auto room_info : j["rooms"]) {
        reservations.clear();                                                                                           // can be replaced by an smart pointer
        for (auto reservation_info : room_info["users"]) {
            vector<string> checkInDate = split_string(reservation_info["checkInDate"], '-');
            vector<string> checkOutDate = split_string(reservation_info["checkInDate"], '-');
            Date _checkInDate = Date(stoi(checkInDate[2]), stoi(checkInDate[1]), stoi(checkInDate[0]));
            Date _checkOutDate = Date(stoi(checkOutDate[2]), stoi(checkOutDate[1]), stoi(checkOutDate[0]));
            Reservation* reservation = new Reservation(reservation_info["id"], room_info["number"] , reservation_info["roomNumber"], _checkInDate , _checkOutDate);
            reservations.push_back(reservation);
        }
        bool is_available = (room_info["capacity"] == room_info["maxCapacity"]) ? true : false; 
        Room* room = new Room(room_info["id"], room_info["maxCapacity"], room_info["capacity"], room_info["price"], is_available , reservations);
    }
    rooms_file.close();
    return rooms;
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