#include <string>
#include <vector>
using namespace std;


#define b(x) var##x 
#define a(x) b(x)
#define UNIQ_ID a(__LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = { "hello", "world" };
    vector<int> UNIQ_ID = { 1, 2, 3, 4 };
}