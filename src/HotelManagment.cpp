#include "HotelManagment.hpp"


HotelManagment::HotelManagment(vector <User*> _users , vector <Reservation*> _reserves , vector<Room*> _rooms , string _server_ip , int _server_port){
    users = _users;
    reserves = _reserves;
    rooms = _rooms;
    server_ip = _server_ip;
    server_port = _server_port;
}





