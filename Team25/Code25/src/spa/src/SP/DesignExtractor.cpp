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

DesignExtractor::DesignExtractor(std::shared_ptr<PkbPopulator> populator) {
    this->pkbPopulator = populator;
}

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
//            std::cout << "populating variable:" << entity << std::endl;
            pkbPopulator->addVar(entity);
        }
}

void DesignExtractor::extractConst(vector<std::string> tokens) {
    for (string entity: tokens)
         if (Token::isNumber(entity)) {
              pkbPopulator->addConst(std::stoi(entity));
//            std::cout << "populating constant:" << entity << std::endl;

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

void ModifiesExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isAssignNode(n)) {
        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
        ModifiesExtractor::visit(a, lineNo);
    } else if (isReadNode(n)) {
        std::shared_ptr<ReadNode> r = std::dynamic_pointer_cast<ReadNode>(n);
        ModifiesExtractor::visit(r, lineNo);
    } else if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        ModifiesExtractor::visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        ModifiesExtractor::visit(wh, lineNo);
    }
}

void ModifiesExtractor::visit(std::shared_ptr<AssignNode> a, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = a->getLine();
    }
    std::cout << "populating modifies:" << "(" << lineNo << "," << a->getVar() <<")"  << std::endl;
    //std::cout<<"checked assign"<<endl;
    pkbPopulator->addModifies(lineNo, a->getVar());
    pkbPopulator->addVar(a->getVar());

    pkbPopulator->addAssignLhs(a->getVar(), lineNo);
    pkbPopulator->addAssignRhs(lineNo, a->getExpr());
}

void ModifiesExtractor::visit(std::shared_ptr<ReadNode> r, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = r->getLine();
    }
    pkbPopulator->addModifies(lineNo, r->getVar());
    pkbPopulator->addVar(r->getVar());
    std::cout << "populating modifies:" << "(" << lineNo << "," << r->getVar() <<")" << std::endl;
}

void ModifiesExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    //check if need to get var from cond expr
    for (auto i : ifStmts) {
        //std::cout << "node type in modifies" << i->print() << std::endl;
        visit(i, lineNo);
    }
    for (auto i : elseStmts) {
        visit(i, lineNo);
    }
}

void ModifiesExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = wh->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    for (auto j: whStmts) {
        visit(j, lineNo);
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

void UsesExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isAssignNode(n)) {
        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
        UsesExtractor::visit(a, lineNo);
    } else if (isPrintNode(n)) {
        std::shared_ptr<PrintNode> r = std::dynamic_pointer_cast<PrintNode>(n);
        UsesExtractor::visit(r, lineNo);
    } else if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        UsesExtractor::visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        UsesExtractor::visit(wh, lineNo);
    }
}

void UsesExtractor::visit(std::shared_ptr<AssignNode> a, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = a->getLine();
    }
    std::cout << "populating uses expr:" << "(" << lineNo << "," << a->getExpr() <<")" << std::endl;
    vector<std::string> rhs = tok.tokenize(a->getExpr());
    extractVar(rhs);
    extractConst(rhs);

    for (auto const token: rhs) {
        if (Token::isValidName(token)) {
            pkbPopulator->addUses(lineNo, token);
        }
    }

    //std::cout<<"checked assign"<<endl;
}

void UsesExtractor::visit(std::shared_ptr<PrintNode> r, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = r->getLine();
    }
    pkbPopulator->addUses(lineNo, r->getVar());
    pkbPopulator->addVar(r->getVar());
    std::cout << "populating uses:" << "(" << lineNo << "," << r ->getVar() <<")" << std::endl;
    //std::cout<<"checked print"<<endl;
}

void UsesExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    Tokenizer t;
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    std::string expr = ifs->getCondExpr();
    std::vector<std::string> tokens = t.tokenize(expr);
    extractVar(tokens);
    extractConst(tokens);

    for (const auto token : tokens) {
        pkbPopulator->addUses(lineNo, token);
    }

    for (auto i : ifStmts) {
        visit(i, lineNo);
    }
    for (auto i : elseStmts) {
        visit(i, lineNo);
    }
}

void UsesExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = wh->getLine();
    }
    Tokenizer t;
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    std::string expr = wh->getCondExpr();
    std::vector<std::string> tokens = t.tokenize(expr);
    extractVar(tokens);
    extractConst(tokens);

    for (const auto token : tokens) {
        pkbPopulator->addUses(lineNo, token);
    }
    for (auto j: whStmts) {
        visit(j, lineNo);
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

void FollowsExtractor::visit(std::shared_ptr<StmtLstNode> sl, int lineNo) {

    std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
    vector<int> stmtLines;
    for(auto i: stmts) {
        if ((!stmtLines.empty()) && (i->getLine() == (stmtLines[stmtLines.size() - 1] + 1))) {
            int left = (stmtLines[stmtLines.size() - 1]);
            int right = i->getLine();
            std::cout << "populating follow pair (" << (stmtLines[stmtLines.size() - 1])<< ',' << i->getLine() << ")" <<endl;
            pkbPopulator->addFollows(left, right);
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

void FollowsStarExtractor::visit(std::shared_ptr<StmtLstNode> sl, int lineNo) {
    std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
    vector<int> stmtLines;
    for(auto i: stmts) {
        stmtLines.push_back(i->getLine());
    }

    while (stmtLines.size() != 1) {
        std::unordered_set<int> follows = std::unordered_set<int>(stmtLines.begin() + 1, stmtLines.end());
        int key = stmtLines[0];
        pkbPopulator->addFollowsStar(key, follows);
        std::cout << "populating follows* " << "(" << stmtLines[0] << "," << "(";
        for(auto k: follows) {
            std::cout << k << " ";
        }
        std::cout<<"))"<<endl;
        stmtLines.erase(stmtLines.begin());
    }

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
void ParentsExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        visit(wh, lineNo);
    }
}

void ParentsExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
        int line = ifs->getLine();
        std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
        std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
        vector<int> stmtLines;
        for(auto i: ifStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
//                std::cout << i->getLine() << " parents " << endl;
                stmtLines.push_back(i->getLine());
            }
        }
        for(auto i: elseStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
//                std::cout << i->getLine() << " parents " << endl;
                stmtLines.push_back(i->getLine());
            }
        }
        for(auto j: stmtLines) {
            std::cout << "populating parents: " << "(" << line << "," << j << ")"<< endl ;
            pkbPopulator->addParent(line, j);
        }
        std::cout<<endl;
        //populate pkb - key,vector or key,value permutations??
}

void ParentsExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
        int line = wh->getLine();
        std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
        vector<int> stmtLines;
        for (auto i: whStmts) {
            if (!(isIfNode(i) || isWhileNode(i))) {
                stmtLines.push_back(i->getLine());
            }
        }
        for(auto j: stmtLines) {
            std::cout << "populating parents: " << "(" << line << "," << j << ")"<< endl ;
            pkbPopulator->addParent(line, j);
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
void ParentsStarExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        visit(wh, lineNo);
    }
}

void ParentsStarExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
//    int line = ifs->getLine();
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
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
            visit(i, lineNo);
        }
    }
    for(auto i: elseStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
//          std::cout<< i->getLine() <<" parents*else " <<endl;
            stmtLines.push_back(i->getLine());
        } else {
            visit(i, lineNo);
        }
    }
    for(auto j: stmtLines) {
        std::cout<<"populating parents*:" <<  "(" << lineNo << "," << j << ")" <<endl;
        pkbPopulator->addParent(lineNo, j);
    }
    //populate pkb - key,vector or key,value permutations??
}

void ParentsStarExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
//    int line = wh->getLine();
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = wh->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    int whLineNo = wh->getLine();
    vector<int> stmtLines;
    stmtLines.push_back(whLineNo);
    for (auto i: whStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
            stmtLines.push_back(i->getLine());
        } else {
            visit(i, lineNo);
        }
    }
    for(auto j: stmtLines) {
        std::cout<<"populating parents*:" << "("  << lineNo << "," << j << ")" <<endl;
        pkbPopulator->addParent(lineNo, j);
    }
    //populate pkb - key,vector or key,value permutations??
}



