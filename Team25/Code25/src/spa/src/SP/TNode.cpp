#include "TNode.h"


void TNode::accept() {
    std::cout << "accept()" << std::endl;
}

StmtLstNode::StmtLstNode(std::vector<std::shared_ptr<StmtNode>> stmts) {
    statements = stmts;
}

ReadNode::ReadNode(int line, const std::string& var) {
    variable = var;
    lineNo = line;
}

PrintNode::PrintNode(int line, const std::string& var) {
    variable = var;
    lineNo = line;
}

IfNode::IfNode(int line, const std::string& condExp, std::shared_ptr<StmtLstNode> ifList, std::shared_ptr<StmtLstNode> elseList) {
   condExpr = condExp;
   ifLst = ifList;
   elseList = elseList;
   lineNo = line;
}

WhileNode::WhileNode(int line, const std::string& condExp, std::shared_ptr<StmtLstNode> stmtList) {
    condExpr = condExp;
    stmtLst = stmtList;
    lineNo = line;
}

AssignNode::AssignNode(int line, const std::string& var, const std::string& expr)  {
    variable = var;
    expression = expr;
    lineNo = line;
}

ProcedureNode::ProcedureNode(std::shared_ptr<StmtLstNode> stmtList) {
    stmtLst = stmtList;
}