#include "date.hpp"

Date::Date() {
    this->year = 1;
    this->month = 1;
    this->day = 1;
}

Date::Date(int year, int month, int day) {
    if (year >= 1) {
        if (month >= 1 && month <= 12) {
            if (day >= 1 && day <= 31) {
                this->year = year;
                this->month = month;
                this->day = day;
                return;
            }
        }
    }

    // handle error. throw exception or simply print error message?
    
}

Date::~Date() {
    // TODO
}

void Date::set_year(int year) {
    if (year >= 1) {
        this->year = year;
    } else {
        // handle error. throw exception or simply print error message?
    }
}

void Date::set_month(int month) {
    if (month >= 1 && month <= 12) {
        this->month = month;
    } else {
        // handle error. throw exception or simply print error message?
    }
}

void Date::set_day(int day) {
    if (day >= 1 && day <= 31) {
        this->day = day;
    } else {
        // handle error. throw exception or simply print error message?
    }
}
