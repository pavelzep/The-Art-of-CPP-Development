#include "date.h"

#pragma once
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

class EventComparisonNode: public Node {
public:

};

class DateComparisonNode: public Node {
public:

};

class LogicalOperationNode: public Node {
public:

};




