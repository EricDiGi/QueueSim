#include <iostream>
#include <cmath>
#include "statistics.hpp"

using namespace std;

int Statistics::factorial(int i){
    if(i == 0)
        return 1;
    return i*factorial(i-1);
}

double Statistics::sum(int M, double l, double mu){
    double acc = 0.0;
    for(int i = 0; i < M; i++){
        acc += (1.0/(double)factorial(i))*pow(l/mu, i);
    }
    return acc;
}

void Statistics::setInitialState(int n, float l, float m, int M){
    this->n = n;
    this->lambda = l;
    this->mu = m;
    this->M = M;
}

double Statistics::percentIdle(){
        double SUM = sum(this->M, this->lambda, this->mu);
        double addon = (1.0/(double)factorial(M))*pow(this->lambda/this->mu, this->M);
        double mod = (this->M*this->mu);
        double mult = mod/(mod-this->lambda);
        double Po = 1.0 / (SUM + addon*mult);
        return Po;
}

double Statistics::avgPopulation(){
    double numerator = (this->lambda*this->mu) * pow((double)this->lambda/(double)this->mu, this->M);
    double denom = factorial(this->M-1)*pow((this->M*this->mu) - this->lambda, 2);
    double full = (numerator/denom)*percentIdle() + ((double)this->lambda/(double)this->mu);
    return full;
}

double Statistics::avgTimeIn(){
    double aTI = avgPopulation()/this->lambda;
    return aTI;
}

double Statistics::avgNumInQ(){
    double aNIQ = avgPopulation() - (this->lambda/this->mu);
    return aNIQ;
}

double Statistics::avgTimeWaiting(){
    double aTW = avgNumInQ()/this->lambda;
    return aTW;
}

double Statistics::RHO(){
    double rho = this->lambda/(this->M*this->mu);
    return rho;
}

void Statistics::FULLSEND(){
    cout << "Po = " << percentIdle() << endl;
    cout << "L = " << avgPopulation() << endl;
    cout << "W = " << avgTimeIn() << endl;
    cout << "Lq = " << avgNumInQ() << endl;
    cout << "Wq = " << avgTimeWaiting() << endl;
}