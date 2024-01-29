
#include <vector>
#include <istream>
#include <string>

#include "json.h"

using namespace std;

struct Spending {
    string category;
    int amount;
};

vector<Spending> LoadFromJson(istream& input) {
    vector<Spending>  result;
    Document doc = Load(input);
    for(const auto& node: doc.GetRoot().AsArray()){
        result.push_back({node.AsMap().at("category").AsString(),node.AsMap().at("amount").AsInt()});
    }
    return result;
}