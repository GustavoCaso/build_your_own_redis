CXX=g++
CXXFLAGS=-Wall -Wextra -O2 -g -std=c++20
BUILD_DIR := ./build
SRC_DIRS := ./src

$(BUILD_DIR)/*.o: $(SRC_DIRS)/*.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_DIRS)/helper.cpp $(SRC_DIRS)/hashtable.cpp $(SRC_DIRS)/avl.cpp $(SRC_DIRS)/zset.cpp $(SRC_DIRS)/heap.cpp $(SRC_DIRS)/thread_pool.cpp $(SRC_DIRS)/server.cpp -I ./ -o $(BUILD_DIR)/server
	$(CXX) $(CXXFLAGS) $(SRC_DIRS)/helper.cpp $(SRC_DIRS)/client.cpp -I ./ -o $(BUILD_DIR)/client

test_avl:
	$(CXX) $(CXXFLAGS) $(SRC_DIRS)/test_avl.cpp -I ./ -o $(BUILD_DIR)/test_avl

test_heap:
	$(CXX) $(CXXFLAGS) $(SRC_DIRS)/test_heap.cpp -I ./ -o $(BUILD_DIR)/test_heap

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
