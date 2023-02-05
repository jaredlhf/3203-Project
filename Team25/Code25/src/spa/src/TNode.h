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
    AssignNode(string variable, string expression);

private:
    string variable;
    string expression;
};

class StmtNode: public TNode {
public:
    StmtNode(AssignNode a);

private:
    AssignNode assign;
};

class StmtLstNode: public TNode {
public:
    StmtLstNode(vector<StmtNode> stmts);

private:
    vector<StmtNode> statements;
};

class ProcedureNode: public TNode {
public:
    ProcedureNode(StmtLstNode stmtLst);

private:
    StmtLstNode statementList;
};




