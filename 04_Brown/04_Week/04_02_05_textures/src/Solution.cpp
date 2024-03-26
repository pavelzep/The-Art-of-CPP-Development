#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

inline bool IsPointInRectangle(Point p, Size size) {
    return ((p.x < size.width) && (p.y < size.height));
}

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
protected:
    std::shared_ptr<ITexture> texture_;
    // void FillByTextures() {

    // }
    // ShapeType shape_type_;
};

class Rectangle : public Figure {
public:
    std::unique_ptr<IShape> Clone() const final {
        auto clone = make_unique<Rectangle>();
        clone.get()->SetPosition(this->GetPosition());
        clone.get()->SetSize(this->GetSize());
        // clone.get()->SetTexture(shared_ptr<ITexture>(this->GetTexture()));
        clone.get()->SetTexture(texture_);
        return clone;
    }

    void Draw(Image& im) const override {

        Size im_size = { static_cast<int>(im.at(0).size()), static_cast<int>(im.size()) };
        Size figure_size = GetSize();
        Point figure_offset = GetPosition();
        Image figure(figure_size.height, string(figure_size.width, '.'));

        if (GetTexture()) {

            Size texture_size = GetTexture()->GetSize();
            Image texture = GetTexture()->GetImage();

            for (int y = 0; y < texture_size.height; y++) {
                // if (y <= figure_size.height) {
                for (int x = 0; x < texture_size.width; x++) {
                    // if (x < figure_size.width) {
                    if (IsPointInRectangle(Point{ x, y }, figure_size)) {
                        figure.at(y).at(x) = texture.at(y).at(x);
                    }
                }
                // }
            }
        }

        for (int y = 0; y < figure_size.height;y++) {
            if ((0 <= y + figure_offset.y) && (y + figure_offset.y < im_size.height)) {
                for (int x = 0; x < figure_size.width;x++) {
                    if ((0 <= x + figure_offset.x) && (x + figure_offset.x < im_size.width)) {
                        im.at(y + figure_offset.y).at(x + figure_offset.x) = figure.at(y).at(x);
                    }
                }
            }
        }

    }
};

class Ellipse : public Figure {
public:
    std::unique_ptr<IShape> Clone() const final {
        auto clone = make_unique<Ellipse>();
        clone.get()->SetPosition(this->GetPosition());
        clone.get()->SetSize(this->GetSize());
        clone.get()->SetTexture(texture_);
        return clone;
    }

    void Draw(Image& im) const override {

        Size im_size = { static_cast<int>(im.at(0).size()), static_cast<int>(im.size()) };
        Size figure_size = GetSize();
        Point figure_offset = GetPosition();
        Image figure(figure_size.height, string(figure_size.width, '.'));

        if (GetTexture()) {

            Size texture_size = GetTexture()->GetSize();
            Image texture = GetTexture()->GetImage();

            for (int y = 0; y < texture_size.height; y++) {
                // if (y <= figure_size.height) {
                for (int x = 0; x < texture_size.width; x++) {
                    // if (x < figure_size.width) {
                    if (IsPointInEllipse(Point{ x, y }, figure_size)) {
                        figure.at(y).at(x) = texture.at(y).at(x);
                    }
                }
                // }
            }
        }

        for (int y = 0; y < figure_size.height;y++) {
            if ((0 <= y + figure_offset.y) && (y + figure_offset.y < im_size.height)) {
                for (int x = 0; x < figure_size.width;x++) {
                    if ((0 <= x + figure_offset.x) && (x + figure_offset.x < im_size.width)) {
                        im.at(y + figure_offset.y).at(x + figure_offset.x) = figure.at(y).at(x);
                    }
                }
            }
        }

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
