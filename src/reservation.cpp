#include "reservation.hpp"

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