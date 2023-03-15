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
    int user_fd;
    bool signed_in;

public:
    User(int id, string username, string password, bool is_admin, int balance, string phone, string address);
    User(int id, string username, string password, bool is_admin);
    User(int id, string username);

    void set_password (string _password);
    void set_balance (int _balance);
    void set_phone (string _phone);
    void set_address (string _address);

    int get_id();
    string get_username();
    string get_password();
    bool is__admin();
    int get_balance();
    string get_phone();
    string get_address();
    int get_user_fd();
    bool is_signed_in();

    void show_info();
    string get_info();
    string get_full_info();

    void sign_in(int _user_fd);
    void sign_out();

};

#endif