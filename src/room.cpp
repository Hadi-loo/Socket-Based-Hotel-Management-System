#include "room.hpp"

Room::Room(int _id, int _max_capacity, int _available_capacity, int _price, bool _is_available, vector<Reservation*> _reservations) {
    id = _id;
    max_capacity = _max_capacity;
    available_capacity = _available_capacity;
    price = _price;
    is_available = _is_available;
    reservations = _reservations;
}