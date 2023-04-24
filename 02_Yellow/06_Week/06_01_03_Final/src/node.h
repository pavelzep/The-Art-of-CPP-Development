#include "date.h"
#include <memory>

#pragma once

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const string& str) const = 0;
    
};

class EmptyNode: public Node {
public:
    EmptyNode();
    bool Evaluate(const Date& date, const string& str) const override;
};

class LogicalOperationNode: public Node {
public:
    LogicalOperationNode(
        const LogicalOperation& logical_operation,
        const shared_ptr<Node> left,
        const shared_ptr<Node> right);

    bool Evaluate(const Date& date, const string& str) const override;

    const LogicalOperation logical_operation_;
    const shared_ptr<Node> left_;
    const shared_ptr<Node> right_;
};

class DateComparisonNode: public Node {
public:
    DateComparisonNode(const Comparison& cmd, const Date& date);

    bool Evaluate(const Date& date, const string& str) const override;

    const Comparison cmd_;
    const Date date_;

};

class EventComparisonNode: public Node {
public:
    EventComparisonNode(const Comparison& cmd, const string& value);

    bool Evaluate(const Date& date, const string& str) const override;
    const Comparison cmd_;
    const string value_;
};




