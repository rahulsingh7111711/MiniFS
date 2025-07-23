CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRCS = src/main.cpp src/vfs.cpp src/block_manager.cpp

TARGET = vfs

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
