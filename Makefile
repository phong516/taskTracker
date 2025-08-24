CXX = g++
CXXFLAGS = -std=c++17 -Wall -Isrc -Isrc/model -Isrc/view -Isrc/controller -Isrc/misc

SRC = $(shell find src -name '*.cpp')
OBJ = $(SRC:.cpp=.o)
TARGET = tasktracker

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.0: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(TARGET)
