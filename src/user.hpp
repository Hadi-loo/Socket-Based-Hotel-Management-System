#ifndef _USER_HPP_
#define _USER_HPP_

#include <string>

using namespace std;

class User {
private:
    int id;
    string username;
    string password;
    bool is_admin;
    int balance;
    string phone;
    string address;

public:
    User(int id, string username, string password, bool is_admin, int balance, string phone, string address);
    User(int id, string username, string password, bool is_admin);
    

};

#endif