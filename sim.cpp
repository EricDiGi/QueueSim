#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "PriorityQ.hpp"
#include "sim.hpp"

using namespace std;

Simulation::Simulation(){
    srand((unsigned int)time(NULL));
}

Simulation::Simulation(int n, float l, float m, int M){
    srand((unsigned int)time(NULL));
    this->n = n; this->lambda = l;
    this->mu = m; this->M = m;
    this->amassedTime = 0;
    this->cmade = 0;
    cout << "sim built" << endl;
}

float Simulation::nextRandInt(float avg){
    float v = float(rand())/float((RAND_MAX));
    float interv = -1*(1.0/avg)*log(v);
    return interv;
}

bool Simulation::moreArrivals(){
    return (cmade <= this->n);
}

void Simulation::morePQ(int v){
    float t;
    for(int i = 0; (i < v) && moreArrivals(); i++){
        Customer c;
        t = nextRandInt(this->lambda);
        this->amassedTime += t;
        cout << this->amassedTime << endl;
        c.setArrival(amassedTime);
        this->PQ.put(c);
        this->cmade++;
    }
    //cout << cmade << endl;
}

void Simulation::major(){
    cout << "in major" << endl;
    morePQ(this->M);
    cout << "morePQ" << endl;
    this->serverAvail = this->M;
    cout << this->PQ << endl;
    cout << this->PQ.empty() << endl;
    while(!this->PQ.empty()){
        processNextEvent();
        if(moreArrivals() && this->PQ.SIZE() > this->M+1)
            morePQ(this->M+1);
    }

    cout << cmade << endl;
    cout << amassedTime << endl;
}

void Simulation::processNextEvent(){
    cout << "in EV proc" << endl;
    Customer c;
    if(!this->FQ.empty())
        c = this->FQ.top();
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
        if(this->FQ.inLine(c)){
            c = this->FQ.pull();
            float t = nextRandInt(this->mu);
            c.setDeparture(c.getArrival()+t);
            c.setSOS(c.getDeparture());
            this->PQ.put(c);
            serverAvail--;
        }
    }
}

void Simulation::printPQ(){
    cout << this->PQ << endl;
}

void Simulation::make(int n, float l, float m, int M){
    //this->PQ = Heap();
    srand((unsigned int)time(NULL));
    this->n = n; this->lambda = l;
    this->mu = m; this->M = m;
    this->amassedTime = 0;
    this->cmade = 0;
    cout << "sim built" << endl;
}