CXX = g++
CXXFLAGS = -Wall -g -std=c++17

SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

src/%.o: src/%.cpp src/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean