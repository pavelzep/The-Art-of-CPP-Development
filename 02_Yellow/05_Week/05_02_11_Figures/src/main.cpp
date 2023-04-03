
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>

using namespace std;

class Figure {
public:
    Figure(string& name): name_(name) {

    };
    virtual string Name() const = 0;
    virtual int Perimeter() const = 0;
    virtual int Area() const = 0;
protected:
    string name_;


};

class Triangle: public Figure {
public:
    Triangle(string& name, int a, int b, int c): Figure(name), a_(a), b_(b), c_(c) {

    };

    string Name() const override {

    };
    int Perimeter()const override {

    };
    int Area() const override {

    };
private:
    int a_;
    int b_;
    int c_;
};

class Rect: public Figure {
public:
    Rect(string& name, int a, int b): Figure(name), a_(a), b_(b) {

    };
    string Name() const override {

    };
    int Perimeter() const override {

    };
    int Area() const override {

    };
private:
    int a_;
    int b_;
};

class Circle: public Figure {
public:
    Circle(string& name, int a): Figure(name), a_(a) {

    };
    string Name() const override {

    };
    int Perimeter() const override {

    };
    int Area() const  override {

    };
private:
    int a_;
};

shared_ptr<Figure> CreateFigure(istringstream& _is) {
    return {};
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}