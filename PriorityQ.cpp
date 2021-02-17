#include <iostream>
#include <queue>
#include "PriorityQ.hpp"



using namespace std;

Customer::Customer(){
    this->arrivalTime = -1.0;
    this->startOfServiceTime = -1.0;
    this->departureTime = -1.0;
    this->next = NULL;
}

Customer::Customer(const Customer &c){
    this->arrivalTime = c.arrivalTime;
    this->startOfServiceTime = c.startOfServiceTime;
    this->departureTime = c.departureTime;
    this->next = NULL;
}

Customer::~Customer(){
    this->next = NULL;
}

Customer::Customer(float arrive){
    this->arrivalTime = arrive;
    this->next = NULL;
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

float Customer::getSOS(){
    return this->startOfServiceTime;
}
void Customer::setDeparture(float dep){
    this->departureTime = dep;
}

float Customer::getDeparture(){
    return this->departureTime;
}

bool Customer::isArrival(){
    if(this->departureTime < 0 && this->startOfServiceTime < 0.0 && this->arrivalTime > -1){
        return true;
    }
    return false;
}

void Customer::NEXT(Customer *c){
    this->next = c;
}

Customer* Customer::NEXT(){
    if(this->next == NULL){
        return NULL;
    }
    return this->next;
}
/*****************************************
HEAP IMPLEMENTATION
*****************************************/ 

Heap::Heap(){
    this->summit = new Customer[0];
    this->size = 0;
}

Heap::~Heap(){
    delete[] this->summit;
}

bool Heap::doSwap(int P, int c){
    float compA = this->summit[P].departureTime;
    float compB = this->summit[c].departureTime;

    if(this->summit[P].isArrival())
        compA = this->summit[P].arrivalTime;
    if(this->summit[c].isArrival())
        compB = this->summit[c].arrivalTime;

    return compA > compB;
}

/* put customer into the queue*/
void Heap::put(Customer c){
    Customer* tempHeap = new Customer[this->size+1];
    for(int i = 0; i < this->size; i++){
        tempHeap[i] = this->summit[i];
    }
    tempHeap[this->size] = c;
    this->size++;
    
    delete[] this->summit;
    this->summit = tempHeap;
    set();
}

void Heap::put(FIFO f){
    Customer* tempHeap = new Customer[this->size+1];
    for(int i = 0; i < this->size; i++){
        tempHeap[i] = this->summit[i];
    }
    tempHeap[this->size] = f.top();
    this->size++;
    
    delete[] this->summit;
    this->summit = tempHeap;
    set();
}
/* pull top priority customer*/
Customer Heap::pull(){
    if(this->size == 0)
        return Customer();
    Customer* tempHeap = new Customer[this->size-1];
    Customer q = this->summit[0];
    if(this->size > 1){
        for(int i = 1; i < this->size; i++){
            tempHeap[i-1] = this->summit[i];
        }
    }
    this->size--;

    delete[] this->summit;
    this->summit = tempHeap;
    set();
    return q;
}

/* Sort the heap using percolate up method*/
void Heap::set(){
    int i = this->size-1;
    while(i/2 > 0){
        if(doSwap(i/2, i)){
            Customer temp = this->summit[i/2];
            swap(this->summit[i/2], this->summit[i]);
            this->summit[i] = temp;
        }
        i = i/2;
    }
}

bool Heap::empty(){
    return (this->size <= 0);
}

int Heap::SIZE(){
    return this->size;
}
int Heap::countDepart(){
    int iter = 0;
    for(int i = 0; i < this->size; i++){
        if(this->summit[i].getDeparture() > -0.5)
            iter++;
    }
    return iter;
}

Customer Heap::peek(){
    return this->summit[0];
}
/*******************************************
FIFO queue
*******************************************/

FIFO::FIFO(){
    this->begin = NULL;
    this->end = NULL;
}

FIFO::~FIFO(){
    this->end = NULL;
    delete[] this->begin;
}

void FIFO::insert(Customer c){
    Customer* t = &c;
    if(end == NULL)
        this->begin = t;
    else
        this->end->NEXT(t);
    this->end = t;
    //if(t != NULL)
        //delete[] t;
}

Customer FIFO::top(){
    Customer c = Customer(*begin);
    return c;
}

Customer FIFO::pull(){
    if(this->begin == NULL)
        return Customer();
    Customer c = *this->begin;
    if(this->begin == this->end)
        this->begin = NULL;
    else
        this->begin = this->begin->NEXT();
    return c;
}

bool FIFO::inLine(Customer c){
    Customer* t = this->begin;
    while(t != NULL){
        if(*t == c){
            return true;
        }
        t = t->NEXT();
    }
    delete t;
    return false;
}

bool FIFO::empty(){
    return this->begin == NULL;
}