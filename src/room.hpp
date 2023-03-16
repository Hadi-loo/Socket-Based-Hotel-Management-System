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
    int get_max_capacity();
    int get_price();
    bool is__available();
    vector<Reservation*> get_reservations();

    void set_max_capacity(int max_capacity);
    void set_price(int price);

    void show_info();
    string get_info();
    
    void add_reservation(Reservation* reservation);
    bool check_room_availability(Date check_in_date, Date check_out_date , int &num_of_beds);
    void first_last_reservation_date(int &first_date, int &last_date);
    int maximum_people_in_room(Date current_date);
    void update_room_status(Date current_date);

};

#endif