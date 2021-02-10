#include <iostream>
#include "statistics.hpp"

using namespace std;

int main(){
    Statistics S;
    S.setInitialState(1,2,3,2);
    cout << S.percentIdle() << endl;
    cout << S.avgPopulation() << endl;
    cout << S.avgTimeIn() << endl;
}