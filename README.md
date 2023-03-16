# Hotel Management Service
This is a hotel reservation system implemented in C++. It consists of a server and multiple clients, which communicate with each other using sockets. 
The server handles requests from clients and manages the hotel reservation database. Clients can connect to the server and make various requests, such as reserving a room, checking availability, and canceling a reservation.

The server stores the reservation data in `.json` files, which can be loaded and saved as needed. The server also ensures that multiple clients can access the system concurrently without conflicts or data corruption.
The clients interact with the system using a command-line interface (CLI), which allows them to enter commands and receive responses from the server. The commands are parsed and validated on the server side to ensure that they are properly formatted and authorized.

## Project Structure

## Server

## Login Menu

## Main Menu

## How to Run
1. navigate to project's root directory
2. make client and server executables using:
```text
make
```
3. run server executable:
```text
./server.out
```
4. run clients executables:
```text
./client.out
```
