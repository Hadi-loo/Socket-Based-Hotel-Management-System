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

void HotelManagement::remove_user_by_id(int id){
    for (int i = 0; i < users.size(); i++){
        if (users[i]->get_id() == id){
            delete users[i];
            users.erase(users.begin() + i);
            return;
        }
    }
}

void HotelManagement::remove_user_by_username(string username){
    for (int i = 0; i < users.size(); i++){
        if (users[i]->get_username() == username){
            delete users[i];
            users.erase(users.begin() + i);
            return;
        }
    }
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

User* HotelManagement::get_user_by_id(int id){
    for (int i = 0; i < users.size(); i++){
        if (users[i]->get_id() == id)
            return users[i];
    }
    return NULL;
}

User* HotelManagement::get_user_by_username(string username){
    for (int i = 0; i < users.size(); i++){
        if (users[i]->get_username() == username)
            return users[i];
    }
    return NULL;
}

int HotelManagement::create_new_user_id(void){
    int max_id = 0;
    for (auto user:users){
        if(user->get_id() > max_id)
            max_id = user->get_id();
    }
    return max_id + 1;
}

bool HotelManagement::username_exists(string username){
    for (auto user:users){
        if(user->get_username() == username)
            return true;
    }
    return false;
}

bool HotelManagement::is_number(string str){
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

bool HotelManagement::authorization_confirmation(int file_descriptor){
    for (auto user:users){
        if(user->get_user_fd() == file_descriptor)
            return user->is_signed_in();
    }
    return false;
}

nlohmann::json HotelManagement::handle_request(nlohmann::json request , int user_fd){
    // TODO
    // handel request.size() == 0 in server.cpp file
    nlohmann::json response;
    string command = request["command"];

    if (command == "signup"){
        int id = create_new_user_id();
        if (username_exists(request["username"])){
            // send error message to client
            // CODE 451: username already exists
            response["status"] = 451;
            return response;
        }
        User* user = new User(id, request["username"]);
        user->set_user_fd(user_fd);
        users.push_back(user);

        // CODE 311: user created successfully
        response["status"] = 311;
        return response;
    }

    else if (command == "change_info") {
        // check if balance is a number
        if (!is_number(request["balance"])) {
            // send error message to client
            // CODE 503: error in input arguments
            response["status"] = 503;
            response["message"] = "balance has to be a number";
            return response;
        }
        
        // check if age phone_number is a number
        if (!is_number(request["phone_number"])) {
            // send error message to client
            // CODE 503: error in input arguments
            // delete user

            response["status"] = 503;
            response["message"] = "phone number has to be a number";
            return response;
        }

        User* user = get_user_by_username(request["username"]);
        if (user == NULL) {
            // send error message to client
            // CODE 430: user not found
            response["status"] = 430;
            return response;
        }

        user->set_password(request["password"]);
        string balance = request["balance"];
        user->set_balance(stoi(balance));
        user->set_phone(request["phone_number"]);
        user->set_address(request["address"]);

        // CODE 231: user info changed successfully

        user->show_info();

        response["status"] = 231;
        return response;
    }

    else if(command == "signin" && request.size() == 3){
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
    if(command == "1" && request.size() == 1){                // 5.1 : view user information
        current_user->show_info();
    }
    else if(command == "2" && request.size() == 1){                // 5.2 : view all users
        if(current_user->_is_admin() == false){
            // Error Handler -> 503 error
        }
        for (auto user:users){
            user->show_info();
        }
    }
    else if(command == "3" && request.size() == 1){                // 5.3: view all rooms
        for (auto room:rooms){
            room->show_info();
        }
    }
    else if(command == "4" && request.size() == 6){                // 5.4:
        
    }
    else if(command == "5" && request.size() == 1){                // 5.5
    }
    else if(command == "6" && request.size() == 1){                // 5.6
    }
    else if(command == "7" && request.size() == 1){                // 5.7
    }
    else if(command == "8" && request.size() == 1){                // 5.8
    }
    else if(command == "9" && request.size() == 1){                // 5.9
    }
    else if(command == "0" && request.size() == 1){                // 5.10
    }

    /*
    To DO: Add other commands
    */
    else{
        // Error Handler -> 503 error
    }
    return "OK\n";
}
