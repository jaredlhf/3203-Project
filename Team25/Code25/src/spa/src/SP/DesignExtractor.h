#pragma once
#include <string>
#include "TNode.h"

using namespace std;

class DesignExtractor {
public:

    virtual void visit(std::shared_ptr<AssignNode> n) {};
    virtual void visit(std::shared_ptr<ReadNode> n) {};
    virtual void visit(std::shared_ptr<PrintNode> n) {};
    virtual void visit(std::shared_ptr<IfNode> n) {};
    virtual void visit(std::shared_ptr<WhileNode> n) {};
    virtual void visit(std::shared_ptr<StmtLstNode> n) {};
    virtual void visit(std::shared_ptr<ProcedureNode> n) {};


    static bool isAssignNode(std::shared_ptr<TNode> n);
    static bool isPrintNode(std::shared_ptr<TNode> n);
    static bool isReadNode(std::shared_ptr<TNode> n);
    static bool isIfNode(std::shared_ptr<TNode> n);
    static bool isWhileNode(std::shared_ptr<TNode> n);
    static bool isStmtLstNode(std::shared_ptr<TNode> n);
    static void extractVar(vector<std::string> tokens);
    static void extractConst(vector<std::string> tokens);
};

class ModifiesExtractor: public DesignExtractor {
public:

    void visit(std::shared_ptr<AssignNode> n);
    void visit(std::shared_ptr<ReadNode> n);
    void visit(std::shared_ptr<IfNode> n);
    void visit(std::shared_ptr<WhileNode> n);
};

class UsesExtractor: public DesignExtractor {
public:

    void visit(std::shared_ptr<AssignNode> n);
    void visit(std::shared_ptr<PrintNode> n);
    void visit(std::shared_ptr<IfNode> n);
    void visit(std::shared_ptr<WhileNode> n);
};

class FollowsExtractor: public DesignExtractor {
public:

    void visit(std::shared_ptr<StmtLstNode> n);
};

class FollowsStarExtractor: public DesignExtractor {
public:

    void visit(std::shared_ptr<StmtLstNode> n);
};

class ParentsExtractor: public DesignExtractor {
public:

    void visit(std::shared_ptr<IfNode> n);
    void visit(std::shared_ptr<WhileNode> n);
};

class ParentsStarExtractor: public DesignExtractor {
public:

    void visit(std::shared_ptr<IfNode> n);
    void visit(std::shared_ptr<WhileNode> n);
};


