#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison& cmd, const Date& date) {
};

EventComparisonNode::EventComparisonNode(const Comparison& cmd, const string& value) {
};

LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation, const shared_ptr<Node> left, const shared_ptr<Node> right) {
};
