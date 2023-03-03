#include "room.hpp"

Room::Room(int id, int max_capacity, int available_capacity, int price, bool is_available, vector<Reservation*> reservations) {
    this->id = id;
    this->max_capacity = max_capacity;
    this->available_capacity = available_capacity;
    this->price = price;
    this->is_available = is_available;
    this->reservations = reservations;
}