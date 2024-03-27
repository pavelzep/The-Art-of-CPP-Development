#include "Common.h"

using namespace std;

inline bool IsPointInRectangle(Point p, Size size) {
    return ((p.x < size.width) && (p.y < size.height));
}

// using CheckFunction = bool(*)(Point, Size);

class Figure : public IShape {
public:
    void SetPosition(Point position) final { this->position_ = position; }
    Point GetPosition() const final { return position_; }
    void SetSize(Size size) final { this->size_ = size; }
    Size GetSize() const final { return size_; }
    void SetTexture(std::shared_ptr<ITexture> texture) final { this->texture_ = texture; }
    ITexture* GetTexture() const final { return texture_.get(); }

    void Draw(Image& im) const override {

        Size im_size = { static_cast<int>(im.at(0).size()), static_cast<int>(im.size()) };
        Size figure_size = GetSize();
        Point figure_offset = GetPosition();
        Image figure(figure_size.height, string(figure_size.width, '.'));

        if (GetTexture()) {
            Size texture_size = GetTexture()->GetSize();
            Image texture = GetTexture()->GetImage();

            for (int y = 0; y < texture_size.height; y++) {
                for (int x = 0; x < texture_size.width; x++) {
                    if (IsPointInFigure(Point{ x, y }, figure_size)) {
                        figure.at(y).at(x) = texture.at(y).at(x);
                    }
                }
            }
        }

        for (int y = 0; y < figure_size.height;y++) {
            if ((0 <= y + figure_offset.y) && (y + figure_offset.y < im_size.height)) {
                for (int x = 0; x < figure_size.width;x++) {
                    if ((0 <= x + figure_offset.x) && (x + figure_offset.x < im_size.width)) {
                        if (IsPointInFigure(Point{ x, y }, figure_size)) {
                            im.at(y + figure_offset.y).at(x + figure_offset.x) = figure.at(y).at(x);
                        }
                    }
                }
            }
        }
    }

private:
    Point position_;
    Size size_;
protected:
    std::shared_ptr<ITexture> texture_;
    virtual bool IsPointInFigure(Point p, Size size) const = 0;

};

class Rectangle : public Figure {
public:
    std::unique_ptr<IShape> Clone() const final {
        auto clone = make_unique<Rectangle>();
        clone.get()->SetPosition(this->GetPosition());
        clone.get()->SetSize(this->GetSize());
        clone.get()->SetTexture(texture_);
        return clone;
    }

    bool IsPointInFigure(Point p, Size size) const final {
        return IsPointInRectangle(p, size);
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

    bool IsPointInFigure(Point p, Size size) const final {
        return IsPointInEllipse(p, size);
    }
};

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