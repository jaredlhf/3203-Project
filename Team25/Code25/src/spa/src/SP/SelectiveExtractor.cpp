#include "SelectiveExtractor.h"

SelectiveExtractor::SelectiveExtractor(std::shared_ptr<PkbPopulator> populator) {
    modifiesExtractor = make_shared<ModifiesExtractor>(populator);
    usesExtractor = make_shared<UsesExtractor>(populator);
    followsExtractor = make_shared<FollowsExtractor>(populator);
    followsStarExtractor = make_shared<FollowsStarExtractor>(populator);
    parentsExtractor = make_shared<ParentsExtractor>(populator);
    parentsStarExtractor = make_shared<ParentsStarExtractor>(populator);
}

void SelectiveExtractor::visit(std::shared_ptr<AssignNode> n) {
    //std::cout << "assign visit SE" << std::endl;
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
    //std::cout << "visit StmtLst SE" <<std::endl;
    n->accept(followsExtractor);
    n->accept(followsStarExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<ProcedureNode> n) {

}

void SelectiveExtractor::visitProgramTree(std::shared_ptr<TNode> root) {
    std::stack<shared_ptr<TNode>> stack;
    stack.push(root);
    while (!stack.empty()) {
        std::shared_ptr<TNode> node = stack.top();
        stack.pop();
        std::cout << " ---- visiting: " << node->print() << std::endl;
        node->accept(shared_from_this());

        for (const auto child: node->getChildren()) {
            //std::cout << "adding to stack" << node ->print() << std::endl;
            stack.push(child);
        }
    }

}