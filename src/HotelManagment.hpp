#ifndef _HOTEL_HPP_
#define _HOTEL_HPP_

#include <string>
#include <vector>
#include "user.hpp"
#include "reservation.hpp"
#include "room.hpp"



using namespace std;


class HotelManagment {
private:
    vector <User*> users;
    vector <Reservation*> reserves;
    vector <Room*> rooms;
    string server_ip;
    int server_port;
    
public:
    HotelManagment(vector <User*> _users , vector <Reservation*> _reserves , vector<Room*> _rooms , string _server_ip , int _server_port);
};











#endif