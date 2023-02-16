#pragma once
#include <string>
#include "TNode.h"

using namespace std;

class DesignExtractor {
public:
    virtual void visit(std::shared_ptr<TNode> n) {};
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
    void visit(std::shared_ptr<TNode> n) override;
};

class UsesExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n) override;
};

class FollowsExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n) override;
};

class FollowsStarExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n) override;
};

class ParentsExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n) override ;
};

class ParentsStarExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n) override;
};


