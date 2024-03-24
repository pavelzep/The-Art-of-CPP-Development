#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

// template <typename T>
class Figure : public IShape {
public:
    // std::unique_ptr<IShape> Clone() const {
    // }

    void SetPosition(Point position) final { this->position_ = position; }
    Point GetPosition() const final { return position_; }
    void SetSize(Size size) final { this->size_ = size; }
    Size GetSize() const final { return size_; }
    void SetTexture(std::shared_ptr<ITexture> texture) final { this->texture_ = texture; }
    ITexture* GetTexture() const final { return texture_.get(); }

    // void SetType(ShapeType shape_type)  { this->shape_type_ = shape_type; }
    // ShapeType GetType() const { return shape_type_; }

private:
    Point position_;
    Size size_;
    std::shared_ptr<ITexture> texture_;
    // ShapeType shape_type_;
};

class Rectangle : public Figure {
public:
    std::unique_ptr<IShape> Clone() const final {
        auto clone = make_unique<Rectangle>();
        clone.get()->SetPosition(this->GetPosition());
        clone.get()->SetSize(this->GetSize());
        clone.get()->SetTexture(shared_ptr<ITexture>(this->GetTexture()));
        return clone;
    }

    void Draw(Image& im) const override {

        Size im_size = { static_cast<int>(im.at(0).size()), static_cast<int>(im.size()) };
        Size t_size = GetSize();
        Point t_offset = GetPosition();
        


    }
};

class Ellipse : public Figure {
public:
    std::unique_ptr<IShape> Clone() const final {
        auto clone = make_unique<Ellipse>();
        clone.get()->SetPosition(this->GetPosition());
        clone.get()->SetSize(this->GetSize());
        clone.get()->SetTexture(shared_ptr<ITexture>(this->GetTexture()));
        return clone;
    }

    void Draw(Image&) const override {
    }

};

// template <typename T>
// unique_ptr<IShape> MakeShape(T shape_type) {
//     unique_ptr<IShape> Shape = make_unique<T>();
//     return Shape;
// }

unique_ptr<IShape> MakeShape(ShapeType shape_type) {
    unique_ptr<IShape> Shape;
    switch (shape_type) {
        case ShapeType::Rectangle: {
            Shape = make_unique<Rectangle>();
            // Shape.get()

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