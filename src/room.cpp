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

Room::~Room() {
    for (int i = 0; i < reservations.size(); i++) {
        delete reservations[i];
    }
}

int Room::get_id(){
    return id;
}

int Room::get_max_capacity() {
    return max_capacity;
}

int Room::get_price() {
    return price;
}

bool Room::is__available() {
    return is_available;
}

vector<Reservation*> Room::get_reservations(){
    return reservations;
}

void Room::set_max_capacity(int _max_capacity) {
    available_capacity += _max_capacity - max_capacity;
    is_available = (available_capacity > 0);
    max_capacity = _max_capacity;
}

void Room::set_price(int _price) {
    price = _price;
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

void Room::add_reservation(Reservation* reservation){
    reservations.push_back(reservation);
}

bool Room::check_room_availability(Date check_in_date, Date check_out_date , int &num_of_beds) {

    int day_checkIn = check_in_date.get_days_since_epoch();
    int day_checkOut = check_out_date.get_days_since_epoch();

    for (int day = day_checkIn ; day <= day_checkOut ; day++){
        int capacity = max_capacity - num_of_beds;

        for (auto reservation : reservations){
            if(reservation->get_check_in_date().get_days_since_epoch() <= day && reservation->get_check_out_date().get_days_since_epoch() > day)
                capacity -= reservation->get_num_of_beds();
            if(capacity < 0)
                return false;
        }

        if(capacity < 0)
            return false;
    }
    return true;
}

void Room::first_last_reservation_date(int &first_date, int &last_date) {
    int first = -1;
    int last = -1;
    for (auto reservation : reservations) {
        if (first == -1 || reservation->get_check_in_date().get_days_since_epoch() < first) {
            first = reservation->get_check_in_date().get_days_since_epoch();
        }
        if (last == -1 || reservation->get_check_out_date().get_days_since_epoch() > last) {
            last = reservation->get_check_out_date().get_days_since_epoch();
        }
    }
    first_date = first;
    last_date = last;
}

int Room::maximum_people_in_room(Date current_date) {
    int first, last;
    first_last_reservation_date(first, last);
    int max = 0;
    if (current_date.get_days_since_epoch() >= first) {
        first = current_date.get_days_since_epoch();
    }
    for (int day = first; day <= last; day++) {
        int people = 0;
        for (auto reservation : reservations) {
            if (reservation->get_check_in_date().get_days_since_epoch() <= day && reservation->get_check_out_date().get_days_since_epoch() > day) {
                people += reservation->get_num_of_beds();
            }
        }
        if (people > max) {
            max = people;
        }
    }
    return max;
}

void Room::update_room_status(Date current_date){
    available_capacity = max_capacity;
    for (auto reservation : reservations){
        if(current_date.get_date() >= reservation->get_check_in_date().get_date()
            && current_date.get_date() < reservation->get_check_out_date().get_date()){
                available_capacity -= reservation->get_num_of_beds();
            }
    }
    if(available_capacity == 0)
        is_available = false;
    else
        is_available = true;
}


void Room::remove_reservation(Reservation* reservation){
    for (int i = 0; i < reservations.size(); i++) {
        if (reservations[i] == reservation) {
            reservations.erase(reservations.begin() + i);
            break;
        }
    }
}


