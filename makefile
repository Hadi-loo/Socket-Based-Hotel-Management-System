# Compiler
CXX = g++
CXXFLAGS = --std=c++11

# Directories
SRC_DIR = src
BIN_DIR = bin

# Executables
SERVER_EXE = server.out
CLIENT_EXE = client.out

# Objects


# Sensitivity lists

ServerExecutableSensitivityList = \
	$(BIN_DIR)/server.o \
	$(BIN_DIR)/parser.o \
	$(BIN_DIR)/logger.o \
	$(BIN_DIR)/HotelManagement.o \
	$(BIN_DIR)/user.o \
	$(BIN_DIR)/room.o \
	$(BIN_DIR)/reservation.o \
	$(BIN_DIR)/date.o \

ClientExecutableSensitivityList = \
	$(BIN_DIR)/client.o \
	$(BIN_DIR)/parser.o \
	$(BIN_DIR)/user.o \
	$(BIN_DIR)/room.o \
	$(BIN_DIR)/reservation.o \
	$(BIN_DIR)/date.o \

ServerSensitivityList = \
	$(SRC_DIR)/server.cpp \
	$(SRC_DIR)/parser.hpp \
	$(SRC_DIR)/logger.hpp \
	$(SRC_DIR)/HotelManagement.hpp \
	$(SRC_DIR)/user.hpp \
	$(SRC_DIR)/defs.hpp \

ClientSensitivityList = \
	$(SRC_DIR)/client.cpp \
	$(SRC_DIR)/parser.hpp \
	$(SRC_DIR)/defs.hpp \

HotelManagementSensitivityList = \
	$(SRC_DIR)/HotelManagement.cpp \
	$(SRC_DIR)/HotelManagement.hpp \
	$(SRC_DIR)/user.hpp \
	$(SRC_DIR)/room.hpp \
	$(SRC_DIR)/reservation.hpp \
	$(SRC_DIR)/date.hpp \

ParserSensitivityList = \
	$(SRC_DIR)/parser.cpp \
	$(SRC_DIR)/parser.hpp \
	$(SRC_DIR)/user.hpp \
	$(SRC_DIR)/json.hpp \

LoggerSensitivityList = \
	$(SRC_DIR)/logger.cpp \
	$(SRC_DIR)/logger.hpp \

UserSensitivityList = \
	$(SRC_DIR)/user.cpp \
	$(SRC_DIR)/user.hpp \

RoomSensitivityList = \
	$(SRC_DIR)/room.cpp \
	$(SRC_DIR)/room.hpp \
	$(SRC_DIR)/reservation.hpp \

ReservationSensitivityList = \
	$(SRC_DIR)/reservation.cpp \
	$(SRC_DIR)/reservation.hpp \
	$(SRC_DIR)/date.hpp \

DateSensitivityList = \
	$(SRC_DIR)/date.cpp \
	$(SRC_DIR)/date.hpp \


# Compile
all: $(SERVER_EXE) $(CLIENT_EXE)

$(SERVER_EXE): $(ServerExecutableSensitivityList)
	$(CXX) $(CXXFLAGS) $(ServerExecutableSensitivityList) -o $(SERVER_EXE)

$(CLIENT_EXE): $(ClientExecutableSensitivityList)
	$(CXX) $(CXXFLAGS) $(ClientExecutableSensitivityList) -o $(CLIENT_EXE) 


$(BIN_DIR)/server.o: $(ServerSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/server.cpp -o $(BIN_DIR)/server.o

$(BIN_DIR)/client.o: $(ClientSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/client.cpp -o $(BIN_DIR)/client.o

$(BIN_DIR)/parser.o: $(ParserSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/parser.cpp -o $(BIN_DIR)/parser.o

$(BIN_DIR)/logger.o: $(LoggerSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/logger.cpp -o $(BIN_DIR)/logger.o

$(BIN_DIR)/HotelManagement.o: $(HotelManagementSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/HotelManagement.cpp -o $(BIN_DIR)/HotelManagement.o

$(BIN_DIR)/user.o: $(UserSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/user.cpp -o $(BIN_DIR)/user.o

$(BIN_DIR)/room.o: $(RoomSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/room.cpp -o $(BIN_DIR)/room.o

$(BIN_DIR)/reservation.o: $(ReservationSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/reservation.cpp -o $(BIN_DIR)/reservation.o

$(BIN_DIR)/date.o: $(DateSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/date.cpp -o $(BIN_DIR)/date.o

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.out
