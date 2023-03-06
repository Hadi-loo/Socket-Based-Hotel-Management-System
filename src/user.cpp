#include "user.hpp"
#include <iostream>

User::User(int id, string username, string password, bool is_admin, int balance, string phone, string address) {
    this->id = id;
    this->username = username;
    this->password = password;
    this->is_admin = is_admin;
    this->balance = balance;
    this->phone = phone;
    this->address = address;
}

User::User(int id, string username, string password, bool is_admin) {
    this->id = id;
    this->username = username;
    this->password = password;
    this->is_admin = is_admin;
}

void User::show_info() {
    cout << "ID: " << this->id << endl;
    cout << "Username: " << this->username << endl;
    cout << "Password: " << this->password << endl;
    cout << "You are " << (this->is_admin ? "" : "not ") << "an admin" << endl;
    if (!this->is_admin) {        
        cout << "Balance: " << this->balance << endl;
        cout << "Phone Number: " << this->phone << endl;
        cout << "Address: " << this->address << endl;
    }
}