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


bool HotelManagement::authorization_confirmation(int file_descriptor){
    for (auto user:users){
        if(user->get_user_fd() == file_descriptor)
            return user->is_signed_in();
    }
    return false;
}


string HotelManagement::handle_request(vector<string> request , int user_fd){
    // TODO
    // handel request.size() == 0 in server.cpp file
    string command_type = request[0];
    if(command_type == "Signup" && request.size() == 6){
        // handel merging input from the server.cpp file
        // check error of phone number entering
        User* user = new User(users.size() , request[1] , sha256(request[2]) , false , stoi(request[3]) , request[4] , request[5]);
        user->set_user_fd(user_fd);
        users.push_back(user);

        // message 231
    }
    else if(command_type == "Signin" && request.size() == 3){
        bool found = false;
        for (auto user:users){
            if(request[1] == user->get_username() && request[2] == user->get_password()){
                found = true;
                user->sign_in();
                user->set_user_fd(user_fd);
            }
        }
        if(found){
            // message 230
        }
        else{
            // Error 430
        }
    }
    if(authorization_confirmation(user_fd) == false){
            // 503 error and return
    }
    // saving pointer to the current connected user
    User* current_user;
    for (auto user:users){
        if(user->get_user_fd() == user_fd){
            current_user = user;
            break;        
        }
    }
    if(command_type == "1" && request.size() == 1){                // 5.1 : view user information
        current_user->show_info();
    }
    else if(command_type == "2" && request.size() == 1){                // 5.2 : view all users
        if(current_user->_is_admin() == false){
            // Error Handler -> 503 error
        }
        for (auto user:users){
            user->show_info();
        }
    }
    else if(command_type == "3" && request.size() == 1){                // 5.3: view all rooms
        for (auto room:rooms){
            room->show_info();
        }
    }
    else if(command_type == "4" && request.size() == 6){                // 5.4:
        
    }
    else if(command_type == "5" && request.size() == 1){                // 5.5
    }
    else if(command_type == "6" && request.size() == 1){                // 5.6
    }
    else if(command_type == "7" && request.size() == 1){                // 5.7
    }
    else if(command_type == "8" && request.size() == 1){                // 5.8
    }
    else if(command_type == "9" && request.size() == 1){                // 5.9
    }
    else if(command_type == "0" && request.size() == 1){                // 5.10
    }

    /*
    To DO: Add other commands
    */
    else{
        // Error Handler -> 503 error
    }
    return "OK\n";
}
