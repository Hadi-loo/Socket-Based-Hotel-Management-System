#include "date.hpp"

Date::Date(int year, int month, int day) {
    if (year > 0) {
        if (month >= 1 && month <= 12) {
            if (day >= 0 && day <= 31) {
                this->year = year;
                this->month = month;
                this->day = day;
                return;
            }
        }
    }

    // handle error. throw exception or simply print error message?
    
}