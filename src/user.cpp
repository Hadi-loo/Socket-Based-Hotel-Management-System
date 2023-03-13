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

string User::get_username() {
    return username;
}

string User::get_password() {
    return password;
}

bool User::is__admin() {
    return is_admin;
}

int User::get_balance() {
    return balance;
}

string User::get_phone() {
    return phone;
}

string User::get_address() {
    return address;
}

int User::get_user_fd() {
    return user_fd;
}

bool User::is_signed_in() {
    return signed_in;
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

string User::get_info() {
    string info = "";
    info += "---------------" + username + "---------------\n";
    info += "ID: " + to_string(id) + "\n";
    info += "Username: " + username + "\n";
    info += "Password: " + password + "\n";
    if (!is_admin) {        
        info += "Balance: " + to_string(balance) + "\n";
        info += "Phone Number: " + phone + "\n";
        info += "Address: " + address + "\n";
        info += "You are one of our beloved customers :)\n";
    } else {
        info += "You are one of our admins\n";
    } 
    info += "---------------------------------------\n";
    return info;
}


void User::sign_in(int _user_fd) {
    signed_in = true;
    user_fd = _user_fd;
}

void User::sign_out() {
    signed_in = false;
    user_fd = -1;
}


