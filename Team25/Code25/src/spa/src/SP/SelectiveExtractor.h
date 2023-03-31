#ifndef SPA_SELECTIVEEXTRACTOR_H
#define SPA_SELECTIVEEXTRACTOR_H

#include <stack>
#include <set>

#include "DesignExtractor.h"
#include "TNode.h"
#include "CFGNode.h"
#include "PKB/PkbPopulator.h"

class SelectiveExtractor: public std::enable_shared_from_this<SelectiveExtractor> {
public:
    SelectiveExtractor(std::shared_ptr<PkbPopulator> pkbPopulator);
    void visit(std::shared_ptr<AssignNode> n);
    void visit(std::shared_ptr<PrintNode> n);
    void visit(std::shared_ptr<ReadNode> n);
    void visit(std::shared_ptr<CallNode> n);
    void visit(std::shared_ptr<IfNode> n);
    void visit(std::shared_ptr<WhileNode> n);
    void visit(std::shared_ptr<StmtLstNode> n);
    void visit(std::shared_ptr<ProcedureNode> n);
    void visitProgramTree(std::shared_ptr<TNode> root);
    void visitCFG(std::shared_ptr<CFGNode> root, std::string procName);

private:
    std::shared_ptr<ModifiesExtractor> modifiesExtractor;
    std::shared_ptr<UsesExtractor> usesExtractor;
    std::shared_ptr<FollowsExtractor> followsExtractor;
    std::shared_ptr<FollowsStarExtractor> followsStarExtractor;
    std::shared_ptr<ParentsExtractor> parentsExtractor;
    std::shared_ptr<ParentsStarExtractor> parentsStarExtractor;
    std::shared_ptr<CallsExtractor> callsExtractor;
    std::shared_ptr<CallsStarExtractor> callsStarExtractor;
    std::shared_ptr<PatternExtractor> patternExtractor;
    std::shared_ptr<AttributeExtractor> attrExtractor;
    std::shared_ptr<ProcedureCallsExtractor> procCallsExtractor;
    std::shared_ptr<StatementExtractor> stmtExtractor;
    std::shared_ptr<PkbPopulator> pkbPopulator;
};
#endif //SPA_SELECTIVEEXTRACTOR_H
