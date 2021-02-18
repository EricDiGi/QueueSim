#ifndef PriorityQ_HPP
#define PriorityQ_HPP

#include <iostream>
#include <queue>

class Customer{
    private:
        float arrivalTime;
        float startOfServiceTime;
        float departureTime;
        Customer* next;
        friend class Heap;
    public:
        int num;
        Customer();
        ~Customer();
        Customer(float arrive);
        Customer(const Customer &c);
        void setSOS(float sos);
        float getSOS();
        void setArrival(float arr);
        float getArrival();
        void setDeparture(float dep);
        float getDeparture();
        bool isArrival();
        void NEXT(Customer *c);
        Customer* NEXT();

        friend std::ostream &operator<< (std::ostream &out, const Customer &c){
            out << c.num << "\t";
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
        Customer* begin;
        Customer* end;
        int size;
    public:
        FIFO();
        ~FIFO();
        void insert(Customer c);
        bool inLine(Customer c);
        Customer top();
        Customer pull();
        bool empty();
        int SIZE();

        friend std::ostream &operator<< (std::ostream &out, const FIFO &l){
            Customer* temp = l.begin;
            if(temp == NULL)
                out << "Line is empty" << std::endl;
            while(temp){
                out << *temp << std::endl;
                temp = temp->NEXT();
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

        Customer peek();
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
                if(h.summit[i].getArrival() > h.summit[i].getDeparture()){
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