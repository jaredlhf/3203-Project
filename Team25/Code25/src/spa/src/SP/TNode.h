#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class TNode
{
public:
    virtual void print() const {};
};

class StmtNode: public TNode {
public:
    virtual void accept() { std::cout << "stmt" <<endl; };
protected:
    int lineNo;
};

class StmtLstNode: public TNode {
public:
    StmtLstNode(std::vector<std::shared_ptr<StmtNode>> stmts);
    std::vector<std::shared_ptr<StmtNode>> getStatements() {
        return this->statements;
    };

    virtual void print() const override{ std::cout << "stmtLst" <<endl; }
private:
    std::vector<std::shared_ptr<StmtNode>> statements;

};

class AssignNode: public StmtNode {
public:
    AssignNode(int lineNo, const std::string& variable, const std::string& expression);
    void accept() override { std::cout << "assign" << std::endl; };
    void print() const override{ std::cout << "Assign"  <<endl; }
private:
    std::string variable;
    std::string expression;
};

class ReadNode: public StmtNode {
public:
    ReadNode(int lineNo, const std::string& var);
    void accept() override{ std::cout << "read" << endl; }
    void print() const override{ std::cout << "read" <<endl; }
private:
    std::string variable;
};

class PrintNode: public StmtNode {
public:
    PrintNode(int lineNo, const std::string& var);
    void accept() override{ std::cout << "print" << endl; }
    void print() const override{ std::cout << "print" <<endl; }
private:
    std::string variable;
};

class IfNode: public StmtNode {
public:
    IfNode(int lineNo, const std::string& condExpr, std::shared_ptr<StmtLstNode> ifLst, std::shared_ptr<StmtLstNode> elseLst);
    void accept() override{ std::cout << "if" << endl; }
    void print() const override{ std::cout << "if" <<endl; }
private:
    std::string condExpr;
    std::shared_ptr<StmtLstNode> ifLst;
    std::shared_ptr<StmtLstNode> elseLst;

};

class WhileNode: public StmtNode {
public:
    WhileNode(int lineNo, const std::string& condExpr, std::shared_ptr<StmtLstNode> stmtLst);
    void accept() override { std::cout << "while" << endl; }
    void print() const override{ std::cout << "while" <<endl; }
private:
    std::string condExpr;
    std::shared_ptr<StmtLstNode> stmtLst;
};



class ProcedureNode: public TNode {
public:
    ProcedureNode(std::shared_ptr<StmtLstNode> stmtLst);
    std::shared_ptr<StmtLstNode> getStmtLst() {
        return this->stmtLst;
    };
    void print() const override{ std::cout << "proc" <<endl;  }
private:
    std::shared_ptr<StmtLstNode> stmtLst;
};




