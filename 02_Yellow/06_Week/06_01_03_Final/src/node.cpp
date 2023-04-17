#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison& cmd, const Date& date): Node(NodeType::DateComparisonNode_), cmd_(cmd), date_(date) {
};

EventComparisonNode::EventComparisonNode(const Comparison& cmd, const string& value):Node(NodeType::EventComparisonNode_), cmd_(cmd), value_(value) {
};

LogicalOperationNode::LogicalOperationNode(
    const LogicalOperation& logical_operation,
    const shared_ptr<Node> left,
    const shared_ptr<Node> right):Node(NodeType::LogicalOperationNode_), logical_operation_(logical_operation), left_(left), right_(right) {
};

EmptyNode::EmptyNode(): Node(NodeType::EmptyNode_) {

};

bool Node::Evaluate(const Date& date, const string& str) {
    NodeType t = this->node_type;
    switch (t) {
        case NodeType::EmptyNode_:
            return false;
            break;

        case NodeType::LogicalOperationNode_:
            return false;
            break;

        case NodeType::DateComparisonNode_:
        { DateComparisonNode* node_p = static_cast<DateComparisonNode*>(this);
        auto cmd__ = node_p->cmd_;
        auto date__ = node_p->date_;
        return false;
        break;
        }
        case NodeType::EventComparisonNode_:
            return false;
            break;

        default:
            break;
    }
    return false;
}

Node::Node(): node_type(NodeType::EmptyNode_) {
}

Node::Node(NodeType node_type_): node_type(node_type_) {
}
