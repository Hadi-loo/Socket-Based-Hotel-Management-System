#include "reservation.hpp"
#include "iostream"


Reservation::Reservation(int costumer_id, int room_id, int number_of_beds, Date check_in_date, Date check_out_date) {
    this->costumer_id = costumer_id;
    this->room_id = room_id;
    this->number_of_beds = number_of_beds;
    this->check_in_date = check_in_date;
    this->check_out_date = check_out_date;
}

Reservation::~Reservation() {
    // TODO
    
}

void Reservation::show_info(){
    cout << "Costumer ID: " << costumer_id << endl;
    cout << "Room ID: " << room_id << endl;
    cout << "Number of Beds: " << number_of_beds << endl;
    cout << "Check In Date: " << check_in_date.get_year() << "/" << check_in_date.get_month() << "/" << check_in_date.get_day() << endl;
    cout << "Check Out Date: " << check_out_date.get_year() << "/" << check_out_date.get_month() << "/" << check_out_date.get_day() << endl;
}

string Reservation::get_info(){
    string info = "";
    info += "Costumer ID: " + to_string(costumer_id) + "\n";
    info += "Room ID: " + to_string(room_id) + "\n";
    info += "Number of Beds: " + to_string(number_of_beds) + "\n";
    info += "Check In Date: " + to_string(check_in_date.get_year()) + "/" + to_string(check_in_date.get_month()) + "/" + to_string(check_in_date.get_day()) + "\n";
    info += "Check Out Date: " + to_string(check_out_date.get_year()) + "/" + to_string(check_out_date.get_month()) + "/" + to_string(check_out_date.get_day()) + "\n";
    return info;
}