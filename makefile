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
ServerSensitivityList = \
	$(SRC_DIR)/server.cpp \
	$(SRC_DIR)/parser.hpp \
	$(SRC_DIR)/defs.hpp

ClientSensitivityList = \
	$(SRC_DIR)/client.cpp \
	$(SRC_DIR)/parser.hpp \
	$(SRC_DIR)/defs.hpp

ParserSensitivityList = \
	$(SRC_DIR)/parser.cpp \
	$(SRC_DIR)/parser.hpp \
	$(SRC_DIR)/json.hpp



# Compile
all: $(SERVER_EXE) $(CLIENT_EXE)

$(SERVER_EXE): $(BIN_DIR)/server.o $(BIN_DIR)/parser.o
	$(CXX) $(CXXFLAGS) $(BIN_DIR)/server.o $(BIN_DIR)/parser.o -o $(SERVER_EXE)

$(CLIENT_EXE): $(BIN_DIR)/client.o $(BIN_DIR)/parser.o
	$(CXX) $(CXXFLAGS) $(BIN_DIR)/client.o $(BIN_DIR)/parser.o -o $(CLIENT_EXE) 


$(BIN_DIR)/server.o: $(ServerSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/server.cpp -o $(BIN_DIR)/server.o

$(BIN_DIR)/client.o: $(ClientSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/client.cpp -o $(BIN_DIR)/client.o

$(BIN_DIR)/parser.o: $(ParserSensitivityList)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/parser.cpp -o $(BIN_DIR)/parser.o

.PHONY: clean

clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.out
