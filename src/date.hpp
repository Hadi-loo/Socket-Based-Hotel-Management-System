#ifndef _DATE_HPP_
#define _DATE_HPP_

using namespace std;

class Date {
private:
    int year;
    int month;
    int day;
    
public:
    Date();
    Date(int year, int month, int day);
    ~Date();
    void set_year(int year);
    void set_month(int month);
    void set_day(int day);

};

#endif