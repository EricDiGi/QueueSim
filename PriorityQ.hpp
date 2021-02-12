#ifndef PriorityQ_HPP
#define PriorityQ_HPP

#include <iostream>
#include <queue>

class Customer{
    private:
        float arrivalTime;
        float startOfServiceTime;
        float departureTime;
        Customer * nextCust;
    public:
        Customer();
        Customer(float arrive);
        void setSOS(float sos);
        void setArrival(float arr);
        float getArrival();
        void setDeparture(float dep);
        bool isArrival();
        friend class Queue;
        friend std::ostream &operator<< (std::ostream &out, const Customer c){
            out << c.arrivalTime << "\t" << c.startOfServiceTime << "\t";
            out << c.departureTime << "\n";
            return out;
        }
};
/*
class Queue{
    private:
        priority_queue<Customer> arrival;
        priority_queue<Customer> depart;
        float time();
    public:
        void placeArrival(Customer c);
        void placeDepart();
    
};*/

#endif