#pragma once
#include <string>
#include "TNode.h"

using namespace std;

class DesignExtractor {
public:
    virtual void visit(std::shared_ptr<TNode> n) {};
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

//class FollowsStarExtractor: public DesignExtractor {
//public:
//    void visit(std::shared_ptr<TNode> n) override { std::cout << "stmt" << endl; };
//};
//
class ParentsExtractor: public DesignExtractor {
public:
    void visit(std::shared_ptr<TNode> n) override ;
};

//class ParentsStarExtractor: public DesignExtractor {
//public:
//    void visit(std::shared_ptr<TNode> n) override { std::cout << "stmt" << endl; };
//};
//
//
