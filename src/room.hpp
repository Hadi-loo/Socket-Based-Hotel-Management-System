#ifndef _ROOM_HPP_
#define _ROOM_HPP_

#include <string>
#include <vector>

using namespace std;

// forward declaration. should it be here?
class Reservation;

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
    
};

#endif