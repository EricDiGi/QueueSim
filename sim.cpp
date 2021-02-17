#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "PriorityQ.hpp"
#include "sim.hpp"

using namespace std;

Simulation::Simulation(){
    srand((unsigned int)time(NULL));
    this->currentWaitTime = 0.0;
    this->customerWaitedCount = 0.0;
    this->totalWaitTime = 0.0;
    this->serviceTime = 0.0;
    this->idleTime = 0.0;
    this->mostRecent = 0.0;
}

Simulation::Simulation(int n, float l, float m, int M){
    srand((unsigned int)time(NULL));
    this->n = n; this->lambda = l;
    this->mu = m; this->M = m;
    this->amassedTime = 0;
    this->cmade = 0;
    this->currentWaitTime = 0.0;
    this->customerWaitedCount = 0.0;
    this->totalWaitTime = 0.0;
    this->serviceTime = 0.0;
    this->idleTime = 0.0;
    this->mostRecent = 0.0;
    cout << "sim built" << endl;
}

float Simulation::nextRandInt(float avg){
    float v = float(rand())/float((RAND_MAX));
    float interv = -1*(1.0/avg)*log(v);
    return interv;
}

bool Simulation::moreArrivals(){
    return (cmade < this->n);
}

void Simulation::morePQ(int v){
    float t;
    for(int i = 0; (i < v) && moreArrivals(); i++){
        Customer c;
        t = nextRandInt(this->lambda);
        this->amassedTime += t;
        c.setArrival(amassedTime);
        this->PQ.put(c);
        this->cmade++;
    }
}

void Simulation::processStats(Customer &c){
    this->currentWaitTime = c.getSOS() - c.getArrival();
    if(this->currentWaitTime > 0){
        this->customerWaitedCount++;
    }
    this->totalWaitTime += this->currentWaitTime;
    this->serviceTime += c.getDeparture() - c.getSOS();
    if(this->serverAvail == M && this->FQ.empty() && !this->PQ.empty()){
        //accum idle
        this->idleTime += (this->PQ.peek()).getArrival() - c.getDeparture();
    }
}

void Simulation::major(){
    this->stat.setInitialState(this->n, this->lambda, this->mu, this->M);
    morePQ(this->M);
    this->serverAvail = this->M;
    while(!this->PQ.empty()){
        processNextEvent();
        if(moreArrivals() && this->PQ.SIZE() <= this->M+1)
            morePQ(this->M+1);
    }
}

void Simulation::processNextEvent(){
    Customer c;
    bool isFQ = false;
    if(!this->FQ.empty()){
        cout << this->FQ;
        c = this->FQ.pull();
        isFQ = true;
    }
    else
        c = this->PQ.pull();
    
    if(c.isArrival()){
        if(this->serverAvail > 0){
            this->serverAvail--;
            c.setSOS(c.getArrival());
            float intv = nextRandInt(this->mu);
            c.setDeparture(c.getArrival() + intv);
            this->PQ.put(c); 
        }
        else{
            this->FQ.insert(c);
        }
    }
    else{
        serverAvail++;
        processStats(c);
        //cout << isFQ << " ";
        if(isFQ){
            //c = this->FQ.pull();
            float t = nextRandInt(this->mu);
            c.setSOS(c.getArrival()+t);
            t = nextRandInt(this->mu);
            c.setDeparture(c.getSOS()+t);
            cout << "THIS IS AN FQ\n"; 
            cout << c.getArrival() << "\t" << c.getSOS() << "\t" << c.getDeparture() << endl;
            this->PQ.put(c);
            serverAvail--;
        }
    }
}

void Simulation::printPQ(){
    cout << this->PQ << endl;
    cout << "Statistics Accum. ::\n";
    cout << this->currentWaitTime << endl;
    cout << this->customerWaitedCount << endl;
    cout << this->totalWaitTime << endl;
    cout << this->serviceTime << endl;
    cout << this->idleTime << endl;
    cout << this->amassedTime << endl;
    float RHO = (this->M * this->amassedTime) / this->serviceTime;
    cout << RHO << endl;
}