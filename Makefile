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

testPriority: $(OBJECTS) testPriority.cpp PriorityQ.hpp PriorityQ.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

testStore: $(OBJECTS) CompanyStore.cpp companyStore.hpp PriorityQ.cpp PriorityQ.hpp statistics.hpp statistics.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

testStructs: $(OBJECTS) testStructs.cpp sim.hpp sim.cpp PriorityQ.cpp PriorityQ.hpp statistics.hpp statistics.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

testHeap:$(OBJECTS) testHeap.cpp PriorityQ.hpp PriorityQ.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
