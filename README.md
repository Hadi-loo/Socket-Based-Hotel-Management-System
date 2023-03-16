# Hotel AliBaba Description
## Hotel Management Service
This is a hotel reservation system implemented in C++. It consists of a server and multiple clients, which communicate with each other using sockets. 
The server handles requests from clients and manages the hotel reservation database. Clients can connect to the server and make various requests, such as reserving a room, checking availability, and canceling a reservation.

The server stores the reservation data in `.json` files, which can be loaded and saved as needed. The server also ensures that multiple clients can access the system concurrently without conflicts or data corruption.
The clients interact with the system using a command-line interface (CLI), which allows them to enter commands and receive responses from the server. The commands are parsed and validated on the server side to ensure that they are properly formatted and authorized.

## Project Structure
There are 5 main folders containing the source and info of this project:
1. [src folder](https://github.com/Hadi-loo/CN_CHomeworks_1/tree/master/src): This folder contains the source code of the project.
2. [logs folder](https://github.com/Hadi-loo/CN_CHomeworks_1/tree/master/logs): This folder contains the logs of the main server and each client.
3. [configuration](https://github.com/Hadi-loo/CN_CHomeworks_1/tree/master/configuration): This folder contains the needed config files.
4. [bin](https://github.com/Hadi-loo/CN_CHomeworks_1/tree/master/bin): This folder contains the object files (.o) produced after compiling src files.
5. [description](https://github.com/Hadi-loo/CN_CHomeworks_1/tree/master/description): The Persian description of the project.

In the src folder, there are several class entities including:
- [HotelManagement](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/src/HotelManagement.hpp): The main processing unit of the program, this class handles the given requests to the server, and gives responses to the clients.
- [User](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/src/user.hpp): This class contains the data of program users, including ordinary users and admin.
- [Room](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/src/room.hpp): This class contains room data.
- [Reservation](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/src/reservation.hpp): The entity of reservation made by users.
- [Date](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/src/date.hpp): Contain date data. We use [Howard Hinnant date library](https://github.com/HowardHinnant/date) to handel date operations.
- [Logger](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/src/logger.hpp): This class saves the log of the program into .log files.
- [Parser](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/src/parser.hpp): Used for parsing JSON and string data.

## Server
  The server IP and port can be modified from the [config.json](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/configuration/config.json) file. The server gets requests in JSON format, parses them and makes a response in JSON again, and sends it to the corresponding client.    
  Here is the roadmap of how to run and setup server:
  1. Run server executable:
```text
./server.out
```   
2. Set the current date of the program:
```text
>> <Date Time>
```   
![Screenshot from 2023-03-16 19-49-28](https://user-images.githubusercontent.com/88896798/225685255-77bbe439-89da-486d-b173-4b738ac4c066.png)


## Client
Each client can connect to the main server whose config is found in the [config.json](https://github.com/Hadi-loo/CN_CHomeworks_1/blob/master/configuration/config.json) file. The client gets requests in JSON format, parses them and makes a response in JSON again, and sends it to the main server.  
the client file can be run via following command:
```
./client.out
```
The client program contains two main menu, the Login, and the Main menu.

### Login Menu
There are 3 available command in this menu:
- **Sign up**:
```
>> signup <username>
>> <password>
>> <purse>
>> <phone number>
>> <address>
```
![Screenshot from 2023-03-16 20-01-45](https://user-images.githubusercontent.com/88896798/225689475-cf5b1c0c-f467-4c95-81bc-18287b73a6aa.png)

- **Sign in**:
```
>> signin <username> <password>
```
![Screenshot from 2023-03-16 20-06-28](https://user-images.githubusercontent.com/88896798/225689822-d4eb214f-e03c-466f-9fec-88a66f4a8692.png)

- **Exit:**
```
>> exit
```
![Screenshot from 2023-03-16 20-08-19](https://user-images.githubusercontent.com/88896798/225690282-86fa08d8-320e-4587-b4d5-3897da123717.png)


### Main Menu

Here is the list of available commands:   

![Screenshot from 2023-03-16 23-14-50](https://user-images.githubusercontent.com/88896798/225735690-c924d549-c95f-443e-ae85-11dd618d65b6.png)


1. **View user information**:   
    
    ![Screenshot from 2023-03-16 20-11-59](https://user-images.githubusercontent.com/88896798/225705492-b7852584-c812-4600-a2e4-dffbb88721c2.png)

2. **View all users**:
  This command is only available for admin users.   
  
   ![Screenshot from 2023-03-16 20-14-00](https://user-images.githubusercontent.com/88896798/225705673-f3c18dde-55ba-4528-abc1-df91a08c4ff2.png)

3. **View rooms information**:   
   
    ![Screenshot from 2023-03-16 20-16-52](https://user-images.githubusercontent.com/88896798/225706305-bf9e2a42-4519-464b-a8d6-c6c1986b552f.png)

4. **Booking**:

```text
    book <RoomNum> <NumOfBeds> <CheckInDate> <CheckOutDate>
```

   ![Screenshot from 2023-03-16 20-21-22](https://user-images.githubusercontent.com/88896798/225707776-c6b41368-86b1-4295-a0be-237bc909578f.png)

5. **Canceling**:

```text
    canceling <RoomNum> <Number of reservation(per person)>
```
   ![Screenshot from 2023-03-16 20-30-52](https://user-images.githubusercontent.com/88896798/225708521-a6d1efa3-d27a-4457-8496-d574f96d9bca.png)

6. **Pass Day**:
```text
    passDay <value>
```

  ![Screenshot from 2023-03-16 20-32-57](https://user-images.githubusercontent.com/88896798/225708826-56389501-03a5-4d8a-a403-74331728597d.png)
  
7. **Edit Information**:
```text
    passDay <value>
```

  ![Screenshot from 2023-03-16 20-44-15](https://user-images.githubusercontent.com/88896798/225709344-1046d106-5ba3-4771-9910-79d6c3cff49c.png)


8. **Leaving Room**:
```text
    room <room number>
```

If you are admin, this command forces people to leave rooms that they are in right now. </br>

![Screenshot from 2023-03-16 23-05-14](https://user-images.githubusercontent.com/88896798/225734006-e176d6da-e7fd-4a19-9262-5b330794db00.png)


If you are a regular customer, you should use this command to leave early. </br>

![Screenshot from 2023-03-16 22-06-11](https://user-images.githubusercontent.com/88896798/225720235-76ffa0cc-5732-43be-8114-bfb8e32acf03.png)


9. **Manage Rooms**:
There are 3 different managing options:
- **Add a room**:
```text
    add <room number> <max capacity> <price>
```

![Screenshot from 2023-03-16 22-18-14](https://user-images.githubusercontent.com/88896798/225723263-326b57b7-c352-4e07-b08c-30c760f80ab6.png)


- **Modify a room**:
```text
    modify <room number> <new max capacity> <new price>
```

![Screenshot from 2023-03-16 22-18-57](https://user-images.githubusercontent.com/88896798/225723274-cd828c31-c895-4021-b269-1c2bfab30d87.png)


- **Delete a room**:
```text
    remove <room number>
```   

![Screenshot from 2023-03-16 22-19-13](https://user-images.githubusercontent.com/88896798/225723301-dd2b4566-9e32-4bf3-80d9-bebbc38de6ed.png)



0. **Log out**:  

![Screenshot from 2023-03-16 22-12-21](https://user-images.githubusercontent.com/88896798/225721528-5bee1291-e5a4-4b1d-9dbe-ec0e29280c2b.png)



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
