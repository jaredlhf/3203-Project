#ifndef SPA_CFGNODE_H
#define SPA_CFGNODE_H

#include <iostream>
#include <vector>

class CFGNode {
public:
    CFGNode() : lineNo_(std::vector<int>()) {}
    CFGNode(std::vector<int> lineNo) : lineNo_(lineNo) {}

    //virtual std::shared_ptr<CFGNode> getNextNode() const { return next_; }
    virtual void setNextNode(std::shared_ptr<CFGNode> next) { next_ = next; }
    std::vector<int> getLineNo() const { return lineNo_; }
    void addLineNo(int lineNo) { lineNo_.push_back(lineNo); }

protected:
    std::vector<int> lineNo_;
    std::shared_ptr<CFGNode> next_;
};

class CFGIfNode :public CFGNode {
public:
    CFGIfNode(std::vector<int> lineNo)  { lineNo_ = lineNo; }
    void setNextNode(std::shared_ptr<CFGNode> next) override { nextThen_->setNextNode(next); nextElse_->setNextNode(next);  };
    void setThenNode(std::shared_ptr<CFGNode> next) {nextThen_ = next; };
    void setElseNode(std::shared_ptr<CFGNode> next) {nextElse_ = next; };
private:
    std::shared_ptr<CFGNode> nextThen_;
    std::shared_ptr<CFGNode> nextElse_;
};


class CFGWhileNode :public CFGNode {
public:
    CFGWhileNode(std::vector<int> lineNo)  { lineNo_ = lineNo; }
    void setLoopNode(std::shared_ptr<CFGNode> next) { nextLoop_ = next; };
private:
    std::shared_ptr<CFGNode> nextLoop_;
};

#endif //SPA_CFGNODE_H
