CC=gcc
CFLAGS=-Wall -Wextra -O2 -g
BUILD_DIR := ./build
SRC_DIRS := ./src

$(BUILD_DIR)/*.o: $(SRC_DIRS)/*.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIRS)/helper.cpp $(SRC_DIRS)/server.cpp -I ./ -o $(BUILD_DIR)/server
	$(CC) $(CFLAGS) $(SRC_DIRS)/helper.cpp $(SRC_DIRS)/client.cpp -I ./ -o $(BUILD_DIR)/client

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
