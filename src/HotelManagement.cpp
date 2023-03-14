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

User* HotelManagement::get_user_by_fd(int fd){
    for (int i = 0; i < users.size(); i++){
        if (users[i]->get_user_fd() == fd)
            return users[i];
    }
    return NULL;
}

Room* HotelManagement::get_room_by_id(int id){
    for (int i = 0 ; i < rooms.size() ; i++){
        if (rooms[i]->get_id() == id)
            return rooms[i];
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

Date convert_string_to_date(string &date , Parser &parser){
    vector<string> date_parts = parser.split_string(date , '-');
    int day = stoi(date_parts[0]);
    int month = stoi(date_parts[1]);
    int year = stoi(date_parts[2]);
    return Date(year , month , day);
}

bool check_room_availability(Room* room, Date check_in_date, Date check_out_date , int &num_of_beds){
    int day_checkIn = check_in_date.get_days_since_epoch();
    int day_checkOut = check_out_date.get_days_since_epoch();
    for (int day = day_checkIn ; day <= day_checkOut ; day++){
        int capacity = room->get_max_capacity();
        for (auto reservation:room->get_reservations()){
            if(reservation->get_check_in_date().get_days_since_epoch() <= day && reservation->get_check_out_date().get_days_since_epoch() >= day)
                capacity -= num_of_beds;
            if(capacity < 0)
                return false;
        }
        if(capacity < 0)
            return false;
    }
    return true;
}


nlohmann::json HotelManagement::handle_request(nlohmann::json request , int user_fd){
    // TODO
    // handel request.size() == 0 in server.cpp file
    nlohmann::json response;
    string command = request["command"];

    if (command == "signup") {
        return handle_signup(request);
    }

    else if (command == "signup_info") {
        return handle_signup_info(request);
    }

    else if (command == "signin") {
        return handle_signin(request, user_fd);
    }

    else if (command == "logout") {
        return handle_signout(request, user_fd);
    }

    else if (command == "get_user_info") {
        return handle_get_user_info(request, user_fd);
    }

    else if (command == "get_all_users") {
        return handle_get_all_users(request, user_fd);
    }

    else if (command == "get_rooms_info") {
        return handle_get_rooms_info(request, user_fd);
    }

    else if (command == "edit_info") {
        return handle_edit_info(request, user_fd);
    }
    
    else if (command == "book_room"){
        return handle_booking(request, user_fd);
    }

    else if (command == "add_room") {
        return handle_add_room(request, user_fd);
    }

    // TODO: Add other commands

    else {
        // Error Handler -> 503 error
    }

    return nlohmann::json({"status", 100});
}

nlohmann::json HotelManagement::handle_signup(nlohmann::json request) {
    nlohmann::json response;
    int id = create_new_user_id();
    if (username_exists(request["username"])){
        // send error message to client
        // CODE 451: username already exists
        response["status"] = 451;
        response["message"] = "username already exists";
        return response;
    }
    User* user = new User(id, request["username"]);
    users.push_back(user);

    // CODE 311: user created successfully
    response["status"] = 311;
    response["message"] = "user created successfully";
    return response;
}

nlohmann::json HotelManagement::handle_signup_info(nlohmann::json request) {
    nlohmann::json response;
    User* user = get_user_by_username(request["username"]);
    if (user == NULL) {
        // send error message to client
        // CODE 430: user not found
        response["status"] = 430;
        response["message"] = "user not found";
        return response;
    }
    
    // check if balance is a number
    if (!is_number(request["balance"])) {
        // send error message to client
        // CODE 503: error in input arguments
        // delete user
        remove_user_by_username(request["username"]);
        response["status"] = 503;
        response["message"] = "balance has to be a number";
        return response;
    }
    
    // check if age phone_number is a number
    if (!is_number(request["phone_number"])) {
        // send error message to client
        // CODE 503: error in input arguments
        // delete user
        remove_user_by_username(request["username"]);
        response["status"] = 503;
        response["message"] = "phone number has to be a number";
        return response;
    }

    user->set_password(request["password"]);
    string balance = request["balance"];
    user->set_balance(stoi(balance));
    user->set_phone(request["phone_number"]);
    user->set_address(request["address"]);

    // send success message to client
    // CODE 231: user info submitted successfully

    user->show_info();

    response["status"] = 231;
    response["message"] = "user's information submitted successfully";
    return response;
} 

nlohmann::json HotelManagement::handle_signin(nlohmann::json request, int user_fd) {
    nlohmann::json response;
    User* user = get_user_by_username(request["username"]);

    if (user != NULL) {
        if (request["password"] == user->get_password()){
            user->sign_in(user_fd);
            // CODE 230: user signed in successfully
            response["status"] = 230;
            response["message"] = "user signed in successfully";
            response["is_admin"] = user->is__admin();
            return response;
        } else {
            // CODE 430: password is incorrect
            response["status"] = 430;
            response["message"] = "password is incorrect";
            return response;
        }
    }

    // CODE 430: user not found
    response["status"] = 430;
    response["message"] = "user not found";
    return response;
}

nlohmann::json HotelManagement::handle_signout(nlohmann::json request, int user_fd) {
    nlohmann::json response;
    User* user = get_user_by_fd(user_fd);

    if (user != NULL) {
        user->sign_out();
        // CODE 201: user signed out successfully
        response["status"] = 201;
        response["message"] = "user signed out successfully";
        return response;
    }

    // CODE 404: user not found
    response["status"] = 404;
    response["message"] = "user not found";
    return response;
}

nlohmann::json HotelManagement::handle_get_user_info(nlohmann::json request, int user_fd) {
    nlohmann::json response;
    User* user = get_user_by_fd(user_fd);

    if (user != NULL) {
        response["status"] = 100;
        response["message"] = "user info retrieved successfully";
        response["id"] = user->get_id();
        response["username"] = user->get_username();
        response["balance"] = user->get_balance();
        response["phone_number"] = user->get_phone();
        response["address"] = user->get_address();
        response["summary"] = user->get_info();
        return response;
    }

    // CODE 404: user not found
    response["status"] = 404;
    response["message"] = "user not found";
    return response;
}

nlohmann::json HotelManagement::handle_get_all_users(nlohmann::json request, int user_fd) {
    nlohmann::json response;
    
    if (users.empty()) {
        // CODE 404: user not found
        response["status"] = 404;
        response["message"] = "users not found";
        return response;
    }

    else {
        response["status"] = 100;
        response["message"] = "all users info retrieved successfully";
        for (auto user:users){
            response["summary"].push_back(user->get_info());
        }
        return response;
    }

}

nlohmann::json HotelManagement::handle_get_rooms_info(nlohmann::json request, int user_fd) {
    nlohmann::json response;

    if (rooms.empty()) {
        // CODE 404: user not found
        response["status"] = 404;
        response["message"] = "rooms not found";
        return response;
    }

    else {
        response["status"] = 100;
        response["message"] = "all rooms info retrieved successfully";
        for (auto room:rooms){
            response["summary"].push_back(room->get_info());
        }
        return response;
    }
}

nlohmann::json HotelManagement::handle_edit_info(nlohmann::json request, int user_fd) {
    nlohmann::json response;
    User* user = get_user_by_fd(user_fd);

    if (user != NULL) {
        bool password_exists = request.find("password") != request.end();
        bool phone_exists = request.find("phone_number") != request.end();
        bool address_exists = request.find("address") != request.end();

        if (phone_exists) {
            if (!is_number(request["phone_number"])) {
                // send error message to client
                // CODE 503: Bad sequence of commands
                response["status"] = 503;
                response["message"] = "phone number has to be a number";
                return response;
            }
        }

        if (password_exists) {
            user->set_password(request["password"]);
        }
        if (phone_exists) {
            user->set_phone(request["phone_number"]);
        }
        if (address_exists) {
            user->set_address(request["address"]);
        }
        
        // CODE 312: Information was changed successfully
        // send success message to client
        response["status"] = 312;
        response["message"] = "Information was changed successfully";
        return response;

    }

    // CODE 404: user not found
    response["status"] = 404;
    response["message"] = "user not found";
    return response;
}

nlohmann::json HotelManagement::handle_add_room(nlohmann::json request, int user_fd) {
    nlohmann::json response;
    User* user = get_user_by_fd(user_fd);

    if (user != NULL) {
        if (user->is__admin()) {
            // check if room_number is a number
            if (!is_number(request["room_id"])) {
                // send error message to client
                // CODE 503: error in input arguments
                response["status"] = 503;
                response["message"] = "room number has to be a number";
                return response;
            }

            // check if room_number is a number
            if (!is_number(request["price"])) {
                // send error message to client
                // CODE 503: error in input arguments
                response["status"] = 503;
                response["message"] = "room price has to be a number";
                return response;
            }

            // check if room_number is a number
            if (!is_number(request["max_capacity"])) {
                // send error message to client
                // CODE 503: error in input arguments
                response["status"] = 503;
                response["message"] = "room capacity has to be a number";
                return response;
            }

            string room_id = request["room_id"];
            string max_capacity = request["max_capacity"];
            string price = request["price"];

            // check if room_number exists
            for (auto room:rooms) {
                if (room->get_id() == stoi(room_id)) {
                    // send error message to client
                    // CODE 111: room number already exists
                    response["status"] = 111;
                    response["message"] = "room number already exists";
                    return response;
                }
            }

            Room* room = new Room(stoi(room_id), stoi(max_capacity), stoi(max_capacity), stoi(price), true, vector<Reservation*>());
            rooms.push_back(room);

            // CODE 104: Room added successfully
            // send success message to client
            response["status"] = 104;
            response["message"] = "Room added successfully";
            return response;
        }
        else {
            // CODE 403: user is not admin
            response["status"] = 403;
            response["message"] = "user is not admin";
            return response;
        }
    }

    // CODE 404: user not found
    response["status"] = 404;
    response["message"] = "user not found";
    return response;
}


nlohmann::json HotelManagement::handle_booking(nlohmann::json request, int user_fd){
    nlohmann::json response;
    Room* room = get_room_by_id(request["room_num"]);

    if (room != NULL){
        Parser parser(CONFIGS_PATH);
        string _check_in_date = request["check_in_date"];
        string _check_out_date = request["check_out_date"];
        Date check_in_date = convert_string_to_date(_check_in_date , parser);
        Date check_out_date = convert_string_to_date(_check_out_date , parser);
        int num_of_beds = request["num_of_beds"];

        if (check_room_availability(room , check_in_date , check_out_date , num_of_beds) == false){
            response["status"] = 109;
            response["message"] = "The room capacity is full.";
            return response;
        }
        
        User* user = get_user_by_fd(user_fd);
        if(user->get_balance() >= room->get_price()){
            user->set_balance(user->get_balance() - room->get_price());
            Reservation* reservation = new Reservation(user->get_id() , room->get_id() , num_of_beds , check_in_date , check_out_date);
            reservations.push_back(reservation);
            room->add_reservation(reservation);
            response["status"] = 100;
            response["message"] = "The room was booked successfully.";
            return response;
        }
        else{
            response["status"] = 108;
            response["message"] = "108: Your account balance is not enogh.";
            return response;
        }
    }

    response["status"] = 101;
    response["message"] = "The desired room was not found.";
    return response;
    
}