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
    Date(int _year, int _month, int _day);
    ~Date();
    void set_year(int _year);
    void set_month(int _month);
    void set_day(int _day);
    void set_date(int _year, int _month, int _day);
    void pass_day(int value);
    int get_year();
    int get_month();
    int get_day();
    int get_days_since_epoch();
    date::year_month_day get_date();
    string dmy_string();
    string ymd_string();
    
};

#endif