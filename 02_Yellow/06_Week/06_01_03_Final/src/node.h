
#pragma once
enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};




class Node {
public:
    void Evaluate();
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


