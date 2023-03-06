#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>





int connectServer(int port) {
    int fd;
    struct sockaddr_in server_address;
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) { // checking for errors
        printf("Error in connecting to server\n");
    }
    printf("Connected to the server\n");
    return fd;
}


int main(int argc, char const *argv[]) {
    char buff[1024] = {0};
    int server_port = atoi(argv[1]);
    
    int server_fd = connectServer(server_port);

    // UDP and select must be added

    while (1) {
        read(0, buff, 1024);
        send(server_fd, buff, strlen(buff), 0);
        memset(buff, 0, 1024);
    }

    return 0;
}