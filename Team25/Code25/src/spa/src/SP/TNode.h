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

class StmtNode: public TNode {
private:
};

class AssignNode: public StmtNode {
public:
    AssignNode(std::string variable, std::string expression);

private:
    std::string variable;
    std::string expression;
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




