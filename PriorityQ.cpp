#include <iostream>
#include <queue>
#include "PriorityQ.hpp"



using namespace std;

Customer::Customer(){
    this->arrivalTime = 0.0;
    this->startOfServiceTime = 0.0;
    this->departureTime = 0.0;
    this->nextCust = NULL;
}

Customer::Customer(float arrive){
    this->arrivalTime = arrive;
}

void Customer::setArrival(float arr){
    this->arrivalTime = arr;
}

float Customer::getArrival(){
    return this->arrivalTime;
}

void Customer::setSOS(float sos){
    this->startOfServiceTime = sos;
}

void Customer::setDeparture(float dep){
    this->departureTime = dep;
}

bool Customer::isArrival(){
    if(this->departure == 0 && this->startOfServiceTime == 0.0 && this->arrivalTime > 0.0){
        return true;
    }
    return false;
}
/*
float Queue::time(){
    return rand();
}*/
/*
Queue::placeArrival(){
    float arrival = time() //some time function
    Customer c = Customer(arrival);
    arrival.push()
}

Queue::placeDepart(){

}*/