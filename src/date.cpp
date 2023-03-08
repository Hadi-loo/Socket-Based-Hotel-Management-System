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
