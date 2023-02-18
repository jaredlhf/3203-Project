#pragma once
#include <string>
#include "TNode.h"
#include "SPConstants.h"

using namespace std;

class DesignExtractor {
public:
    virtual void visit(std::shared_ptr<AssignNode> n, int lineNo) {};
    virtual void visit(std::shared_ptr<ReadNode> n, int lineNo) {};
    virtual void visit(std::shared_ptr<PrintNode> n, int lineNo) {};
    virtual void visit(std::shared_ptr<IfNode> n, int lineNo) {};
    virtual void visit(std::shared_ptr<WhileNode> n, int lineNo) {};
    virtual void visit(std::shared_ptr<StmtLstNode> n, int lineNo) {};
    virtual void visit(std::shared_ptr<ProcedureNode> n, int lineNo) {};


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
    void visit(std::shared_ptr<TNode> n, int lineNo);
    void visit(std::shared_ptr<AssignNode> n, int lineNo);
    void visit(std::shared_ptr<ReadNode> n, int lineNo);
    void visit(std::shared_ptr<IfNode> n, int lineNo);
    void visit(std::shared_ptr<WhileNode> n, int lineNo);
};

class UsesExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n, int lineNo);
    void visit(std::shared_ptr<AssignNode> n, int lineNo);
    void visit(std::shared_ptr<PrintNode> n, int lineNo);
    void visit(std::shared_ptr<IfNode> n, int lineNo);
    void visit(std::shared_ptr<WhileNode> n, int lineNo);
};

class FollowsExtractor: public DesignExtractor {
public:

    void visit(std::shared_ptr<StmtLstNode> n, int lineNo);
};

class FollowsStarExtractor: public DesignExtractor {
public:

    void visit(std::shared_ptr<StmtLstNode> n, int lineNo);
};

class ParentsExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n, int lineNo);
    void visit(std::shared_ptr<IfNode> n, int lineNo);
    void visit(std::shared_ptr<WhileNode> n, int lineNo);
};

class ParentsStarExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n, int lineNo);
    void visit(std::shared_ptr<IfNode> n, int lineNo);
    void visit(std::shared_ptr<WhileNode> n, int lineNo);
};


