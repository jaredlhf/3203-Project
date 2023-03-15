#include <memory>
#include "CFGNode.h"

CFGNode::CFGNode() : lineNo_(std::vector<int>()){}

CFGNode::CFGNode(std::vector<int> lineNo) : lineNo_(lineNo){}


void CFGNode::findLeafNodes(std::unordered_set<std::shared_ptr<CFGNode>>& leafNodes) {
    if (next_ == nullptr || next_->getLineNo().empty()) {
        leafNodes.insert(shared_from_this());
        return;
    }
    next_->findLeafNodes(leafNodes);
}

std::unordered_set<std::shared_ptr<CFGNode>> CFGNode::getAllLeafNodes() {
    std::unordered_set<std::shared_ptr<CFGNode>> leafNodes;
    findLeafNodes(leafNodes);
    return leafNodes;
}

void CFGNode::setNextNodes(std::shared_ptr<CFGNode> next) {
    std::unordered_set<std::shared_ptr<CFGNode>> leafNodes = getAllLeafNodes();

    for (auto leafNode : leafNodes) {
        leafNode->next_ = next;
    }
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


void CFGIfNode::findLeafNodes(std::unordered_set<std::shared_ptr<CFGNode>>& leafNodes) {
    nextThen_->findLeafNodes(leafNodes);
    nextElse_->findLeafNodes(leafNodes);
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

void CFGWhileNode::findLeafNodes(std::unordered_set<std::shared_ptr<CFGNode>>& leafNodes) {
    if (next_ == nullptr || next_->getLineNo().size() == 0) {
        leafNodes.insert(shared_from_this());
        return;
    }
    next_->findLeafNodes(leafNodes);
}


std::vector<std::shared_ptr<CFGNode>> CFGWhileNode::getAllNextNodes() {
    std::vector<std::shared_ptr<CFGNode>> nextNodes = std::vector<std::shared_ptr<CFGNode>>();
    nextNodes.push_back(next_);
    nextNodes.push_back(nextLoop_);
    return nextNodes;
}
