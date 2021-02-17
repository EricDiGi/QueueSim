#include <iostream>
#include <cstdlib>
#include <ctime>
#include "PriorityQ.hpp"
#include "sim.hpp"

using namespace std;

int main(){
    Simulation S = Simulation(5000,8,5,1);
    S.major();
    S.printPQ();
}