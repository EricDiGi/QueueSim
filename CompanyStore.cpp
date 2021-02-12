#include <iostream>
#include <cmath>

#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include "statistics.hpp" 
#include "companyStore.hpp"
#include "PriorityQ.hpp"

using namespace std;
/* GLOBALS */
int n = 0; 
float lambda = 1.0; 
float mu = 1.0;
int M = 1;

Service::Service(){
    this->population = NULL;
    this->currTime = 0.0;
}

void Service::load(int n, float lambda){
    this->population = new Customer[n];
    this->popSize = n;
    this->popPos = 0;
    for(int i = 0; i < n; i++){
        this->population[i].setArrival(NextRandInterval(lambda));
    }
}

float Service::NextRandInterval(float lambda){
    //cout << rand() << endl;
    float f = (float)(rand()%RAND_MAX)/RAND_MAX;
    float randIntv = -1*(1.0/lambda)*log(f);
    return randIntv;
}

void Service::printPOP(){
    for(int i = 0 ; i < n; i++){
        cout << this->population[i];
    }
}

float Service::testAvg(){
    float sum = 0.0;
    for(int i = 0 ; i < n; i++){
        sum += this->population[i].getArrival();
    }
    return sum/n;
}

void loadFirstArr(){
    for(int i = 0; i < 5; i++){
        //this->PQ.push(this->population[i]);
    }
    this->popPos = 5;
}

bool Service::moreArrivals(){
    return (this->popSize - this->popPos) > 0;
}

void Service::putArrivals(){
    //this->PQ.push(this->population[this->popPos]);
    this->popPos++;
}

void Service::processNextEv(){
    Customer* c = PQ.top(); //top returns pointer to top of heap
    if(c->isArrival()){
        if(this->availServers > 0){
            this->availServers--;
            c->setStartOfService(this->currTime);
            float interv = NextRandInterval();
            c->setDeparture(this->currTime + interv);
            PQ.set(); //Reorg priority Q
        }
        else{
            FIFO.next(c);
        }
    }
    else{
        this->availServers++;
        this->STATS.FULLSEND();
        if(!FIFO.empty()){
            Customer c = FIFO.pop();
            
        }
        
    }
}

void Service::SIM(){
    this->STATS.setInitialState(n, lambda, mu, M);
    loadFirstArr();
    this->availServers = M;
    while(!PQ.empty()){
        processNextEv();
        if(moreArrivals() && PQ.size() < M+1){
            putArrivals();
        }
    }
}


/* MAIN STREAM */
int main(){
    srand(time(NULL));
    cout << "n - number of arrivals : ";
    while(n < 1000 || n > 5000){
        if(n < 1000 || n > 5000){cout << "Enter value 1-10 please: ";}
        cin >> n;
    }
    cout << "average arrivals / time : ";
    cin >> lambda;
    cout << "avg number served / time : ";
    cin >> mu;
    cout << "Number of Severs  : ";
    cin >> M;
    while(M <= 0 || M > 10){
        if(M <= 0 || M > 10){cout << "Enter value 1-10 please: ";}
        cin >> M;
    }
    cout << "BEGINNING SIM ---\n";


    Service S;
    S.load(n,lambda); //load customers into system.
    //S.printPOP();
    cout << S.testAvg() << endl;
    S.SIM();
    Statistics stats;
    stats.setInitialState(n, lambda, mu, M);
    stats.FULLSEND();
}