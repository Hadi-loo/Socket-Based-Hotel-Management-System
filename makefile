CC = g++ --std=c++17
BIN_DIR = bin
SERVER_EXE = server
CLIENT_EXE = client

all: $(SERVER_EXE) $(CLIENT_EXE)

$(SERVER_EXE): server.cpp
	$(CC) server.cpp -o $(SERVER_EXE)

$(CLIENT_EXE): client.cpp
	$(CC) client.cpp -o $(CLIENT_EXE)

clean:
	rm -f /$(BIN_DIR)/*.o /$(BIN_DIR)/*.out
