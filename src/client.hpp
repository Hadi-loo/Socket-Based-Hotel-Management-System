#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include "defs.hpp"
#include "parser.hpp"
#include "json.hpp"

using namespace std;

int connectServer(string host_name ,int port);
void authentication_menu(int server_fd, bool &logged_in, Parser &client_parser);
void main_menu(int server_fd, bool &logged_in, Parser &client_parser);
void show_main_menu();
void pretty_write(string message, string color);
bool handle_signup(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input);
bool handle_signin(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input, Parser &client_parser);
bool handle_signout(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input);
bool handle_show_user_info(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input);
bool handle_show_all_users(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input);

#endif
