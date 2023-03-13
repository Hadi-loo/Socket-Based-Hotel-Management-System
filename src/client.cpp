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

int connectServer(string host_name ,int port) {
    int fd;
    struct sockaddr_in server_address;
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = inet_addr(host_name.c_str());

    if (connect(fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) { // checking for errors
        printf("Error in connecting to server\n");
    }
    else
        printf("client Connected to the server\n");
    return fd;
}

void authentication_menu(int server_fd, Parser* client_parser) {
    cout << ">> ";
    string input;
    vector<string> parsed_input;
    cin >> input;
    parsed_input = client_parser->split_string(input, ' ');
    // switch case for signin, signup, exit



}

int main(int argc, char const *argv[]) {
    char buff[MAX_BUFFER_SIZE] = {0};
    vector<string> input;

    Parser client_parser(CONFIGS_PATH);
    string server_ip_address;
    int server_port;
    client_parser.parse_config(CONFIG_FILE_NAME, server_ip_address, server_port);
    int server_fd = connectServer(server_ip_address, server_port);
    bool logged_in = false;

    // UDP and select must be added

    while (1) {

        write(1, ">> ", 3);
        read(0, buff, MAX_BUFFER_SIZE);
        input = client_parser.split_string(buff, ' ');
        nlohmann::json request, response;
        
        if (input[0] == "signup") {
            
            // check if user is already logged in
            if (logged_in) {
                // TODO: print error message
                continue;
            }
            
            // check if user entered username
            if (input.size() != 2) {
                // TODO: print error message
                continue;
            }
            
            request["command"] = "signup";
            request["username"] = input[1];
                        
            send(server_fd, request.dump().c_str(), strlen(request.dump().c_str()), 0);
            memset(buff, 0, MAX_BUFFER_SIZE);
            read(server_fd, buff, MAX_BUFFER_SIZE);
            response = nlohmann::json::parse(buff);
            
            // check if username was valid or not
            if (response["status"] == 451) {
                // CODE 451: username already exists
                // TODO: print error message
                continue;
            }
            
            else if (response["status"] == 311) {
                string password, balance, phone_number, address;
                cout << "User Created Successfully. Enter the following information:\n";
                cout << ">> Password: ";
                cin >> password;
                cout << ">> Balance: ";
                cin >> balance;
                cout << ">> Phone Number: ";
                cin >> phone_number;
                cout << ">> Address: ";
                cin >> address;

                request["command"] = "change_info";
                request["password"] = password;
                request["balance"] = balance;
                request["phone_number"] = phone_number;
                request["address"] = address;

                send(server_fd, request.dump().c_str(), strlen(request.dump().c_str()), 0);
                memset(buff, 0, MAX_BUFFER_SIZE);
                read(server_fd, buff, MAX_BUFFER_SIZE);
                response = nlohmann::json::parse(buff);

                // check if signup was successful
                if (response["status"] == 503) {
                    // CODE 503: invalid arguments
                    // TODO: print error message
                    cout << "Invalid arguments: " << response["message"] << "\n";
                    continue;
                }
                else if (response["status"] == 430) {
                    // CODE 430: user not found
                    // TODO: print error message
                    cout << "User not found!\n";
                    continue;
                }
                else if (response["status"] == 231) {
                    // CODE 231: user info changed successfully
                    // TODO: print success message
                    cout << "Successfully signed up!\n";
                    continue;
                }
            }
        }


        string message = buff;
        send(server_fd, message.c_str(), strlen(message.c_str()), 0);
        memset(buff, 0, MAX_BUFFER_SIZE);
        read(server_fd, buff, MAX_BUFFER_SIZE);
        write(1, buff, strlen(buff));
    }

    return 0;
}