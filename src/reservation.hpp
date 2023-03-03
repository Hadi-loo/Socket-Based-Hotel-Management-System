#ifndef _RESERVATION_HPP_
#define _RESERVATION_HPP_

#include "date.hpp"

using namespace std;

class Reservation {
private:
    int costumer_id;
    int room_id;
    int number_of_beds;
    Date check_in_date;
    Date check_out_date;

public:
    Reservation(int costumer_id, int room_id, int number_of_beds, Date check_in_date, Date check_out_date);
    ~Reservation();

};


#endif