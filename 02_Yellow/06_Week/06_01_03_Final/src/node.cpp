#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison& cmd, const Date& date): cmd_(cmd), date_(date) {
}

bool DateComparisonNode::Evaluate(const Date& date, const string& str) const {
    switch (this->cmd_) {
        case  Comparison::Less:
            return date < this->date_;
            break;
        case  Comparison::LessOrEqual:
            return  ((this->date_ == date) || (date < this->date_));
            break;
        case  Comparison::Greater:
            return  this->date_ < date;
            break;
        case  Comparison::GreaterOrEqual:
            return ((this->date_ == date) || (this->date_ < date));
            break;
        case  Comparison::Equal:
            return this->date_ == date;
            break;
        case  Comparison::NotEqual:
            return this->date_ != date;
            break;
        default:
            return false;
            break;
    }
};

EventComparisonNode::EventComparisonNode(const Comparison& cmd, const string& value): cmd_(cmd), value_(value) {
}

bool EventComparisonNode::Evaluate(const Date& date, const string& str)const {

    switch (this->cmd_) {
        case Comparison::Equal:
            return  str == this->value_;
            break;
        case Comparison::NotEqual:
            return str != this->value_;
            break;
        case  Comparison::Less:
            return str < this->value_;
            break;
        case  Comparison::LessOrEqual:
            return  str <= value_;
            break;
        case  Comparison::Greater:
            return  str > value_;
            break;
        case  Comparison::GreaterOrEqual:
            return str >= value_;
            break;

        default:
            return  false;
            break;
    }
};

LogicalOperationNode::LogicalOperationNode(
    const LogicalOperation& logical_operation,
    const shared_ptr<Node> left,
    const shared_ptr<Node> right): logical_operation_(logical_operation), left_(left), right_(right) {
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& str) const {

    bool left_ = this->left_->Evaluate(date, str);
    bool right_ = this->right_->Evaluate(date, str);
    bool res = true;
    switch (this->logical_operation_) {
        case LogicalOperation::Or:
            res = left_ || right_;
            break;
        case LogicalOperation::And:
            res = left_ && right_;
            break;
        default:
            break;
    }
    return res;
};

EmptyNode::EmptyNode() {
}

bool EmptyNode::Evaluate(const Date& date, const string& str)const {
    return true;
};
