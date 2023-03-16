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
    int payed_money = 0;
    Date check_in_date;
    Date check_out_date;

public:
    Reservation(int costumer_id, int room_id, int number_of_beds, int payed_money, Date check_in_date, Date check_out_date);
    Reservation(int costumer_id, int room_id, int number_of_beds, Date check_in_date, Date check_out_date);
    ~Reservation();

    int get_costumer_id();
    int get_room_id();
    int get_num_of_beds();
    int get_payed_money();
    Date get_check_in_date();
    Date get_check_out_date();
    

    void show_info();
    string get_info();
    
};


#endif