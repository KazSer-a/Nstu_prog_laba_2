CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude
SOURCES = main.cpp $(wildcard src/*.cpp)
all: laba2
laba2: $(SOURCES) include/tasks.h include/hash_table.h
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@
clean:
	rm -f laba2 laba2.exe
.PHONY: all clean
