#ifndef statistics_HPP
#define statistics_HPP
#include "PriorityQ.hpp"

class Statistics{
    private:
        int n = 0; 
        float lambda = 1.0; 
        float mu = 1.0;
        int M = 1;
        Customer* queue;
        int qiter;
        int factorial(int i);
        double sum(int M, double l, double mu);
    public:
        void setInitialState(int n, float l, float m, int M);
        void FULLSEND();
        void putEntry(Customer c);
        double percentIdle();
        double avgPopulation();
        double avgTimeIn();
        double avgNumInQ();
        double avgTimeWaiting();
        double RHO();
        void printQ();
};

#endif