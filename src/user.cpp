#include "user.hpp"

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