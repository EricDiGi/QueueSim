#ifndef PriorityQ_HPP
#define PriorityQ_HPP

#include <iostream>
#include <queue>

class Customer{
    private:
        float arrivalTime;
        float startOfServiceTime;
        float departureTime;
        Customer * next;
    public:
        Customer();
        ~Customer();
        Customer(float arrive);
        void setSOS(float sos);
        float getSOS();
        void setArrival(float arr);
        float getArrival();
        void setDeparture(float dep);
        float getDeparture();
        bool isArrival();
        void chain(Customer *c);
        Customer* NEXT();

        friend class Heap;
        friend std::ostream &operator<< (std::ostream &out, const Customer &c){
            out << c.arrivalTime << "\t" << c.startOfServiceTime << "\t";
            out << c.departureTime << "\n";
            return out;
        }
        bool operator== (const Customer &b) const{
            return this->arrivalTime == b.arrivalTime;
        }
};


class FIFO{
    private:
        Customer* line;
        int size;
        int rems;
    public:
        FIFO();
        ~FIFO();
        void insert(Customer c);
        bool inLine(Customer c);
        Customer top();
        Customer pull();
        bool empty();

        friend std::ostream &operator<< (std::ostream &out, const FIFO &l){
            Customer c;
            for(int i = 0; i < (l.size-l.rems); i++){
                c = l.line[(l.rems+i)%200];
                if(c.isArrival()){
                    out << "+" << c.getArrival() << "\t";
                }
                else{
                    out << "-" << c.getDeparture() << "\t";
                }
            }
            return out;
        }
};

class Heap{
    private:
        Customer* summit;
        int size;
        bool doSwap(int P, int c);
    public:
        Heap();
        ~Heap();

        void put(Customer c);
        void put(FIFO f);
        Customer pull();
        void set();

        bool empty();
        int SIZE();

        int countDepart();
        
        friend std::ostream &operator<< (std::ostream &out, const Heap &h){
            out << "HEAP SUMMARY::\t";
            for(int i = 0; i < h.size; i++){
                if(h.summit[i].isArrival()){
                    out << "+" << h.summit[i].getArrival() << "\t";
                }
                else{
                    out << "-" << h.summit[i].getDeparture() << "\t";
                }
            }
            out << std::endl;
            return out;
        }
};

#endif