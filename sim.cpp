#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "PriorityQ.hpp"
#include "sim.hpp"

using namespace std;

Simulation::Simulation(){
    srand((unsigned int)time(NULL));
    this->M = this->n = 0;
    this->lambda = this->mu = 0;
    this->massTime = 0.0;
    this->numCust = 0;
    this->servers = 0;
}

Simulation::Simulation(int n, float l, float m, int M){
    srand((unsigned int)time(NULL));
    this->M = M;
    this->n = n;
    this->lambda = l;
    this->mu = m;
    this->massTime = 0.0;
    this->numCust = 0;
    this->servers = 0;
}

bool Simulation::moreArrivals(){
    return this->numCust < this->n;
}

void Simulation::putPQ(int v){
    float t = 0.0;
    for(int i = 0; (i < v) && moreArrivals(); i++){
        t = nextRand(this->lambda);
        this->massTime += t;
        Customer c = Customer(this->massTime);
        c.num = this->numCust;
        this->PQ.put(c);
        this->numCust++;
    }
}


float Simulation::nextRand(float avg){
    float r = float(rand()%(RAND_MAX-1))/float((RAND_MAX));
    float i = -1.0*(1.0/avg)*log(r);
    return i;

}

void Simulation::processNextEvent(){
    Customer c;
    //if(this->FQ.SIZE() < this->M+1)
        c = Customer(this->PQ.pull());
    //else
        //c = Customer(this->FQ.());
    //cout << (c);
    if(c.getArrival() > c.getDeparture()){
        if(this->servers > 0){
            cout << this->servers << endl;
            this->servers -= 1;
            this->PQ.pull();
            c.setSOS(c.getArrival());
            float i = nextRand(this->mu);
            c.setDeparture(c.getSOS() + i);
            this->PQ.put(c);
            cout << c;
            //cout << "depart\n";
        }
        else{
            cout << "i ";
            this->FQ.insert(c);
            this->PQ.put(c);
        }
    }
    else{
        this->servers++;
        //cout << this->FQ.inLine(c) << endl;
        //cout << this->FQ.SIZE() << endl;
        cout << "bool: " << (this->FQ.inLine(c)) << endl;
        if(this->FQ.inLine(c)){
            this->FQ.pull();
            this->servers--;
            float i = nextRand(this->mu);
            c.setSOS(c.getArrival()+i);
            i = nextRand(this->mu);
            c.setDeparture(c.getSOS() + i);
            this->PQ.put(c);
            cout << "FQ proc" << endl;
            cout << "f " << c;
        }
        //cout << "departing\n";
    }
}

void Simulation::main_(){
    this->servers = this->M;
    putPQ(this->M);
    int buffer = 0;
    while(!this->PQ.empty() && buffer < 10*this->n){
        processNextEvent();
        if(moreArrivals() && this->PQ.SIZE() <= this->M+1)
            putPQ(this->M);
        buffer++;
    }
    cout << buffer << endl;
    cout << this->PQ.SIZE() << " " << this->FQ.SIZE() << endl;
    cout << this->numCust << endl;
    cout << this->massTime << endl;
}