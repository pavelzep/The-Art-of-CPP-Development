#include "rectangle.h"
#include <iostream>
int main() {
    Rectangle r(8, 8);
    std::cout << r.GetPerimeter() << " " << r.GetArea() << std::endl;
    return 0;
}