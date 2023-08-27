CXX=g++
CXXFLAGS=-Wall -Wextra -O2 -std=c++20
BUILD_DIR := ./build
SRC_DIRS := ./src
TEST_DIRS := ./test

server: $(SRC_DIRS)/helper.cpp $(SRC_DIRS)/hashtable.cpp $(SRC_DIRS)/avl.cpp $(SRC_DIRS)/zset.cpp $(SRC_DIRS)/heap.cpp $(SRC_DIRS)/thread_pool.cpp $(SRC_DIRS)/server.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/server

client: $(SRC_DIRS)/helper.cpp $(SRC_DIRS)/client.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/client

test_avl: $(TEST_DIRS)/test_avl.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/test_avl

test_heap: $(TEST_DIRS)/test_heap.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/test_heap

all: server client

test: test_avl test_heap
	./$(BUILD_DIR)/test_avl
	./$(BUILD_DIR)/test_heap

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
