#include "TNode.h"


void TNode::accept() {
    std::cout << "accept()" << std::endl;
}

AssignNode::AssignNode(std::string var, std::string expr) : variable(var), expression(expr) {}

StmtNode::StmtNode(AssignNode a) : assign(a) {}

StmtLstNode::StmtLstNode(std::vector<StmtNode> stmts) : statements(stmts){}

ProcedureNode::ProcedureNode(StmtLstNode stmtLst) : statementList(stmtLst){}