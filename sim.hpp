#ifndef sim_HPP
#define sim_HPP

#include "PriorityQ.hpp"
#include "statistics.hpp"

class Simulation{
    private:
        Heap PQ;
        FIFO FQ;
        Statistics stat;

        float currentWaitTime;
        int customerWaitedCount;
        float totalWaitTime;
        float serviceTime;
        float idleTime;

        float mostRecent;

        int n; int M;
        float mu; float lambda;
        
        int cmade;

        float amassedTime;
        int serverAvail;
        float nextRandInt(float avg);
    public:
        Simulation();
        Simulation(int n, float l, float m, int M);
        void morePQ(int v);
        bool moreArrivals();
        void major();
        void processNextEvent();
        void processStats(Customer &c);
        void printPQ();
};

#endif