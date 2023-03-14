#include "date.hpp"

Date::Date() {
    year = 1;
    month = 1;
    day = 1;
}

Date::Date(int _year, int _month, int _day) {
    if (_year >= 1) {
        if (_month >= 1 && _month <= 12) {
            if (_day >= 1 && _day <= 31) {
                year = _year;
                month = _month;
                day = _day;
                date = date::year_month_day(date::year(_year) / date::month(_month) / date::day(_day));
                return;
            }
        }
    }

    // handle error. throw exception or simply print error message?
    
}

Date::~Date() {
    // TODO
}

void Date::set_year(int _year) {
    if (_year >= 1) {
        year = _year;
    } else {
        // handle error. throw exception or simply print error message?
    }
}

void Date::set_month(int _month) {
    if (_month >= 1 && _month <= 12) {
        month = _month;
    } else {
        // handle error. throw exception or simply print error message?
    }
}

void Date::set_day(int _day) {
    if (_day >= 1 && _day <= 31) {
        day = _day;
    } else {
        // handle error. throw exception or simply print error message?
    }
}

int Date::get_year(){return year;}

int Date::get_month(){return month;}

int Date::get_day(){return day;}

date::year_month_day Date::get_date(){return date;}

int Date::get_days_since_epoch(){
    return date::sys_days(this->date).time_since_epoch() / date::days{1};
}