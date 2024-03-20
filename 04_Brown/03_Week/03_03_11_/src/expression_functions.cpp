#include "common.h"


class ValueExpr : public Expression {
public:
    ValueExpr(int val) : value(val) {}

    int Evaluate() const override {
        return value;
    }

    std::string ToString() const override {
        return std::to_string(value);
    }
private:
    int value;

};

class BinarExpr : public Expression {
public:
    BinarExpr(ExpressionPtr lhs_, ExpressionPtr rhs_) : lhs(move(lhs_)), rhs(move(rhs_)) {}

    // std::string ToString() const override {
    //     return "(" + std::to_string(Evaluate()) + ")";
    // }
protected:
    ExpressionPtr lhs, rhs;
};

class SumExpr : public BinarExpr {
public:
    SumExpr(ExpressionPtr lhs_, ExpressionPtr rhs_) : BinarExpr(move(lhs_), move(rhs_)) {

    }
    int Evaluate() const override {
        return lhs.get()->Evaluate() + rhs.get()->Evaluate();
    }

    std::string ToString() const override {
        return "(" + lhs.get()->ToString() + ")+(" + rhs.get()->ToString() + ")";
    }

};
class ProdExpr : public BinarExpr {
public:
    ProdExpr(ExpressionPtr lhs_, ExpressionPtr rhs_) : BinarExpr(move(lhs_), move(rhs_)) {

    }
    int Evaluate() const override {
        return lhs.get()->Evaluate() * rhs.get()->Evaluate();
    }
    std::string ToString() const override {
        return "(" + lhs.get()->ToString() + ")*(" + rhs.get()->ToString() + ")";
    }

};



ExpressionPtr Value(int value) {
    return std::make_unique<ValueExpr>(value);
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return std::make_unique<SumExpr>(move(left), move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return std::make_unique<ProdExpr>(move(left), move(right));
}