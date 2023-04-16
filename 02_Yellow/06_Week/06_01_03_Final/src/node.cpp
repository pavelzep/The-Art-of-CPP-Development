#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison& cmd, const Date& date):cmd_(cmd), date_(date) {
};

EventComparisonNode::EventComparisonNode(const Comparison& cmd, const string& value):cmd_(cmd), value_(value) {
};

LogicalOperationNode::LogicalOperationNode(
    const LogicalOperation& logical_operation,
    const shared_ptr<Node> left,
    const shared_ptr<Node> right): logical_operation_(logical_operation), left_(left), right_(right) {
};
