#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`


class Figure : public IShape {

    std::unique_ptr<IShape> Clone() const {

    }

    void SetPosition(Point position) { this->position_ = position; }
    Point GetPosition() const { return position_; }
    void SetSize(Size size) { this->size_ = size; }
    Size GetSize() const { return size_; }

    void SetTexture(std::shared_ptr<ITexture>) {
    }
    
    ITexture* GetTexture() const {
    }

    void Draw(Image&) const {
    }

private:
    Point position_;
    Size size_;
};

class Rectangle : public Figure {
public:

};

class Ellipse : public Figure {
public:

};

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    unique_ptr<IShape> Shape;
    switch (shape_type) {
        case ShapeType::Rectangle: {
            Shape = make_unique<Rectangle>();

            break;
        }
        case ShapeType::Ellipse: {
            Shape = make_unique<Ellipse>();
            break;
        }
        default:
            break;
    }
    return Shape;
}