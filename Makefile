CXX = g++
CXXFLAGS = -g -std=c++11 -Wall

SRCS = $(wildcard *.hpp)
OBJECTS = $(SRCS: .hpp=.o)

all: testStats

clean:
	rm -rf *.dSYM
	$(RM) *.o *.gc* test*.o core main

testStats: $(OBJECTS) testStats.cpp statistics.hpp statistics.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^