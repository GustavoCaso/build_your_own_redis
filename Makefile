CXX=g++
CXXFLAGS=-Wall -Wextra -O2 -g -std=c++20
BUILD_DIR := ./build
SRC_DIRS := ./src

$(BUILD_DIR)/*.o: $(SRC_DIRS)/*.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_DIRS)/helper.cpp  $(SRC_DIRS)/hashtable.cpp $(SRC_DIRS)/server.cpp -I ./ -o $(BUILD_DIR)/server
	$(CXX) $(CXXFLAGS) $(SRC_DIRS)/helper.cpp $(SRC_DIRS)/client.cpp -I ./ -o $(BUILD_DIR)/client

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
