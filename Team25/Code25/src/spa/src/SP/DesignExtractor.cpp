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



void DesignExtractor::extractVar(vector<std::string> tokens) {
    for (string entity: tokens)
        if (Token::isValidName((entity))) {
            std::cout << "populating variable:" << entity << std::endl;
            //parser->pkbPopulator->addVar(entity);
        }
}

void DesignExtractor::extractConst(vector<std::string> tokens) {
    for (string entity: tokens)
         if (Token::isNumber(entity)) {
            //parser->pkbPopulator->addConst(std::stoi(entity));
            std::cout << "populating constant:" << entity << std::endl;
        }
}

//void ModifiesExtractor::visit(std::shared_ptr<TNode> n) {
//    if (isAssignNode(n)) {
//        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
//        std::cout << "populating:" << a->getVar() << std::endl;
//        std::cout<<"checked assign"<<endl;
//    } else if (isReadNode(n)) {
//        std::shared_ptr<ReadNode> r = std::dynamic_pointer_cast<ReadNode>(n);
//        std::cout << "populating:" << r->getVar() << std::endl;
//        //parser->pkbPopulator->addVar(entity);
//        std::cout<<"checked read"<<endl;
//    } else if (isIfNode(n)) {
//        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
//        std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
//        //check if need to get var from cond expr
//        for (auto i : ifStmts) {
//            visit(i);
//        }
//        for (auto i : elseStmts) {
//            visit(i);
//        }
//    } else if (isWhileNode(n)) {
//        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
//        for (auto j: whStmts) {
//            visit(j);
//        }
//    }
//}

void ModifiesExtractor::visit(std::shared_ptr<TNode> n) {
    if (isAssignNode(n)) {
        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
        ModifiesExtractor::visit(a);
    } else if (isReadNode(n)) {
        std::shared_ptr<ReadNode> r = std::dynamic_pointer_cast<ReadNode>(n);
        ModifiesExtractor::visit(r);
    } else if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        ModifiesExtractor::visit(ifs);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        ModifiesExtractor::visit(wh);
    }
}

void ModifiesExtractor::visit(std::shared_ptr<AssignNode> a) {
    std::cout << "populating modifies:" << a->getVar() << std::endl;
    //std::cout<<"checked assign"<<endl;
}

void ModifiesExtractor::visit(std::shared_ptr<ReadNode> r) {
    std::cout << "populating modifies:" << r->getVar() << std::endl;
}

void ModifiesExtractor::visit(std::shared_ptr<IfNode> ifs) {
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    //check if need to get var from cond expr
    for (auto i : ifStmts) {
        //std::cout << "node type in modifies" << i->print() << std::endl;
        visit(i);
    }
    for (auto i : elseStmts) {
        visit(i);
    }
}

void ModifiesExtractor::visit(std::shared_ptr<WhileNode> wh) {
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    for (auto j: whStmts) {
        visit(j);
    }
}

//void UsesExtractor::visit(std::shared_ptr<TNode> n) {
//    Tokenizer t;
//    std::cout<<n->print()<<endl;
//    if (isAssignNode(n)) {
//        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
//        std::cout << "expr:" << a->getExpr() << std::endl;
//        vector<std::string> rhs = tok.tokenize(a->getExpr());
//        extractVar(rhs);
//        extractConst(rhs);
//        std::cout<<"checked assign"<<endl;
//    } else if (isPrintNode(n)) {
//        std::shared_ptr<PrintNode> r = std::dynamic_pointer_cast<PrintNode>(n);
//        std::cout << "populating:" << r->getVar() << std::endl;
//        std::cout<<"checked print"<<endl;
//    } else if (isIfNode(n)) {
//        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
//        std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
//        std::string expr = ifs->getCondExpr();
//        extractVar(t.tokenize(expr));
//        extractConst(t.tokenize(expr));
//        for (auto i : ifStmts) {
//            visit(i);
//        }
//        for (auto i : elseStmts) {
//            visit(i);
//        }
//    } else if (isWhileNode(n)) {
//        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
//        std::string expr = wh->getCondExpr();
//        extractVar(t.tokenize(expr));
//        extractConst(t.tokenize(expr));
//        for (auto j: whStmts) {
//            visit(j);
//        }
//    }
//}

void UsesExtractor::visit(std::shared_ptr<TNode> n) {
    if (isAssignNode(n)) {
        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
        UsesExtractor::visit(a);
    } else if (isPrintNode(n)) {
        std::shared_ptr<PrintNode> r = std::dynamic_pointer_cast<PrintNode>(n);
        UsesExtractor::visit(r);
    } else if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        UsesExtractor::visit(ifs);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        UsesExtractor::visit(wh);
    }
}

void UsesExtractor::visit(std::shared_ptr<AssignNode> a) {
    std::cout << "populating uses expr:" << a->getExpr() << std::endl;
    vector<std::string> rhs = tok.tokenize(a->getExpr());
    extractVar(rhs);
    extractConst(rhs);
    //std::cout<<"checked assign"<<endl;
}

void UsesExtractor::visit(std::shared_ptr<PrintNode> r) {
    std::cout << "populating uses:" << r->getVar() << std::endl;
    //std::cout<<"checked print"<<endl;
}

void UsesExtractor::visit(std::shared_ptr<IfNode> ifs) {
    Tokenizer t;
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    std::string expr = ifs->getCondExpr();
    extractVar(t.tokenize(expr));
    extractConst(t.tokenize(expr));
    for (auto i : ifStmts) {
        visit(i);
    }
    for (auto i : elseStmts) {
        visit(i);
    }
}

void UsesExtractor::visit(std::shared_ptr<WhileNode> wh) {
    Tokenizer t;
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    std::string expr = wh->getCondExpr();
    extractVar(t.tokenize(expr));
    extractConst(t.tokenize(expr));
    for (auto j: whStmts) {
        visit(j);
    }
}

//void FollowsExtractor::visit(std::shared_ptr<TNode> n) {
//    if (isStmtLstNode(n)) {
//        std::shared_ptr<StmtLstNode> sl = std::dynamic_pointer_cast<StmtLstNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
//        vector<int> stmtLines;
//        for(auto i: stmts) {
//            if ((!stmtLines.empty()) && (i->getLine() == (stmtLines[stmtLines.size() - 1] + 1))) {
//                std::cout << "populating follow pair (" << (stmtLines[stmtLines.size() - 1])<< ',' << i->getLine() << ")" <<endl;
//            }
//            stmtLines.push_back(i->getLine());
//        }
//    }
//}

void FollowsExtractor::visit(std::shared_ptr<StmtLstNode> sl) {

    std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
    vector<int> stmtLines;
    for(auto i: stmts) {
        if ((!stmtLines.empty()) && (i->getLine() == (stmtLines[stmtLines.size() - 1] + 1))) {
            std::cout << "populating follow pair (" << (stmtLines[stmtLines.size() - 1])<< ',' << i->getLine() << ")" <<endl;
        }
        stmtLines.push_back(i->getLine());
    }
}

//void FollowsStarExtractor::visit(std::shared_ptr<TNode> n) {
//    if (isStmtLstNode(n)) {
//        std::shared_ptr<StmtLstNode> sl = std::dynamic_pointer_cast<StmtLstNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
//        vector<int> stmtLines;
//        for(auto i: stmts) {
//                stmtLines.push_back(i->getLine());
//        }
//        for(auto j : stmtLines) {
//            std::cout << j << " ";
//        }
//    }
//}

void FollowsStarExtractor::visit(std::shared_ptr<StmtLstNode> sl) {
    std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
    vector<int> stmtLines;
    for(auto i: stmts) {
        stmtLines.push_back(i->getLine());
    }
    std::cout << "populating follows* ";
    for(auto j : stmtLines) {
        std::cout << j << " " ;
    }
    std::cout << std::endl;
}

//void ParentsExtractor::visit(std::shared_ptr<TNode> n) {
//    if (isIfNode(n)) {
//        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
//        std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
//        vector<int> stmtLines;
//        for(auto i: ifStmts) {
//            if (!(isIfNode(i) || isWhileNode(i))) {
//                std::cout << i->getLine() << " parents " << endl;
//                stmtLines.push_back(i->getLine());
//            }
//        }
//        for(auto i: elseStmts) {
//            if (!(isIfNode(i) || isWhileNode(i))) {
//                std::cout << i->getLine() << " parents " << endl;
//                stmtLines.push_back(i->getLine());
//            }
//        }
////        for(auto j: stmtLines) {
////            std::cout << j << " parents " << endl;
////        }
//        //populate pkb - key,vector or key,value permutations??
//    } else if (isWhileNode(n)) {
//        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
//        vector<int> stmtLines;
//        for (auto i: whStmts) {
//            if (!(isIfNode(i) || isWhileNode(i))) {
//                stmtLines.push_back(i->getLine());
//            }
//        }
//        //populate pkb - key,vector or key,value permutations??
//    }
//}
void ParentsExtractor::visit(std::shared_ptr<TNode> n) {
    if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        visit(ifs);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        visit(wh);
    }
}

void ParentsExtractor::visit(std::shared_ptr<IfNode> ifs) {
        std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
        std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
        vector<int> stmtLines;
        for(auto i: ifStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
                std::cout << i->getLine() << " parents " << endl;
                stmtLines.push_back(i->getLine());
            }
        }
        for(auto i: elseStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
                std::cout << i->getLine() << " parents " << endl;
                stmtLines.push_back(i->getLine());
            }
        }
//        for(auto j: stmtLines) {
//            std::cout << j << " parents " << endl;
//        }
        //populate pkb - key,vector or key,value permutations??
}

void ParentsExtractor::visit(std::shared_ptr<WhileNode> wh) {
        std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
        vector<int> stmtLines;
        for (auto i: whStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
                stmtLines.push_back(i->getLine());
            }
        }
        //populate pkb - key,vector or key,value permutations??
}



//void ParentsStarExtractor::visit(std::shared_ptr<TNode> n) {
//    ParentsExtractor p;
//    if (isIfNode(n)) {
//        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
//        std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
//        int ifLineNo = ifs->getLine();
//        vector<int> stmtLines;
//        stmtLines.push_back(ifLineNo);
//        for(auto i: ifStmts) {
//            if (!(isIfNode(i) || isWhileNode(i))) {
////                std::cout<< i->getLine() <<" parents*if " <<endl;
//                stmtLines.push_back(i->getLine());
//            } else {
//               visit(i);
//            }
//        }
//        for(auto i: elseStmts) {
//            if (!(isIfNode(i) || isWhileNode(i))) {
////                std::cout<< i->getLine() <<" parents*else " <<endl;
//                stmtLines.push_back(i->getLine());
//            } else {
//                visit(i);
//            }
//        }
//        for(auto j: stmtLines) {
//            std::cout << j <<" parents*" <<endl;
//        }
//        //populate pkb - key,vector or key,value permutations??
//    } else if (isWhileNode(n)) {
//        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
//        std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
//        vector<int> stmtLines;
//        for (auto i: whStmts) {
//            if (!(isIfNode(i) || isWhileNode(i))) {
//                stmtLines.push_back(i->getLine());
//            } else {
//                p.visit(i);
//            }
//        }
//        //populate pkb - key,vector or key,value permutations??
//    }
//}
void ParentsStarExtractor::visit(std::shared_ptr<TNode> n) {
    if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        visit(ifs);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        visit(wh);
    }
}

void ParentsStarExtractor::visit(std::shared_ptr<IfNode> ifs) {
    ParentsExtractor p;
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    int ifLineNo = ifs->getLine();
    vector<int> stmtLines;
    stmtLines.push_back(ifLineNo);
    for(auto i: ifStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
//          std::cout<< i->getLine() <<" parents*if " <<endl;
            stmtLines.push_back(i->getLine());
        } else {
            visit(i);
        }
    }
    for(auto i: elseStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
//          std::cout<< i->getLine() <<" parents*else " <<endl;
            stmtLines.push_back(i->getLine());
        } else {
            visit(i);
        }
    }
    for(auto j: stmtLines) {
        std::cout << j <<" parents*" <<endl;
    }
    //populate pkb - key,vector or key,value permutations??
}

void ParentsStarExtractor::visit(std::shared_ptr<WhileNode> wh) {
    ParentsExtractor p;
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    vector<int> stmtLines;
    for (auto i: whStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
            stmtLines.push_back(i->getLine());
        } else {
            p.visit(i);
        }
    }
    //populate pkb - key,vector or key,value permutations??
}



