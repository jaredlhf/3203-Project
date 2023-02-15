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
protected:
    int lineNo;
};

class StmtLstNode: public TNode {
public:
    StmtLstNode(std::vector<std::shared_ptr<StmtNode>> stmts);

private:
    std::vector<std::shared_ptr<StmtNode>> statements;
};

class ReadNode: public StmtNode {
public:
    ReadNode(int lineNo, const std::string& var);
private:
    std::string variable;
};

class PrintNode: public StmtNode {
public:
    PrintNode(int lineNo, const std::string& var);
private:
    std::string variable;
};

class IfNode: public StmtNode {
public:
    IfNode(int lineNo, const std::string& condExpr, std::shared_ptr<StmtLstNode> ifLst, std::shared_ptr<StmtLstNode> elseLst);
private:
    std::string condExpr;
    std::shared_ptr<StmtLstNode> ifLst;
    std::shared_ptr<StmtLstNode> elseLst;

};

class WhileNode: public StmtNode {
public:
    WhileNode(int lineNo, const std::string& condExpr, std::shared_ptr<StmtLstNode> stmtLst);
private:
    std::string condExpr;
    std::shared_ptr<StmtLstNode> stmtLst;
};

class AssignNode: public StmtNode {
public:
    AssignNode(int lineNo, const std::string& variable, const std::string& expression);

private:
    std::string variable;
    std::string expression;
};

class ProcedureNode: public TNode {
public:
    ProcedureNode(std::shared_ptr<StmtLstNode> stmtLst);

private:
    std::shared_ptr<StmtLstNode> stmtLst;
};




