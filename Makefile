CC=gcc
CFLAGS=-Wall -Wextra -O2 -g
BUILD_DIR := ./build
SRC_DIRS := ./src

# The final build step.
$(BUILD_DIR)/*.o: $(SRC_DIRS)/*.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIRS)/server.cpp -o $(BUILD_DIR)/server
	$(CC) $(CFLAGS) $(SRC_DIRS)/client.cpp -o $(BUILD_DIR)/client

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
