#ifndef _RESERVATION_HPP_
#define _RESERVATION_HPP_

#include <string>
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

    void show_info();
    string get_info();
    Date get_check_in_date(){return check_in_date;}
    Date get_check_out_date(){return check_out_date;}
    int get_num_of_beds(){return number_of_beds;}
};


#endif