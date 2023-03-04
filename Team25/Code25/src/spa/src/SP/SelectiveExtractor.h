#ifndef SPA_SELECTIVEEXTRACTOR_H
#define SPA_SELECTIVEEXTRACTOR_H

#include <stack>

#include "DesignExtractor.h"
#include "TNode.h"
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

private:
    std::shared_ptr<ModifiesExtractor> modifiesExtractor;
    std::shared_ptr<UsesExtractor> usesExtractor;
    std::shared_ptr<FollowsExtractor> followsExtractor;
    std::shared_ptr<FollowsStarExtractor> followsStarExtractor;
    std::shared_ptr<ParentsExtractor> parentsExtractor;
    std::shared_ptr<ParentsStarExtractor> parentsStarExtractor;
    std::shared_ptr<CallsExtractor> callsExtractor;
    std::shared_ptr<CallsStarExtractor> callsStarExtractor;
    std::shared_ptr<StatementExtractor> stmtExtractor;

};
#endif //SPA_SELECTIVEEXTRACTOR_H
