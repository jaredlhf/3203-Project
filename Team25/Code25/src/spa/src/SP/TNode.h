#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class TNode
{
public:
    virtual std::string print() const {return "tnode";};
};

class StmtNode: public TNode {
public:
    virtual void accept() { std::cout << "stmt" <<endl; };
    virtual int getLine() { return lineNo; };
protected:
    int lineNo;
};

class StmtLstNode: public TNode {
public:
    StmtLstNode(std::vector<std::shared_ptr<StmtNode>> stmts);
    std::vector<std::shared_ptr<StmtNode>> getStatements() {
        return this->statements;
    };
private:
    std::vector<std::shared_ptr<StmtNode>> statements;

};

class AssignNode: public StmtNode {
public:
    AssignNode(int lineNo, const std::string& variable, const std::string& expression);
    void accept() override { std::cout << "assign" << std::endl; };
    std::string print() const override {return "assign";};
    std::string getVar() { return this->variable; };
    std::string getExpr() { return this->expression; };
    int getLine() override { return lineNo; };
private:
    int lineNo;
    std::string variable;
    std::string expression;
};

class ReadNode: public StmtNode {
public:
    ReadNode(int lineNo, const std::string& var);
    void accept() override{ std::cout << "read" << endl; }
    std::string getVar() { return this->variable; };
    int getLine() override { return lineNo; };
private:
    int lineNo;
    std::string variable;
};

class PrintNode: public StmtNode {
public:
    PrintNode(int lineNo, const std::string& var);
    void accept() override{ std::cout << "print" << endl; }
    std::string getVar() { return this->variable; };
    int getLine() override { return lineNo; };
private:
    int lineNo;
    std::string variable;
};

class IfNode: public StmtNode {
public:
    IfNode(int lineNo, const std::string& condExpr, std::shared_ptr<StmtLstNode> ifLst, std::shared_ptr<StmtLstNode> elseLst);
    void accept() override{ std::cout << "if" << endl; }
    std::string getCondExpr() { return this->condExpr; };
    std::shared_ptr<StmtLstNode> getIfLst() { return this->ifLst; };
    std::shared_ptr<StmtLstNode> getElseLst() { return this->elseLst; };
    int getLine() override { return lineNo; };
private:
    int lineNo;
    std::string condExpr;
    std::shared_ptr<StmtLstNode> ifLst;
    std::shared_ptr<StmtLstNode> elseLst;

};

class WhileNode: public StmtNode {
public:
    WhileNode(int lineNo, const std::string& condExpr, std::shared_ptr<StmtLstNode> stmtLst);
    void accept() override { std::cout << "while" << endl; }
    std::string getCondExpr() { return this->condExpr; };
    std::shared_ptr<StmtLstNode> getStmtLst() { return this->stmtLst; };
    int getLine() override { return lineNo; };
private:
    int lineNo;
    std::string condExpr;
    std::shared_ptr<StmtLstNode> stmtLst;
};



class ProcedureNode: public TNode {
public:
    ProcedureNode(std::shared_ptr<StmtLstNode> stmtLst);
    std::shared_ptr<StmtLstNode> getStmtLst() {
        return this->stmtLst;
    };
//    void print() const override{ std::cout << "proc" <<endl;  }
private:
    std::shared_ptr<StmtLstNode> stmtLst;
};




