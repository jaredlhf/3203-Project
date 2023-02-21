#include "TNode.h"
#include "DesignExtractor.h"
#include "SelectiveExtractor.h"


StmtLstNode::StmtLstNode(std::vector<std::shared_ptr<StmtNode>> stmts) {
    statements = stmts;
}

void StmtLstNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<StmtLstNode> node = std::dynamic_pointer_cast<StmtLstNode>(shared_from_this());
    extractor->visit(node, SPConstants::INVALID_LINE_NO);
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
    std::shared_ptr<AssignNode> node = std::dynamic_pointer_cast<AssignNode>(shared_from_this());
    extractor->visit(node, SPConstants::INVALID_LINE_NO);
}

void AssignNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
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
    extractor->visit(node, SPConstants::INVALID_LINE_NO);
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
    extractor->visit(node, SPConstants::INVALID_LINE_NO);
}

void PrintNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<PrintNode> node = std::dynamic_pointer_cast<PrintNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> PrintNode::getChildren() {
    return std::vector<std::shared_ptr<TNode>>();
}

CallNode::CallNode(int line, const std::string& var) {
    variable = var;
    lineNo = line;
}

void CallNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<CallNode> node = std::dynamic_pointer_cast<CallNode>(shared_from_this());
    extractor->visit(node, SPConstants::INVALID_LINE_NO);
}

void CallNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<CallNode> node = std::dynamic_pointer_cast<CallNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> CallNode::getChildren() {
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
    extractor->visit(node, SPConstants::INVALID_LINE_NO);
}

void IfNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<IfNode> node = std::dynamic_pointer_cast<IfNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> IfNode::getChildren() {
    std::vector<std::shared_ptr<TNode>> children;
    children.push_back(ifLst);
    children.push_back(elseLst);
    return children;
}

WhileNode::WhileNode(int line, const std::string& condExp, std::shared_ptr<StmtLstNode> stmtList) {
    condExpr = condExp;
    stmtLst = stmtList;
    lineNo = line;
}

void WhileNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<WhileNode> node = std::dynamic_pointer_cast<WhileNode>(shared_from_this());
    extractor->visit(node, SPConstants::INVALID_LINE_NO);
}

void WhileNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<WhileNode> node = std::dynamic_pointer_cast<WhileNode>(shared_from_this());
    selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> WhileNode::getChildren() {
    std::vector<std::shared_ptr<TNode>> children;
    children.push_back(stmtLst);
    return children;
}


ProcedureNode::ProcedureNode(std::shared_ptr<StmtLstNode> stmtList, std::string proc) {
    stmtLst = stmtList;
    proc = proc;
}

void ProcedureNode::accept(std::shared_ptr<DesignExtractor> extractor) {
    std::shared_ptr<ProcedureNode> node = std::dynamic_pointer_cast<ProcedureNode>(shared_from_this());
    extractor->visit(node, SPConstants::INVALID_LINE_NO);
}

void ProcedureNode::accept(std::shared_ptr<SelectiveExtractor> selectiveExtractor) {
    std::shared_ptr<ProcedureNode> node = std::dynamic_pointer_cast<ProcedureNode>(shared_from_this());
    //selectiveExtractor->visit(node);
}

std::vector<std::shared_ptr<TNode>> ProcedureNode::getChildren() {
    std::vector<std::shared_ptr<TNode>> children;
    children.push_back(stmtLst);
    return children;
}