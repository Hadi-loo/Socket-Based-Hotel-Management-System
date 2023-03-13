#include "room.hpp"
#include "iostream"

using namespace std;

Room::Room(int _id, int _max_capacity, int _available_capacity, int _price, bool _is_available, vector<Reservation*> _reservations) {
    id = _id;
    max_capacity = _max_capacity;
    available_capacity = _available_capacity;
    price = _price;
    is_available = _is_available;
    reservations = _reservations;
}

vector<Reservation*> Room::get_reservations(){
    return reservations;
}

void Room::show_info(){
    cout << "ID: " << id << endl;
    cout << "Max Capacity: " << max_capacity << endl;
    cout << "Available Capacity: " << available_capacity << endl;
    cout << "Price: " << price << endl;
    cout << "Is Available: " << (is_available ? "Yes" : "No") << endl;
    cout << "Reservations: " << endl;
    for (int i = 0; i < reservations.size(); i++) {
        cout << "Reservation " << i + 1 << ":" << endl;
        reservations[i]->show_info();
    }
}

string Room::get_info(){
    string info = "";
    info += "---------------Room" + to_string(id) + "---------------\n";
    info += "ID: " + to_string(id) + "\n";
    info += "Max Capacity: " + to_string(max_capacity) + "\n";
    info += "Available Capacity: " + to_string(available_capacity) + "\n";
    info += "Price: " + to_string(price) + "\n";
    if (is_available) {
        info += "This room is available\n";
    } else {
        info += "This room is unavailable\n";
    }
    info += "Reservations: \n";
    for (int i = 0; i < reservations.size(); i++) {
        info += "____________Reservation" + to_string(i+1) + "____________\n";
        info += reservations[i]->get_info();
    }
    info += "----------------------------------------\n";
    return info;
}

