#include "user.hpp"
#include <iostream>

User::User(int _id, string _username, string _password, bool _is_admin, int _balance, string _phone, string _address) {
    id = _id;
    username = _username;
    password = _password;
    is_admin = _is_admin;
    balance = _balance;
    phone = _phone;
    address = _address;
}

User::User(int _id, string _username, string _password, bool _is_admin) {
    id = _id;
    username = _username;
    password = _password;
    is_admin = _is_admin;
}

User::User(int _id, string _username) {
    id = _id;
    username = _username;
    is_admin = false;
}

int User::get_id() {
    return id;
}

void User::set_password(string _password) {
    password = _password;
}

void User::set_balance(int _balance) {
    balance = _balance;
}

void User::set_phone(string _phone) {
    phone = _phone;
}

void User::set_address(string _address) {
    address = _address;
}

void User::show_info() {
    cout << "---------------User Info---------------" << endl;
    cout << "ID: " << id << endl;
    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;
    cout << "You are " << (is_admin ? "" : "not ") << "an admin" << endl;
    if (!is_admin) {        
        cout << "Balance: " << balance << endl;
        cout << "Phone Number: " << phone << endl;
        cout << "Address: " << address << endl;
    }
    cout << "---------------------------------------" << endl;
}