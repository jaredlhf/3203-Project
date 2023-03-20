#ifndef SPA_CFGNODE_H
#define SPA_CFGNODE_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>

class CFGNode : public std::enable_shared_from_this<CFGNode> {
public:
    CFGNode();
    CFGNode(std::vector<int> lineNo);

    virtual std::vector<std::shared_ptr<CFGNode>> getAllNextNodes();
    virtual void findLeafNodes(std::unordered_set<std::shared_ptr<CFGNode>>& leafNodes);
    std::unordered_set<std::shared_ptr<CFGNode>> getAllLeafNodes();
    void setNextNodes(std::shared_ptr<CFGNode> next);
    std::vector<int> getLineNo() const;
    void addLineNo(int lineNo);

protected:
    std::vector<int> lineNo_;
    std::shared_ptr<CFGNode> next_;
};

class CFGIfNode :public CFGNode {
public:
    CFGIfNode(int lineNo);

    std::vector<std::shared_ptr<CFGNode>> getAllNextNodes() override;
    void findLeafNodes(std::unordered_set<std::shared_ptr<CFGNode>>& leafNodes) override;
    void setThenNode(std::shared_ptr<CFGNode> next);
    void setElseNode(std::shared_ptr<CFGNode> next);
private:
    std::shared_ptr<CFGNode> nextThen_;
    std::shared_ptr<CFGNode> nextElse_;
};


class CFGWhileNode :public CFGNode {
public:
    CFGWhileNode(int lineNo);

    std::vector<std::shared_ptr<CFGNode>> getAllNextNodes() override;
    void findLeafNodes(std::unordered_set<std::shared_ptr<CFGNode>>& leafNodes) override;
    void setLoopNode(std::shared_ptr<CFGNode> next);
private:
    std::shared_ptr<CFGNode> nextLoop_;
};

#endif //SPA_CFGNODE_H
