CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = hello10
SRC = hello10.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean run