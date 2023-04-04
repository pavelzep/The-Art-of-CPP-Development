
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

class Figure {
public:
    Figure(string& name, vector<int>& params): name_(name), params_(params) {

    };

    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
protected:
    string name_;
    vector<int> params_;
};

class Triangle: public Figure {
public:
    Triangle(string& name, vector<int>& params): Figure(name, params) {

    };

    string Name() const override {
        return name_;
    };
    double Perimeter()const override {
        return  params_.at(0) + params_.at(1) + params_.at(2);
    };
    double Area() const override {
        double p = (params_.at(0) + params_.at(1) + params_.at(2)) / 2.;
        return sqrt(p * (p - params_.at(0)) * (p - params_.at(1)) * (p - params_.at(2)));
    };
private:

};

class Rect: public Figure {
public:
    Rect(string& name, vector<int>& params): Figure(name, params) {

    };
    string Name() const override {
        return name_;
    };

    double Perimeter() const override {
        return (params_.at(0) + params_.at(1)) * 2;
    };

    double Area() const override {
        return params_.at(0) * params_.at(1);
    };
private:

};

class Circle: public Figure {
public:
    Circle(string& name, vector<int>& params): Figure(name, params) {

    };
    string Name() const override {
        return name_;
    };
    double Perimeter() const override {
        return params_.at(0) * 2 * 3.14;
    };
    double Area() const  override {
        return params_.at(0) * params_.at(0) * 3.14;
    };
private:
    int a_;
};




istringstream& operator >> (istringstream& is, vector<int>& vect) {
    int t;
    while (is >> t) {
        vect.push_back(t);
    }
    return is;
}

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string name;
    is >> name;
    vector<int> params;
    is >> params;
    shared_ptr<Figure> figure_;
    if (name == "RECT") {
        figure_ = make_shared<Rect>(name, params);
    } else if (name == "TRIANGLE") {
        figure_ = make_shared<Triangle>(name, params);
    } else  if (name == "CIRCLE") {
        figure_ = make_shared<Circle>(name, params);
    }

    return figure_;
}

int main() {


    fstream cin("../input.txt");

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