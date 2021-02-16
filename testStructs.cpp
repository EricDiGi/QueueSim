#include <iostream>
#include <cstdlib>
#include <ctime>
#include "PriorityQ.hpp"
#include "sim.hpp"

using namespace std;

int main(){
    Simulation S = Simulation(100,5,5,5);
    S.major();
    S.printPQ();
    S.printStatsQ();
}