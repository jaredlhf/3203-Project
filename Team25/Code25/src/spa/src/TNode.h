#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class TNode
{
public:
    void accept();
};

class AssignNode: public TNode {
public:
    AssignNode(std::string variable, std::string expression);

private:
    std::string variable;
    std::string expression;
};

class StmtNode: public TNode {
public:
    StmtNode(AssignNode a);

private:
    AssignNode assign;
};

class StmtLstNode: public TNode {
public:
    StmtLstNode(std::vector<StmtNode> stmts);

private:
    std::vector<StmtNode> statements;
};

class ProcedureNode: public TNode {
public:
    ProcedureNode(StmtLstNode stmtLst);

private:
    StmtLstNode statementList;
};




