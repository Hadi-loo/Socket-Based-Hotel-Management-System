#include "client.hpp"

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

int connectServer(string host_name ,int port) {
    int fd;
    struct sockaddr_in server_address;
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = inet_addr(host_name.c_str());

    if (connect(fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) { // checking for errors
        pretty_write("Error in connecting to server\n", "red");
    }
    else {
        pretty_write("Successfully connected to server\n", "green");
    }
    return fd;
}

void authentication_menu(int server_fd, bool &logged_in, Parser &client_parser) {
    
    char buff[MAX_BUFFER_SIZE] = {0};
    vector<string> input;

    while (true) {

        pretty_write(">> ", "cyan");
        memset(buff, 0, MAX_BUFFER_SIZE);
        read(0, buff, MAX_BUFFER_SIZE);
        input = client_parser.split_string(buff, ' ');
        nlohmann::json request, response;
        
        if (input.size() == 0) {
            continue;
        }

        else if (input[0] == "signup") {
            bool should_continue = handle_signup(logged_in, request, response, server_fd, buff, input);
            if (should_continue) {
                continue;
            }
        }

        else if (input[0] == "signin" || input[0] == "login") {
            bool should_continue = handle_signin(logged_in, request, response, server_fd, buff, input, client_parser);
            if (should_continue) {
                continue;
            }
        }

        else if (input[0] == "exit" || input[0] == "quit") {
            pretty_write("OODAFEZ :(\n", "cyan");
            exit(0);
        }

        else {
            pretty_write("Invalid command\n", "red");
        }

    }

}

void main_menu(int server_fd, bool &logged_in, Parser &client_parser) {
    
    char buff[MAX_BUFFER_SIZE] = {0};
    vector<string> input;

    while (1) {

        show_main_menu();
        pretty_write("\n>> ", "cyan");
        memset(buff, 0, MAX_BUFFER_SIZE);
        read(0, buff, MAX_BUFFER_SIZE);

        input = client_parser.split_string(buff, ' ');
        nlohmann::json request, response;

        if (input.size() == 0) {
            continue;
        } else if (input.size() > 1) {
            // TODO: print error message
            pretty_write("Invalid command\n", "red");
            continue;
        }

        if (input[0] == "0" || input[0] == "signout" || input[0] == "logout") {
            bool should_continue = handle_signout(logged_in, request, response, server_fd, buff, input);
            if (should_continue) {
                continue;
            } else {
                break;
            }
        }

        else if (input[0] == "1" || input[0] == "view_user" || input[0] == "show_user") {
            bool should_continue = handle_show_user_info(logged_in, request, response, server_fd, buff, input);
            if (should_continue) {
                continue;
            } else {
                break;
            }
        }

        else if (input[0] == "2") {
            bool should_continue = handle_show_all_users(logged_in, request, response, server_fd, buff, input);
            if (should_continue) {
                continue;
            } else {
                break;
            }
        }

        else if (input[0] == "3") {

        }

        else if (input[0] == "4") {

        }

        else if (input[0] == "5") {

        }

        else if (input[0] == "6") {

        }

        else if (input[0] == "7") {

        }

        else if (input[0] == "8") {

        }

        else if (input[0] == "9") {

        }

        else {
            pretty_write("Invalid command\n", "red");
        }

    }
}

void show_main_menu() {
    cout << "\n";
    cout << MAGENTA;
    cout << "____________________MAIN MENU____________________\n";
    cout << RESET;
    cout << YELLOW << "1. " << RESET << "View user Information\n";
    cout << YELLOW << "2. " << RESET << "View all users\n";
    cout << YELLOW << "3. " << RESET << "View rooms information\n";
    cout << YELLOW << "4. " << RESET << "Booking\n";
    cout << YELLOW << "5. " << RESET << "Canceling\n";
    cout << YELLOW << "6. " << RESET << "Pass day\n";
    cout << YELLOW << "7. " << RESET << "Edit information\n";
    cout << YELLOW << "8. " << RESET << "Leave room\n";
    cout << YELLOW << "9. " << RESET << "Rooms status\n";
    cout << YELLOW << "0. " << RESET << "Logout\n";
    cout << MAGENTA;
    cout << "_________________________________________________\n";
}

void pretty_write(string message, string color) {
    
    if (color == "red") {
        write(1, "\033[1;31m", 8);
    } else if (color == "yellow") {
        write(1, "\033[1;33m", 8);
    } else if (color == "green") {
        write(1, "\033[1;32m", 8);
    } else if (color == "blue") {
        write(1, "\033[1;34m", 8);
    } else if (color == "magenta") {
        write(1, "\033[1;35m", 8);
    } else if (color == "cyan") {
        write(1, "\033[1;36m", 8);
    } else if (color == "white") {
        write(1, "\033[1;37m", 8);
    } else if (color == "reset") {
        write(1, "\033[0m", 5);
    }

    write(1, message.c_str(), message.size());
    write(1, "\033[0m", 5);
}

bool handle_signup(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input) {
    // check if user is already logged in
    if (logged_in) {
        // TODO: print error message
        pretty_write("You are already logged in\n", "red");
        return true;
    }
    
    // check if user entered username
    if (input.size() != 2) {
        // TODO: print error message
        cout << RED;
        cout << "Invalid arguments count: " << input.size() << "\n";
        cout << RESET;
        return true;
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
        cout << RED;
        cout << "Username already exists\n";
        cout << RESET;
        return true;
    }
    
    else if (response["status"] == 311) {
        string password, balance, phone_number, address;
        cout << GREEN;
        cout << "User Created Successfully. ";
        cout << RESET;
        cout << "Enter the following information:\n";
        pretty_write(">> Password: ", "cyan");
        cin >> password;
        pretty_write(">> Balance: ", "cyan");
        cin >> balance;
        pretty_write(">> Phone Number: ", "cyan");
        cin >> phone_number;
        pretty_write(">> Address: ", "cyan");
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
            cout << RED;
            cout << "Invalid arguments: ";
            cout << RESET;
            cout << response["message"] << "\n";
            return true;
        }
        else if (response["status"] == 430) {
            // CODE 430: user not found
            // TODO: print error message
            cout << RED;
            cout << "User not found!\n";
            cout << RESET;
            return true;
        }
        else if (response["status"] == 231) {
            // CODE 231: user info changed successfully
            // TODO: print success message
            cout << GREEN;
            cout << "Successfully signed up!\n";
            cout << RESET;
            return true;
        }
    }
    return true;
}

bool handle_signin(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input, Parser &client_parser) {
    // check if user is already logged in
    if (logged_in) {
        // TODO: print error message
        cout << RED;
        cout << "You are already logged in\n";
        cout << RESET;
        return true;
    }

    // check if user entered username
    if (input.size() != 3) {
        // TODO: print error message
        cout << RED;
        cout << "Invalid arguments count\n";
        cout << RESET;
        return true;
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
        cout << RED;
        cout << "can't signin: ";
        cout << RESET;
        cout << response["message"] << "\n";
        return true;
    }   

    // login successful
    else if (response["status"] == 230) {
        // CODE 230: login successful
        // TODO: print success message
        logged_in = true;
        cout << GREEN;
        cout << "Successfully signed in!\n";
        cout << RESET;
        main_menu(server_fd, logged_in, client_parser);
    }

    return true;
}

bool handle_signout(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input) {

    // check if user is logged in
    if (!logged_in) {
        // TODO: print error message
        pretty_write("You are not logged in\n", "red");
        return true;
    }

    if (input.size() != 1) {
        // TODO: print error message
        pretty_write("Invalid arguments\n", "red");
        return true;
    }

    request["command"] = "logout";

    send(server_fd, request.dump().c_str(), request.dump().size(), 0);
    memset(buff, 0, MAX_BUFFER_SIZE);
    read(server_fd, buff, MAX_BUFFER_SIZE);
    response = nlohmann::json::parse(buff);

    // check if logout was successful or not
    if (response["status"] == 404) {
        // CODE 404: user not found
        // TODO: print error message
        pretty_write("User not found\n", "red");
        return true;
    }

    else if (response["status"] == 201) {
        // CODE 201: logout was successful
        // TODO: print success message
        logged_in = false;
        pretty_write("Logout was successful\n", "green");
        return false;
    }

    return true;
}

bool handle_show_user_info(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input) {
    // check if user is logged in
    if (!logged_in) {
        // TODO: print error message
        pretty_write("You are not logged in\n", "red");
        return true;
    }

    if (input.size() != 1) {
        // TODO: print error message
        pretty_write("Invalid arguments\n", "red");
        return true;
    }

    request["command"] = "get_user_info";

    send(server_fd, request.dump().c_str(), request.dump().size(), 0);
    memset(buff, 0, MAX_BUFFER_SIZE);
    read(server_fd, buff, MAX_BUFFER_SIZE);
    response = nlohmann::json::parse(buff);

    // check if get_user_info was successful or not
    if (response["status"] == 404) {
        // CODE 404: user not found
        // TODO: print error message
        pretty_write(response["message"], "red");
        pretty_write("\n", "red");
        return true;
    }

    else if (response["status"] == 100) {
        // CODE 100: get_user_info was successful
        // TODO: print success message
        pretty_write(response["message"], "green");
        pretty_write("\n", "green");
        pretty_write(response["summary"], "magenta");
        return true;
    }

    return true;

}

bool handle_show_all_users(bool &logged_in, nlohmann::json &request, nlohmann::json &response, int server_fd, char *buff, vector<string> &input) {
    // check if user is logged in
    if (!logged_in) {
        // TODO: print error message
        pretty_write("You are not logged in\n", "red");
        return true;
    }

    if (input.size() != 1) {
        // TODO: print error message
        pretty_write("Invalid arguments\n", "red");
        return true;
    }

    request["command"] = "get_all_users";

    send(server_fd, request.dump().c_str(), request.dump().size(), 0);
    memset(buff, 0, MAX_BUFFER_SIZE);
    read(server_fd, buff, MAX_BUFFER_SIZE);
    response = nlohmann::json::parse(buff);

    // check if get_all_users was successful or not
    if (response["status"] == 404) {
        // CODE 404: users not found
        // TODO: print error message
        pretty_write(response["message"], "red");
        pretty_write("\n", "red");
        return true;
    }

    else if (response["status"] == 100) {
        // CODE 100: get_all_users was successful
        // TODO: print success message
        pretty_write(response["message"], "green");
        pretty_write("\n", "green");
        string color = "magenta";
        for (auto user_info : response["summary"]) {
            pretty_write(user_info, color);
            pretty_write("\n", color);
            color = (color == "magenta") ? "cyan" : "magenta";
        }
        return true;
    }

    return true;

}


    



