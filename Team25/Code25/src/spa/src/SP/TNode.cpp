#include "TNode.h"
#include "DesignExtractor.h"
#include "SelectiveExtractor.h"


StmtLstNode::StmtLstNode(std::vector<std::shared_ptr<StmtNode>> stmts) {
    statements = stmts;
}

void StmtLstNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<StmtLstNode> node = std::dynamic_pointer_cast<StmtLstNode>(shared_from_this());
    extractor->visit(node);
}

void StmtLstNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<StmtLstNode> node = std::dynamic_pointer_cast<StmtLstNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> StmtLstNode::getChildren() {
    std::vector<std::shared_ptr<TNode>> children;
    for (const auto& statement : statements) {
        children.push_back(statement);
    }
    return children;
}

AssignNode::AssignNode(int line, const std::string& var, const std::string& expr)  {
    variable = var;
    expression = expr;
    lineNo = line;
}

void AssignNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::cout << "assign accept E" << std::endl;
    std::shared_ptr<AssignNode> node = std::dynamic_pointer_cast<AssignNode>(shared_from_this());
    extractor->visit(node);
}

void AssignNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::cout << "assign accept SE" << std::endl;
    std::shared_ptr<AssignNode> node = std::dynamic_pointer_cast<AssignNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> AssignNode::getChildren() {
    return std::vector<std::shared_ptr<TNode>>();
}

ReadNode::ReadNode(int line, const std::string& var) {
    variable = var;
    lineNo = line;
}

void ReadNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<ReadNode> node = std::dynamic_pointer_cast<ReadNode>(shared_from_this());
    extractor->visit(node);
}

void ReadNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<ReadNode> node = std::dynamic_pointer_cast<ReadNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> ReadNode::getChildren() {
    return std::vector<std::shared_ptr<TNode>>();
}

PrintNode::PrintNode(int line, const std::string& var) {
    variable = var;
    lineNo = line;
}

void PrintNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<PrintNode> node = std::dynamic_pointer_cast<PrintNode>(shared_from_this());
    extractor->visit(node);
}

void PrintNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<PrintNode> node = std::dynamic_pointer_cast<PrintNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> PrintNode::getChildren() {
    return std::vector<std::shared_ptr<TNode>>();
}

IfNode::IfNode(int line, const std::string& condExp, std::shared_ptr<StmtLstNode> ifList, std::shared_ptr<StmtLstNode> elseList) {
   condExpr = condExp;
   ifLst = ifList;
   elseLst = elseList;
   lineNo = line;
}

void IfNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<IfNode> node = std::dynamic_pointer_cast<IfNode>(shared_from_this());
    extractor->visit(node);
}

void IfNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<IfNode> node = std::dynamic_pointer_cast<IfNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> IfNode::getChildren() {
    std::vector<std::shared_ptr<TNode>> ifs = ifLst->getChildren();
    std::vector<std::shared_ptr<TNode>> els = elseLst->getChildren();
    ifs.insert(ifs.end(), els.begin(), els.end());
    return ifs;
}

WhileNode::WhileNode(int line, const std::string& condExp, std::shared_ptr<StmtLstNode> stmtList) {
    condExpr = condExp;
    stmtLst = stmtList;
    lineNo = line;
}

void WhileNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<WhileNode> node = std::dynamic_pointer_cast<WhileNode>(shared_from_this());
    extractor->visit(node);
}

void WhileNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<WhileNode> node = std::dynamic_pointer_cast<WhileNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> WhileNode::getChildren() {
    return stmtLst->getChildren();
}


ProcedureNode::ProcedureNode(std::shared_ptr<StmtLstNode> stmtList) {
    stmtLst = stmtList;
}

void ProcedureNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<ProcedureNode> node = std::dynamic_pointer_cast<ProcedureNode>(shared_from_this());
    extractor->visit(node);
}

void ProcedureNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<ProcedureNode> node = std::dynamic_pointer_cast<ProcedureNode>(shared_from_this());
    //selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> ProcedureNode::getChildren() {
    return stmtLst->getChildren();
}