#ifndef _HOTEL_HPP_
#define _HOTEL_HPP_

#include <string>
#include <vector>
#include <iostream>
#include "user.hpp"
#include "reservation.hpp"
#include "room.hpp"
#include "date.hpp"
#include "sha2.h"
#include "json.hpp"
#include "defs.hpp"
#include "parser.hpp"

using namespace std;


class HotelManagement {
private:
    vector <User*> users;
    vector <Reservation*> reservations;
    vector <Room*> rooms;
    Date current_date;
    string server_ip;
    int server_port;
    
public:
    HotelManagement();
    ~HotelManagement();

    void set_server_ip(string server_ip);
    void set_server_port(int server_port);

    void add_user(User* user);
    void add_users(vector<User*> users);
    void remove_user_by_id(int id);
    void remove_user_by_username(string username);

    void add_room(Room* room);
    void add_rooms(vector<Room*> rooms);
    
    void add_reservation(Reservation* reservation);
    void add_reservations(vector<Room*> reservations);
    
    void get_starting_date(Parser &server_parser);
    void update_reservations();

    vector<User*> get_users();
    vector<Room*> get_rooms();

    User* get_user_by_id(int id);
    User* get_user_by_username(string username);
    User* get_user_by_fd(int fd);
    
    Room* get_room_by_id(int id);

    int create_new_user_id(void);
    bool username_exists(string username);
    bool is_number(string str);
    
    bool authorization_confirmation(int file_descriptor);
    void user_disconnected(int file_descriptor);

    nlohmann::json handle_request(nlohmann::json request, int user_fd);

    nlohmann::json handle_signup(nlohmann::json request);
    nlohmann::json handle_signup_info(nlohmann::json request);
    nlohmann::json handle_signin(nlohmann::json request, int user_fd);
    nlohmann::json handle_signout(nlohmann::json request, int user_fd);
    nlohmann::json handle_get_user_info(nlohmann::json request, int user_fd);
    nlohmann::json handle_get_all_users(nlohmann::json request, int user_fd);
    nlohmann::json handle_get_rooms_info(nlohmann::json request, int user_fd);
    nlohmann::json handle_edit_info(nlohmann::json request, int user_fd);
    nlohmann::json handle_booking(nlohmann::json request, int user_fd);

    // bool check_room_availability(Room* room, Date check_in_date, Date check_out_date , int &num_of_beds);

    nlohmann::json handle_add_room(nlohmann::json request, int user_fd);
    nlohmann::json handle_modify_room(nlohmann::json request, int user_fd);
    nlohmann::json handle_delete_room(nlohmann::json request, int user_fd);
    nlohmann::json handle_pass_day(nlohmann::json request, int user_fd);
    nlohmann::json handle_leave_room(nlohmann::json request, int user_fd);
    nlohmann::json handle_get_user_reservations(nlohmann::json request, int user_fd);
    nlohmann::json handle_cancel_reservation(nlohmann::json request, int user_fd);


};


#endif