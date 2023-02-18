#ifndef SPA_SELECTIVEEXTRACTOR_H
#define SPA_SELECTIVEEXTRACTOR_H

#include "DesignExtractor.h"
#include "TNode.h"

class SelectiveExtractor {
public:
    SelectiveExtractor();
    void visit(std::shared_ptr<AssignNode> n);
    void visit(std::shared_ptr<PrintNode> n);
    void visit(std::shared_ptr<ReadNode> n);
    void visit(std::shared_ptr<IfNode> n);
    void visit(std::shared_ptr<WhileNode> n);
    void visit(std::shared_ptr<StmtLstNode> n);
    void visit(std::shared_ptr<ProcedureNode> n);


private:
    std::shared_ptr<ModifiesExtractor> modifiesExtractor;
    std::shared_ptr<UsesExtractor> usesExtractor;
    std::shared_ptr<FollowsExtractor> followsExtractor;
    std::shared_ptr<FollowsStarExtractor> followsStarExtractor;
    std::shared_ptr<ParentsExtractor> parentsExtractor;
    std::shared_ptr<ParentsStarExtractor> parentsStarExtractor;
};
#endif //SPA_SELECTIVEEXTRACTOR_H
