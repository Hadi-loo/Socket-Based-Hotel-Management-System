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
#include "defs.hpp"
#include "parser.hpp"
#include "logger.hpp"
#include "HotelManagement.hpp"
#include "json.hpp"
using namespace std;


int setupServer(int port , string ip_address) {
    const char* ip = ip_address.c_str();
    struct sockaddr_in address;
    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    int is_ok;
    is_ok = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (is_ok < 0) {
        cout << RED << "Error: " << RESET << "Could not bind server to port " << port << endl;
        exit(1);
    }
    listen(server_fd, 4);

    return server_fd;
}

int acceptClient(int server_fd) {
    int client_fd;
    struct sockaddr_in client_address;
    int address_len = sizeof(client_address);
    client_fd = accept(server_fd, (struct sockaddr *)&client_address, (socklen_t*) &address_len);

    return client_fd;
}


int main(int argc, char const *argv[]) {
    int server_fd, new_socket, max_sd;
    
    Parser server_parser(CONFIGS_PATH);
    Logger server_logger(LOGS_PATH);
    HotelManagement hotel_managment;
    nlohmann::json request, response;
    
    string server_ip_address;
    int server_port;
    server_parser.parse_config(CONFIG_FILE_NAME, server_ip_address, server_port);
    
    char buffer[MAX_BUFFER_SIZE] = {0};
    fd_set master_set, working_set;
    server_fd = setupServer(server_port , server_ip_address);

    FD_ZERO(&master_set);
    max_sd = server_fd;
    FD_SET(server_fd, &master_set);

    hotel_managment.set_server_ip(server_ip_address);
    hotel_managment.set_server_port(server_port);

    vector<User*> users = server_parser.parse_users(USERSINFO_FILE_NAME);
    vector<Room*> rooms = server_parser.parse_rooms(ROOMSINFO_FILE_NAME);
    hotel_managment.add_users(users);
    hotel_managment.add_rooms(rooms);
    hotel_managment.add_reservations(rooms);

    hotel_managment.get_starting_date(server_parser);

    string log_message = "Server is up and running on " + server_ip_address + ":" + to_string(server_port) + "...\n";
    server_logger.log(SERVER_LOG_FILE_NAME, log_message);
    cout << log_message;

    hotel_managment.update_reservations();
    


    while (1) {
        working_set = master_set;
        select(max_sd + 1, &working_set, NULL, NULL, NULL);
        for (int i = 0; i <= max_sd; i++) {
            if (FD_ISSET(i, &working_set)) {
                if (i == server_fd) {                                       // new client
                    new_socket = acceptClient(server_fd);
                    FD_SET(new_socket, &master_set);
                    if (new_socket > max_sd)
                        max_sd = new_socket;
                    log_message = "New client connected with fd = " + to_string(new_socket) + "\n";
                    server_logger.log(SERVER_LOG_FILE_NAME, log_message);
                    cout << log_message;
                }
                
                else {                                                      // client sending msg
                    int bytes_received;
                    bytes_received = recv(i , buffer, MAX_BUFFER_SIZE, 0);
                    if (bytes_received == 0) {                              // client closed connection
                        // TODO: handle client disconnection
                        hotel_managment.user_disconnected(i);
                        User* user = hotel_managment.get_user_by_fd(i);
                        if (user != NULL) {
                            user->sign_out();
                            log_message = "User " + user->get_username() + " disconnected\n";
                            server_logger.log(user->get_username() + ".log", log_message);
                        } else {
                            log_message = "Client with fd = " + to_string(i) + " disconnected\n";
                        }
                        server_logger.log(SERVER_LOG_FILE_NAME, log_message);
                        cout << log_message;
                        close(i);
                        FD_CLR(i, &master_set);
                        continue;
                    }

                    // this section is for debugging and should be removed
                    log_message = "Received message from client fd = " + to_string(i) + ": " + buffer + "\n";
                    server_logger.log(SERVER_LOG_FILE_NAME, log_message);
                    cout << log_message;

                    request = nlohmann::json::parse(buffer);
                    response = hotel_managment.handle_request(request, i);

                    User* user = hotel_managment.get_user_by_fd(i);
                    if (user != NULL) {
                        log_message = "Sending response to user " + user->get_username() + ": ";
                    } else {
                        log_message = "Sending response to client fd = " + to_string(i) + ": ";
                    }

                    if (response.find("message") != response.end()) {
                        log_message += string(response["message"]) + "\n";
                    } else {
                        log_message = response.dump() + "\n";
                    }
                    server_logger.log(SERVER_LOG_FILE_NAME, log_message);
                    if (user != NULL) {
                        server_logger.log(user->get_username() + ".log", log_message);
                    }
                    cout << "Sending response to client fd = " << i << ": " << response.dump() << endl;

                    // update json files before sending response
                    server_parser.rewrite_users_file(USERSINFO_FILE_NAME, hotel_managment.get_users());
                    server_parser.rewrite_rooms_file(ROOMSINFO_FILE_NAME, hotel_managment.get_rooms());

                    send(i, response.dump().c_str(), response.dump().length(), 0);
                    memset(buffer, 0, MAX_BUFFER_SIZE);
                }
            }
        }
    }

    return 0;
}