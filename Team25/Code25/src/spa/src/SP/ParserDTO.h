#ifndef SPA_PARSERDTO_H
#define SPA_PARSERDTO_H
#include <memory>
#include <iostream>

class TNode; //forward declaration
class CFGNode; //forward declaration


class ParserDTO {
public:
    ParserDTO(std::shared_ptr<TNode> tNode, int lineNo) : tNode_(tNode), lineNo_(lineNo) {}
    ParserDTO(std::shared_ptr<TNode> tNode, std::shared_ptr<CFGNode> cfgNode) : tNode_(tNode), cfgNode_(cfgNode) {}
    ParserDTO(std::shared_ptr<TNode> tNode, std::shared_ptr<CFGNode> cfgNode, std::string procName) : tNode_(tNode), cfgNode_(cfgNode), procName_(procName) {}

    std::shared_ptr<TNode> getNode() const { return tNode_; }
    int getLine() const { return lineNo_; }
    std::shared_ptr<CFGNode> getCFGNode() const { return cfgNode_; }
    std::string getProcName() const { return procName_; }

private:
    std::shared_ptr<TNode> tNode_;
    int lineNo_;
    std::shared_ptr<CFGNode> cfgNode_;
    std::string procName_;
};

#endif //SPA_PARSERDTO_H
