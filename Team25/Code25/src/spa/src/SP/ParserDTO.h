#ifndef SPA_PARSERDTO_H
#define SPA_PARSERDTO_H

#include <iostream>

class TNode; //forward declaration
class CFGNode; //forward declaration


class ParserDTO {
public:
    ParserDTO(std::shared_ptr<TNode> tNode, int lineNo) : tNode_(tNode), lineNo_(lineNo) {}
    ParserDTO(std::shared_ptr<TNode> tNode, std::shared_ptr<CFGNode> cfgNode) : tNode_(tNode), cfgNode_(cfgNode) {}

    std::shared_ptr<TNode> getNode() const { return tNode_; }
    int getLine() const { return lineNo_; }
    std::shared_ptr<CFGNode> getCFGNode() const { return cfgNode_; }

private:
    std::shared_ptr<TNode> tNode_;
    int lineNo_;
    std::shared_ptr<CFGNode> cfgNode_;
};

#endif //SPA_PARSERDTO_H
