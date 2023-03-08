#include "user.hpp"
#include <iostream>

User::User(int _id, string _username, string _password, bool _is_admin, int _balance, string _phone, string _address) {
    id = id;
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

void User::show_info() {
    cout << "ID: " << id << endl;
    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;
    cout << "You are " << (is_admin ? "" : "not ") << "an admin" << endl;
    if (!is_admin) {        
        cout << "Balance: " << balance << endl;
        cout << "Phone Number: " << phone << endl;
        cout << "Address: " << address << endl;
    }
}