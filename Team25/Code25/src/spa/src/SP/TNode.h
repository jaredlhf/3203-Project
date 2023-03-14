#pragma once

#include <string>
#include <iostream>
#include <vector>
#include<memory>
#include "SPConstants.h"

class DesignExtractor; //forward declaration
class SelectiveExtractor; //forward declaration

class TNode: public std::enable_shared_from_this<TNode>
{
public:
    virtual std::string print() const {return "tnode";};
    virtual void accept(std::shared_ptr<DesignExtractor> extractor) = 0;
    virtual void accept(std::shared_ptr<SelectiveExtractor> extractor) = 0;
    virtual std::vector<std::shared_ptr<TNode>> getChildren() = 0;
};

class StmtNode: public TNode {
public:
    virtual int getLine() { return lineNo; };
protected:
    int lineNo;
};

class StmtLstNode: public TNode {
public:
    StmtLstNode(std::vector<std::shared_ptr<StmtNode>> stmts, const std::string& proc);
    std::vector<std::shared_ptr<StmtNode>> getStatements() {
        return this->statements;
    };
    std::string getProc() {
        return this->name;
    }
    std::string print() const override {return "stmtLst node";};
    std::vector<std::shared_ptr<TNode>> getChildren() override;
    void accept(std::shared_ptr<DesignExtractor> extractor) override;
    void accept(std::shared_ptr<SelectiveExtractor> extractor) override;
private:
    std::vector<std::shared_ptr<StmtNode>> statements;
    std::string name;

};

class AssignNode: public StmtNode {
public:
    AssignNode(int lineNo, const std::string& variable, const std::string& expression,  const std::string& proc);
    std::string print() const override {return "assign node";};
    std::string getVar() { return this->variable; };
    std::string getExpr() { return this->expression; };
    int getLine() override { return lineNo; };
    std::string getProc() {
        return this->name;
    }

    std::vector<std::shared_ptr<TNode>> getChildren() override;
    void accept(std::shared_ptr<DesignExtractor> extractor) override;
    void accept(std::shared_ptr<SelectiveExtractor> extractor) override;
private:
    int lineNo;
    std::string variable;
    std::string expression;
    std::string name;
};

class ReadNode: public StmtNode {
public:
    ReadNode(int lineNo, const std::string& var,  const std::string& proc);
    std::string getVar() { return this->variable; };
    int getLine() override { return lineNo; };
    std::string getProc() {
        return this->name;
    }

    std::string print() const override {return "read node";};
    std::vector<std::shared_ptr<TNode>> getChildren() override;
    void accept(std::shared_ptr<DesignExtractor> extractor) override;
    void accept(std::shared_ptr<SelectiveExtractor> extractor) override;
private:
    int lineNo;
    std::string variable;
    std::string name;
};

class CallNode: public StmtNode {
public:
    CallNode(int lineNo, const std::string& var, const std::string& proc);
    std::string getVar() { return this->variable; };
    int getLine() override { return lineNo; };
    std::string getProc() {
        return this->name;
    }

    std::string print() const override {return "read node";};
    std::vector<std::shared_ptr<TNode>> getChildren() override;
    void accept(std::shared_ptr<DesignExtractor> extractor) override;
    void accept(std::shared_ptr<SelectiveExtractor> extractor) override;
private:
    int lineNo;
    std::string proc;
    std::string variable;
    std::string name;
};

class PrintNode: public StmtNode {
public:
    PrintNode(int lineNo, const std::string& var,  const std::string& proc);
    std::string getVar() { return this->variable; };
    int getLine() override { return lineNo; };
    std::string getProc() {
        return this->name;
    }

    std::string print() const override {return "print node";};
    std::vector<std::shared_ptr<TNode>> getChildren() override;
    void accept(std::shared_ptr<DesignExtractor> extractor) override;
    void accept(std::shared_ptr<SelectiveExtractor> extractor) override;
private:
    int lineNo;
    std::string variable;
    std::string name;
};

class IfNode: public StmtNode {
public:
    IfNode(int lineNo, const std::string& condExpr, std::shared_ptr<StmtLstNode> ifLst, std::shared_ptr<StmtLstNode> elseLst, const std::string& proc);
    std::string getCondExpr() { return this->condExpr; };
    std::shared_ptr<StmtLstNode> getIfLst() { return this->ifLst; };
    std::shared_ptr<StmtLstNode> getElseLst() { return this->elseLst; };
    int getLine() override { return lineNo; };
    std::string getProc() {
        return this->name;
    }

    std::string print() const override {return "if node";};
    std::vector<std::shared_ptr<TNode>> getChildren() override;
    void accept(std::shared_ptr<DesignExtractor> extractor) override;
    void accept(std::shared_ptr<SelectiveExtractor> extractor) override;
private:
    int lineNo;
    std::string condExpr;
    std::shared_ptr<StmtLstNode> ifLst;
    std::shared_ptr<StmtLstNode> elseLst;
    std::string name;
};

class WhileNode: public StmtNode {
public:
    WhileNode(int lineNo, const std::string& condExpr, std::shared_ptr<StmtLstNode> stmtLst, const std::string& proc);
    std::string getCondExpr() { return this->condExpr; };
    std::shared_ptr<StmtLstNode> getStmtLst() { return this->stmtLst; };
    int getLine() override { return lineNo; };
    std::string getProc() {
        return this->name;
    }

    std::string print() const override {return "while node";};
    std::vector<std::shared_ptr<TNode>> getChildren() override;
    void accept(std::shared_ptr<DesignExtractor> extractor) override;
    void accept(std::shared_ptr<SelectiveExtractor> extractor) override;
private:
    int lineNo;
    std::string condExpr;
    std::shared_ptr<StmtLstNode> stmtLst;
    std::string name;
};



class ProcedureNode: public TNode {
public:
    ProcedureNode(std::shared_ptr<StmtLstNode> stmtLst, const std::string& proc);
    std::shared_ptr<StmtLstNode> getStmtLst() {
        return this->stmtLst;
    };
    std::string getProc() {
        return this->name;
    };

    std::string print() const override {return "procedure node";};
    std::vector<std::shared_ptr<TNode>> getChildren() override;
    void accept(std::shared_ptr<DesignExtractor> extractor) override;
    void accept(std::shared_ptr<SelectiveExtractor> extractor) override;
private:
    std::shared_ptr<StmtLstNode> stmtLst;
    std::string name;
};




