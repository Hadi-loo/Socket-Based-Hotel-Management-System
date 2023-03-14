#ifndef _DATE_HPP_
#define _DATE_HPP_

#include "date.h"

using namespace std;

class Date {
private:
    int year;
    int month;
    int day;
    date::year_month_day date;
    
public:
    Date();
    Date(int year, int month, int day);
    ~Date();
    void set_year(int year);
    void set_month(int month);
    void set_day(int day);
    int get_year();
    int get_month();
    int get_day();
    int get_days_since_epoch();
    date::year_month_day get_date();

};

#endif