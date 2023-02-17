#include "SelectiveExtractor.h"

SelectiveExtractor::SelectiveExtractor() {
    modifiesExtractor = make_shared<ModifiesExtractor>();
    usesExtractor = make_shared<UsesExtractor>();
    followsExtractor = make_shared<FollowsExtractor>();
    followsStarExtractor = make_shared<FollowsStarExtractor>();
    parentsExtractor = make_shared<ParentsExtractor>();
    parentsStarExtractor = make_shared<ParentsStarExtractor>();
}

void SelectiveExtractor::visit(std::shared_ptr<AssignNode> n) {
    std::cout << "assign visit SE" << std::endl;
    n->accept(modifiesExtractor);
    n->accept(usesExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<PrintNode> n) {
    n->accept(usesExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<ReadNode> n) {
    n->accept(modifiesExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<IfNode> n) {
    n->accept(usesExtractor);
    n->accept(modifiesExtractor);
    n->accept(parentsExtractor);
    n->accept(parentsStarExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<WhileNode> n) {
    n->accept(usesExtractor);
    n->accept(modifiesExtractor);
    n->accept(parentsExtractor);
    n->accept(parentsStarExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<StmtLstNode> n) {
    std::cout << "visit StmtLst SE" <<std::endl;
    n->accept(followsExtractor);
    n->accept(followsStarExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<ProcedureNode> n) {

}