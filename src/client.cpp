#include "client.hpp"

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

void authentication_menu(int server_fd, bool &logged_in, Parser &client_parser) {
    
    char buff[MAX_BUFFER_SIZE] = {0};
    vector<string> input;

    while (true) {

        write(1, ">> ", 3);
        memset(buff, 0, MAX_BUFFER_SIZE);
        read(0, buff, MAX_BUFFER_SIZE);
        input = client_parser.split_string(buff, ' ');
        nlohmann::json request, response;
        
        if (input.size() == 0) {
            cout << "::::: ZERO ::::::\n";
            continue;
        }

        if (input[0] == "signup") {
            
            // check if user is already logged in
            if (logged_in) {
                // TODO: print error message
                cout << "You are already logged in\n";
                continue;
            }
            
            // check if user entered username
            if (input.size() != 2) {
                // TODO: print error message
                cout << "Invalid arguments count: " << input.size() << "\n";
                for (int i = 0; i < input.size(); i++) {
                    cout << input[i] << "\n";
                }
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
                cout << "Username already exists\n";
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

                request["command"] = "signup_info";
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

        else if (input[0] == "signin") {
                
            // check if user is already logged in
            if (logged_in) {
                // TODO: print error message
                cout << "You are already logged in\n";
                continue;
            }
        
            // check if user entered username
            if (input.size() != 3) {
                // TODO: print error message
                cout << "Invalid arguments count\n";
                continue;
            }

            request["command"] = "signin";
            request["username"] = input[1];
            request["password"] = input[2];

            send(server_fd, request.dump().c_str(), strlen(request.dump().c_str()), 0);
            memset(buff, 0, MAX_BUFFER_SIZE);
            read(server_fd, buff, MAX_BUFFER_SIZE);
            response = nlohmann::json::parse(buff);

            // check if singin was successful or not
            if (response["status"] == 430) {
                // CODE 430: 
                // TODO: print error message
                cout << "can't signin: " << response["message"] << "\n";
                continue;
            }   

            // login successful
            else if (response["status"] == 230) {
                // CODE 230: login successful
                // TODO: print success message
                logged_in = true;
                cout << "Successfully signed in!\n";
                main_menu(server_fd, logged_in, client_parser);
            }


        }
    }

}

void main_menu(int server_fd, bool &logged_in, Parser &client_parser) {
    
    char buff[MAX_BUFFER_SIZE] = {0};
    vector<string> input;

    while (1) {

        show_main_menu();
        write(1, ">> ", 3);
        memset(buff, 0, MAX_BUFFER_SIZE);
        read(0, buff, MAX_BUFFER_SIZE);

    }
}

void show_main_menu() {
    cout << "1. View user Information\n";
    cout << "2. View all users\n";
    cout << "3. View rooms information\n";
    cout << "4. Booking\n";
    cout << "5. Canceling\n";
    cout << "6. Pass day\n";
    cout << "7. Edit information\n";
    cout << "8. Leave room\n";
    cout << "9. Rooms status\n";
    cout << "0. Logout\n";
}

int main(int argc, char const *argv[]) {

    Parser client_parser(CONFIGS_PATH);
    string server_ip_address;
    int server_port;
    client_parser.parse_config(CONFIG_FILE_NAME, server_ip_address, server_port);
    int server_fd = connectServer(server_ip_address, server_port);
    bool logged_in = false;

    authentication_menu(server_fd, logged_in, client_parser);

    return 0;
}
