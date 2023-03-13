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
    string get_username(){return username;}
    string get_password(){return password;}

    void show_info();

    void sign_in(int _user_fd);
    void sign_out(){signed_in = false;}
    bool is_signed_in(){return signed_in;}
    void set_user_fd(int _user_fd){user_fd = _user_fd;}
    int get_user_fd(){return user_fd;}
    bool _is_admin(){return is_admin;}
};

#endif