#include "HotelManagement.hpp"

HotelManagement::HotelManagement(){
    users = vector <User*>();
    reservations = vector <Reservation*>();
    rooms = vector <Room*>();
}

HotelManagement::~HotelManagement(){
    for (int i = 0; i < users.size(); i++)
        delete users[i];
    for (int i = 0; i < reservations.size(); i++)
        delete reservations[i];
    for (int i = 0; i < rooms.size(); i++)
        delete rooms[i];
}

void HotelManagement::set_server_ip(string server_ip){
    this->server_ip = server_ip;
}

void HotelManagement::set_server_port(int server_port){
    this->server_port = server_port;
}

void HotelManagement::add_user(User* user){
    users.push_back(user);
}

void HotelManagement::add_users(vector <User*> users){
    for (int i = 0; i < users.size(); i++)
        this->users.push_back(users[i]);
}

void HotelManagement::add_room(Room* room){
    rooms.push_back(room);
}

void HotelManagement::add_rooms(vector <Room*> rooms){
    for (int i = 0; i < rooms.size(); i++)
        this->rooms.push_back(rooms[i]);
}

void HotelManagement::add_reservation(Reservation* reservation){
    reservations.push_back(reservation);
}

void HotelManagement::add_reservations(vector <Room*> rooms){
    for (int i = 0; i < rooms.size(); i++){
        vector<Reservation*> _reservations = rooms[i]->get_reservations();
        for (int j = 0 ; j < _reservations.size() ; j++)
            this->reservations.push_back(_reservations[j]);
    }
}

string HotelManagement::handle_request(vector<string> request){
    // TODO
    // handel request.size() == 0 in server.cpp file
    string command_type = request[0];
    if(command_type == "Signup" && request.size() == 2){
        // handel merging input from the server.cpp file
    }
    else if(command_type == "Signin" && request.size() == 2){
        // TO DO
    }
    else if(command_type == "view" && request.size() == 3){                                                   // 5.1 5.2 5.3 : view commands 
        if(request[1] == "my"){}
        else if(request[1] == "users"){}
        else if(request[1] == "rooms"){}
        else{
            // Error Handler
        }
    }
    /*
    To DO: Add other commands
    */
    else{
        // Error Handler
    }
    return "OK\n";
}
