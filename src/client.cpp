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

int main(int argc, char const *argv[]) {
    char buff[1024] = {0};

    Parser client_parser(CONFIGS_PATH);
    string server_ip_address;
    int server_port;
    client_parser.parse_config(CONFIG_FILE_NAME, server_ip_address, server_port);
    int server_fd = connectServer(server_ip_address, server_port);

    // UDP and select must be added

    while (1) {
        read(0, buff, 1024);
        send(server_fd, buff, strlen(buff), 0);
        memset(buff, 0, 1024);
    }

    return 0;
}