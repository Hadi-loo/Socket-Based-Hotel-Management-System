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
    vector <Reservation*> reserves;
    vector <Room*> rooms;
    Date current_date;
    string server_ip;
    int server_port;
    
public:
    HotelManagment();
    ~HotelManagment();
    HotelManagment(vector <User*> _users , vector <Reservation*> _reserves , vector<Room*> _rooms , string _server_ip , int _server_port);

    void set_server_ip(string server_ip);
    void set_server_port(int server_port);

    void add_user(User* user);
    void add_users(vector <User*> users);
    

};


#endif