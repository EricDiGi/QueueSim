#include <iostream>
#include <cstdlib>
#include <ctime>
#include "PriorityQ.hpp"
#include "sim.hpp"

using namespace std;

int main(){
    Simulation S = Simulation(100,8,1,10);
    S.main_();
}