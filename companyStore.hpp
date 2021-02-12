#ifndef companyStore_HPP
#define companyStore_HPP

#include "PriorityQ.hpp"

class Service{
    private:
        Customer* population;
        Statistics STATS;
        //Queue PQ;
        //FIFOQ FIFO;
        int availServers;
        int popPos;
        int popSize;
        float currTime;
        void loadFirstArr();
    public:
        Service();
        void load(int n, float lambda);
        void printPOP();
        float NextRandInterval(float avg);
        float testAvg();
        void processNextEv();
        bool moreArrivals();
        void putArrivals();
        void SIM();
};

#endif