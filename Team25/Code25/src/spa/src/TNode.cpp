#include "TNode.h"


void TNode::accept() {
    cout << "accept()" << endl;
}

AssignNode::AssignNode(string var, string expr) : variable(var), expression(expr) {}

StmtNode::StmtNode(AssignNode a) : assign(a) {}


StmtLstNode::StmtLstNode(StmtNode stmt) : statement(stmt){}

ProcedureNode::ProcedureNode(StmtLstNode stmtLst) : statementList(stmtLst){}