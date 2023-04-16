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
    bool Evaluate(const Date& date, const string& str) {
        return bool();
    }
};

class EmptyNode: public Node {
public:

};

class LogicalOperationNode: public Node {
public:
    LogicalOperationNode(
        const LogicalOperation& logical_operation,
        const shared_ptr<Node> left, const shared_ptr<Node> right);

    const LogicalOperation logical_operation_;
    const shared_ptr<Node> left_;
    const shared_ptr<Node> right_;
};

class DateComparisonNode: public Node {
public:
    DateComparisonNode(const Comparison& cmd, const Date& date);

    const Comparison cmd_;
    const Date date_;


};

class EventComparisonNode: public Node {
public:
    EventComparisonNode(const Comparison& cmd, const string& value);
    const Comparison cmd_;
    const string value_;
};




