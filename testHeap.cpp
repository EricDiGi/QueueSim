#include <iostream>
#include "PriorityQ.hpp"

using namespace std;

int main(){
    Heap h;
    FIFO F;
    Customer a; Customer b; Customer c; Customer d; Customer e; Customer f;
    a.setArrival(0.5);
    b.setArrival(1.0);
    c.setArrival(1.5);
    d.setArrival(2.0);
    e.setArrival(3.0);
    f.setArrival(0.25);
    f.setDeparture(1.25);
    F.insert(a); h.put(a);
    F.insert(b); h.put(b);
    F.insert(c); h.put(c);
    F.insert(d); h.put(d);
    F.insert(e); h.put(e);
    F.insert(f); h.put(f);
    cout << h.peek() << endl;
    cout << h << endl;
    h.pull();
    cout << h << endl;
    cout << F.top(); F.pull();
    cout << F.empty() << endl;
    cout << F.inLine(b) << endl;
    cout << F;
}