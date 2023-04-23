#pragma once 

#include <vector>
#include <string>
#include <set>
#include <iostream>


using namespace std;

struct Events {
    vector<string> lastEvents;
    set<string> sortedEvents;
};

ostream& operator << (ostream& out, const Events& events);
