#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "TNode.h"
#include "Token.h"
#include "Tokenizer.h"
#include "DesignExtractor.h"

using namespace std;
Tokenizer tok;

bool DesignExtractor::isAssignNode(std::shared_ptr<TNode> n) {
    return (dynamic_pointer_cast<AssignNode>(n) != nullptr);
}

bool DesignExtractor::isReadNode(std::shared_ptr<TNode> n) {
    return (dynamic_pointer_cast<ReadNode>(n) != nullptr);
}

bool DesignExtractor::isPrintNode(std::shared_ptr<TNode> n) {
    return (dynamic_pointer_cast<PrintNode>(n) != nullptr);
}

bool DesignExtractor::isIfNode(std::shared_ptr<TNode> n) {
    return (dynamic_pointer_cast<IfNode>(n) != nullptr);
}

bool DesignExtractor::isWhileNode(std::shared_ptr<TNode> n) {
    return (dynamic_pointer_cast<WhileNode>(n) != nullptr);
}

bool DesignExtractor::isStmtLstNode(std::shared_ptr<TNode> n) {
    return (dynamic_pointer_cast<StmtLstNode>(n) != nullptr);
}

void ModifiesExtractor::visit(std::shared_ptr<TNode> n) {
    if (isAssignNode(n)) {
        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
        std::cout << "populating:" << a->getVar() << std::endl;
        std::cout<<"checked assign"<<endl;
    } else if (isReadNode(n)) {
        std::shared_ptr<ReadNode> r = std::dynamic_pointer_cast<ReadNode>(n);
        std::cout << "populating:" << r->getVar() << std::endl;
        //parser->pkbPopulator->addVar(entity);
        std::cout<<"checked read"<<endl;
    } else if (isIfNode(n)) {
    } else if (isWhileNode(n)) {
    }
}

void UsesExtractor::visit(std::shared_ptr<TNode> n) {
    std::cout<<n->print()<<endl;
    if (isAssignNode(n)) {
        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
        std::cout << "expr:" << a->getExpr() << std::endl;
        vector<std::string> rhs = tok.tokenize(a->getExpr());
        for (string entity: rhs)
            if (Token::isValidName((entity))) {
                std::cout << "populating variable:" << entity << std::endl;
                //parser->pkbPopulator->addVar(entity);
            } else if (Token::isNumber(entity)) {
                //parser->pkbPopulator->addConst(std::stoi(entity));
                std::cout << "populating constant:" << entity << std::endl;
            }
        std::cout<<"checked assign"<<endl;
    } else if (isPrintNode(n)) {
        std::shared_ptr<PrintNode> r = std::dynamic_pointer_cast<PrintNode>(n);
        std::cout << "populating:" << r->getVar() << std::endl;
        std::cout<<"checked print"<<endl;
    } else if (isIfNode(n)) {
    } else if (isWhileNode(n)) {
    }
}

void FollowsExtractor::visit(std::shared_ptr<TNode> n) {
    if (isStmtLstNode(n)) {
        std::shared_ptr<StmtLstNode> sl = std::dynamic_pointer_cast<StmtLstNode>(n);
        std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
        vector<int> stmtLines;
        for(auto i: stmts) {
            if(!(isIfNode(i) || isWhileNode(i))) {
                std::cout<<i->getLine()<<endl;
                if ((!stmtLines.empty()) && (i->getLine() == (stmtLines[stmtLines.size() - 1] + 1))) {
                    std::cout << "populating follow pair (" << (stmtLines[stmtLines.size() - 1])<< ',' << i->getLine() << ")" <<endl;
                }
                stmtLines.push_back(i->getLine());
            }
        }
    }
}

void ParentsExtractor::visit(std::shared_ptr<TNode> n) {
    if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
        std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
        vector<int> stmtLines;
        for(auto i: ifStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
                stmtLines.push_back(i->getLine());
            }
        }
        for(auto i: elseStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
                stmtLines.push_back(i->getLine());
            }
        }
        //populate pkb - key,vector or key,value permutations??
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
        vector<int> stmtLines;
        for (auto i: whStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
                stmtLines.push_back(i->getLine());
            }
        }
        //populate pkb - key,vector or key,value permutations??
    }
}



