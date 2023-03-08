#include "HotelManagment.hpp"

HotelManagment::HotelManagment(){
    users = vector <User*>();
    reserves = vector <Reservation*>();
    rooms = vector <Room*>();
}

HotelManagment::~HotelManagment(){
    for (int i = 0; i < users.size(); i++)
        delete users[i];
    for (int i = 0; i < reserves.size(); i++)
        delete reserves[i];
    for (int i = 0; i < rooms.size(); i++)
        delete rooms[i];
}

HotelManagment::HotelManagment(vector <User*> _users , vector <Reservation*> _reserves , vector<Room*> _rooms , string _server_ip , int _server_port){
    users = _users;
    reserves = _reserves;
    rooms = _rooms;
    server_ip = _server_ip;
    server_port = _server_port;
}

void HotelManagment::set_server_ip(string server_ip){
    this->server_ip = server_ip;
}

void HotelManagment::set_server_port(int server_port){
    this->server_port = server_port;
}

void HotelManagment::add_user(User* user){
    users.push_back(user);
}

void HotelManagment::add_users(vector <User*> users){
    for (int i = 0; i < users.size(); i++)
        this->users.push_back(users[i]);
}



