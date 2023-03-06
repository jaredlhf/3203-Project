#include "CFGNode.h"

CFGNode::CFGNode() : lineNo_(std::vector<int>()){}

CFGNode::CFGNode(std::vector<int> lineNo) : lineNo_(lineNo){}

void CFGNode::setNextNode(std::shared_ptr<CFGNode> next) {
    next_ = next;
}

std::vector<std::shared_ptr<CFGNode>> CFGNode::getAllNextNodes() {
    std::vector<std::shared_ptr<CFGNode>> nextNodes = std::vector<std::shared_ptr<CFGNode>>();
    nextNodes.push_back(next_);
    return nextNodes;
}

void CFGNode::addLineNo(int lineNo) {
    lineNo_.push_back(lineNo);
}

std::vector<int> CFGNode::getLineNo() const {
    return lineNo_;
}

CFGIfNode::CFGIfNode(int lineNo) {
    lineNo_ = std::vector<int>();
    addLineNo(lineNo);
}

std::vector<std::shared_ptr<CFGNode>> CFGIfNode::getAllNextNodes() {
    std::vector<std::shared_ptr<CFGNode>> nextNodes = std::vector<std::shared_ptr<CFGNode>>();
    nextNodes.push_back(nextThen_);
    nextNodes.push_back(nextElse_);
    return nextNodes;
}

void CFGIfNode::setNextNode(std::shared_ptr<CFGNode> next) {
    nextThen_->setNextNode(next);
    nextElse_->setNextNode(next);
}

void CFGIfNode::setThenNode(std::shared_ptr<CFGNode> next) {
    nextThen_ = next;
};

void CFGIfNode::setElseNode(std::shared_ptr<CFGNode> next) {
    nextElse_ = next;
};

CFGWhileNode::CFGWhileNode(int lineNo) {
    lineNo_ = std::vector<int>();
    addLineNo(lineNo);
}

void CFGWhileNode::setLoopNode(std::shared_ptr<CFGNode> next) {
    nextLoop_ = next;
}

std::vector<std::shared_ptr<CFGNode>> CFGWhileNode::getAllNextNodes() {
    std::vector<std::shared_ptr<CFGNode>> nextNodes = std::vector<std::shared_ptr<CFGNode>>();
    nextNodes.push_back(next_);
    nextNodes.push_back(nextLoop_);
    return nextNodes;
}
