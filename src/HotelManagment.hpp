#ifndef _HOTEL_HPP_
#define _HOTEL_HPP_

#include <string>
#include <vector>
#include "user.hpp"
#include "reservation.hpp"
#include "room.hpp"
#include "date.hpp"

using namespace std;


class HotelManagment {
private:
    vector <User*> users;
    vector <Reservation*> reservations;
    vector <Room*> rooms;
    Date current_date;
    string server_ip;
    int server_port;
    
public:
    HotelManagment();
    ~HotelManagment();

    void set_server_ip(string server_ip);
    void set_server_port(int server_port);

    void add_user(User* user);
    void add_users(vector<User*> users);

    void add_room(Room* room);
    void add_rooms(vector<Room*> rooms);
    
    void add_reservation(Reservation* reservation);
    void add_reservations(vector<Room*> reservations);

};


#endif