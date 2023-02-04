#pragma once

#include <string>
#include <iostream>

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
    StmtLstNode(StmtNode stmt);

private:
    StmtNode statement;
};

class ProcedureNode: public TNode {
public:
    ProcedureNode(StmtLstNode stmtLst);

private:
    StmtLstNode statementList;
};




