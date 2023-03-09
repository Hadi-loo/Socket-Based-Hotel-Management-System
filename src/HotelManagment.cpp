#include "HotelManagment.hpp"

HotelManagment::HotelManagment(){
    users = vector <User*>();
    reservations = vector <Reservation*>();
    rooms = vector <Room*>();
}

HotelManagment::~HotelManagment(){
    for (int i = 0; i < users.size(); i++)
        delete users[i];
    for (int i = 0; i < reservations.size(); i++)
        delete reservations[i];
    for (int i = 0; i < rooms.size(); i++)
        delete rooms[i];
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

void HotelManagment::add_room(Room* room){
    rooms.push_back(room);
}

void HotelManagment::add_rooms(vector <Room*> rooms){
    for (int i = 0; i < rooms.size(); i++)
        this->rooms.push_back(rooms[i]);
}

void HotelManagment::add_reservation(Reservation* reservation){
    reservations.push_back(reservation);
}

void HotelManagment::add_reservations(vector <Room*> rooms){
    for (int i = 0; i < rooms.size(); i++){
        vector<Reservation*> _reservations = rooms[i]->get_reservations();
        for (int j = 0 ; j < _reservations.size() ; j++)
            this->reservations.push_back(_reservations[j]);
    }
}

