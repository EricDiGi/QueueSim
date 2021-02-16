#include <iostream>
#include "PriorityQ.hpp"

using namespace std;

int main(){
    Heap h;
    Customer a; Customer b; Customer c; Customer d; Customer e; Customer f;
    a.setArrival(0.5);
    b.setArrival(1.0);
    c.setArrival(1.5);
    d.setArrival(2.0);
    e.setArrival(3.0);
    f.setArrival(0.25);
    f.setDeparture(1.25);
    h.put(a);
    h.put(c);
    h.put(f);
    h.put(b);
    h.put(e);
    h.put(d);
    cout << h;
    cout << h.pull() << endl;
    h.set();
    cout << h << endl;
    cout << h.pull() << endl;
    h.set();
    cout << h << endl;
    cout << h.pull() << endl;
    h.set();
    cout << h << endl;
    cout << h.pull() << endl;
    h.set();
    cout << h << endl;
    cout << h.pull() << endl;
    h.set();
    cout << h << endl;
    cout << h.pull() << endl;
    h.set();
    cout << h << endl;
}