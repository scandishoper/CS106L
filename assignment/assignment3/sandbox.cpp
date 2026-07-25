/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include <iostream>
#include "class.h"

void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
    shoper<double> a;
    shoper<double> b("scandi", 100.0);
    a.setname("shoper");
    a.setbalance(1000.0);
    std::cout << "name: " << a.getname() << " balance=" << a.getbalance() << " history_size=" << a.gethistorysize() << "\n";
    std::cout << "name: " << b.getname() << " balance=" << b.getbalance() << " history_size=" << b.gethistorysize() << "\n";
}