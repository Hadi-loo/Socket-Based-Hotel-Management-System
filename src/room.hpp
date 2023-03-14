#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include "reservation.hpp"
#include <string>
#include <vector>

using namespace std;

class Room {
private:
    int id;
    int max_capacity;
    int available_capacity;
    int price;
    bool is_available;
    vector<Reservation*> reservations;

public:
    Room(int id, int max_capacity, int available_capacity, int price, bool is_available, vector<Reservation*> reservations);

    int get_id();
    vector<Reservation*> get_reservations();

    void show_info();
    string get_info();
    int get_id(){return id;}
    int get_max_capacity(){return max_capacity;}
    int get_price(){return price;}
    void add_reservation(Reservation* reservation);
};

#endif