#include "xml.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Spending {
  string category;
  int amount;
};

vector<Spending> LoadFromXml(istream& input) {
    vector<Spending> result;
    Document doc = Load(input);
    for (const auto& item : doc.GetRoot().Children()) {
        if(item.Name() == "spend"){
            result.push_back({item.AttributeValue<string>("category"),item.AttributeValue<int>("amount")});
        }
    }
    return result;
}
