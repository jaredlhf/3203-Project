#include "SelectiveExtractor.h"

SelectiveExtractor::SelectiveExtractor(
    std::shared_ptr<PkbPopulator> populator) {
  modifiesExtractor = make_shared<ModifiesExtractor>(populator);
  usesExtractor = make_shared<UsesExtractor>(populator);
  followsExtractor = make_shared<FollowsExtractor>(populator);
  followsStarExtractor = make_shared<FollowsStarExtractor>(populator);
  parentsExtractor = make_shared<ParentsExtractor>(populator);
  parentsStarExtractor = make_shared<ParentsStarExtractor>(populator);
  callsExtractor = make_shared<CallsExtractor>(populator);
  callsStarExtractor = make_shared<CallsStarExtractor>(populator);
  patternExtractor = make_shared<PatternExtractor>(populator);
  attrExtractor = make_shared<AttributeExtractor>(populator);
  stmtExtractor = make_shared<StatementExtractor>(populator);
}

void SelectiveExtractor::visit(std::shared_ptr<AssignNode> n) {
  n->accept(modifiesExtractor);
  n->accept(usesExtractor);
  n->accept(stmtExtractor);
  n->accept(patternExtractor);
  n->accept(attrExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<PrintNode> n) {
  n->accept(usesExtractor);
  n->accept(stmtExtractor);
  n->accept(attrExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<ReadNode> n) {
  n->accept(modifiesExtractor);
  n->accept(stmtExtractor);
  n->accept(attrExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<CallNode> n) {
  n->accept(modifiesExtractor);
  n->accept(usesExtractor);
  n->accept(stmtExtractor);
  n->accept(callsExtractor);
  n->accept(callsStarExtractor);
  n->accept(attrExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<IfNode> n) {
  n->accept(usesExtractor);
  n->accept(modifiesExtractor);
  n->accept(parentsExtractor);
  n->accept(parentsStarExtractor);
  n->accept(callsExtractor);
  n->accept(callsStarExtractor);
  n->accept(attrExtractor);
  n->accept(patternExtractor);
  n->accept(stmtExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<WhileNode> n) {
  n->accept(usesExtractor);
  n->accept(modifiesExtractor);
  n->accept(parentsExtractor);
  n->accept(parentsStarExtractor);
  n->accept(callsExtractor);
  n->accept(callsStarExtractor);
  n->accept(attrExtractor);
  n->accept(patternExtractor);
  n->accept(stmtExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<StmtLstNode> n) {
  n->accept(followsExtractor);
  n->accept(followsStarExtractor);
}

void SelectiveExtractor::visit(std::shared_ptr<ProcedureNode> n) {
  n->accept(modifiesExtractor);
  n->accept(usesExtractor);
  n->accept(attrExtractor);
}

void SelectiveExtractor::visitProgramTree(std::shared_ptr<TNode> root) {
  std::stack<shared_ptr<TNode>> stack;
  stack.push(root);
  while (!stack.empty()) {
    std::shared_ptr<TNode> node = stack.top();
    stack.pop();
    node->accept(shared_from_this());

    for (const auto child : node->getChildren()) {
      stack.push(child);
    }
  }
}

void SelectiveExtractor::visitCFG(std::shared_ptr<CFGNode> root) {
  std::set<std::shared_ptr<CFGNode>> visited;
  std::stack<std::shared_ptr<CFGNode>> stack;
  if (root != nullptr) {
    stack.push(root);
  }

  while (!stack.empty()) {
    auto curr = stack.top();
    stack.pop();

    if (curr == nullptr || curr->getLineNo().empty() ||
        (visited.find(curr) != visited.end())) {
      continue;
    }

    visited.insert(curr);

    for (auto child : curr->getAllNextNodes()) {
      if (child == nullptr) {
        continue;
      }

      auto childLineNo = child->getLineNo();
      if (!childLineNo.empty()) {
        std::cout << "populating Next: (" << curr->getLineNo().back() << ", "
                  << childLineNo.front() << ") " << std::endl;
      }
      stack.push(child);
    }

    auto lineNo = curr->getLineNo();
    if (lineNo.size() >= 2) {
      for (int i = 0; i < lineNo.size() - 1; i++) {
        std::cout << "populating Next: (" << lineNo[i] << ", " << lineNo[i + 1]
                  << ") " << std::endl;
      }
    }
  }
}