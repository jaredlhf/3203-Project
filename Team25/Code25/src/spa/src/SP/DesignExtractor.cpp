#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
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

bool DesignExtractor::isCallNode(std::shared_ptr<TNode> n) {
    return (dynamic_pointer_cast<CallNode>(n) != nullptr);
}

bool DesignExtractor::isProcedureNode(std::shared_ptr<TNode> n) {
    return (dynamic_pointer_cast<ProcedureNode>(n) != nullptr);
}


void DesignExtractor::extractVar(vector<std::string> tokens) {
    for (string entity: tokens)
        if (Token::isValidName((entity))) {
            pkbPopulator->addVar(entity);
        }
}

void DesignExtractor::extractConst(vector<std::string> tokens) {
    for (string entity: tokens)
        if (Token::isNumber(entity)) {
            pkbPopulator->addConst(std::stoi(entity));
        }
}


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
    } else if (isProcedureNode(n)) {
        std::shared_ptr<ProcedureNode> p = std::dynamic_pointer_cast<ProcedureNode>(n);
        ModifiesExtractor::visit(p, SPConstants::PROCEDURE);
    }
}

void ModifiesExtractor::visit(std::shared_ptr<AssignNode> a, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = a->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }

    if (lineNo == SPConstants::PROCEDURE) {
        pkbPopulator->addModifiesProc(a -> getProc(), a ->getVar());
    } else {
        pkbPopulator->addModifies(lineNo, a->getVar());
    }
}

void ModifiesExtractor::visit(std::shared_ptr<ReadNode> r, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = r->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }

    if (lineNo == SPConstants::PROCEDURE) {
        pkbPopulator->addModifiesProc(r -> getProc(), r ->getVar());
    } else {
        pkbPopulator->addModifies(lineNo, r->getVar());
    }
}

void ModifiesExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    for (auto i: ifStmts) {
        visit(i, lineNo);
    }
    for (auto i: elseStmts) {
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

void ModifiesExtractor::visit(std::shared_ptr<ProcedureNode> p, int lineNo) {
    std::vector<std::shared_ptr<StmtNode>> pStmts = p->getStmtLst()->getStatements();
    for (auto j: pStmts) {
        visit(j, SPConstants::PROCEDURE);
    }
}


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
    } else if (isProcedureNode(n)) {
        std::shared_ptr<ProcedureNode> p = std::dynamic_pointer_cast<ProcedureNode>(n);
        UsesExtractor::visit(p, SPConstants::PROCEDURE);
    }
}

void UsesExtractor::visit(std::shared_ptr<AssignNode> a, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = a->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }
    vector<std::string> rhs = tok.tokenize(a->getExpr());

    for (auto const token: rhs) {
        if (Token::isValidName(token)) {
            if (lineNo == SPConstants::PROCEDURE) {
                pkbPopulator->addUsesProc(a->getProc(), token);
            } else {
                pkbPopulator->addUses(lineNo, token);
            }
        }
    }
}

void UsesExtractor::visit(std::shared_ptr<PrintNode> r, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = r->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }
    if (lineNo == SPConstants::PROCEDURE) {
        pkbPopulator->addUsesProc(r->getProc(), r->getVar());
    } else {
        pkbPopulator->addUses(lineNo, r->getVar());
    }
}

void UsesExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }

    Tokenizer t;
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    std::string expr = ifs->getCondExpr();
    std::vector<std::string> tokens = t.tokenize(expr);
    std::vector<std::string> validTokens;
    for(const auto token:tokens) {
        if (Token::isValidName(token)) {
            validTokens.push_back(token);
        }
    }
    for (const auto token: validTokens) {
          if (lineNo == SPConstants::PROCEDURE) {
              pkbPopulator->addUsesProc(ifs->getProc(), token);
          } else {
              pkbPopulator->addUses(lineNo, token);
          }
    }

    for (auto i: ifStmts) {
        visit(i, lineNo);
    }
    for (auto i: elseStmts) {
        visit(i, lineNo);
    }
}

void UsesExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = wh->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }
    Tokenizer t;
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    std::string expr = wh->getCondExpr();
    std::vector<std::string> tokens = t.tokenize(expr);
    std::vector<std::string> validTokens;
    for(const auto token:tokens) {
        if (Token::isValidName(token)) {
              validTokens.push_back(token);
        }
    }
    for (const auto token: validTokens) {
        if (lineNo == SPConstants::PROCEDURE) {
              pkbPopulator->addUsesProc(wh->getProc(), token);
        } else {
              pkbPopulator->addUses(lineNo, token);
        }
    }

    for (auto j: whStmts) {
        visit(j, lineNo);
    }
}

void UsesExtractor::visit(std::shared_ptr<ProcedureNode> p, int lineNo) {
    std::vector<std::shared_ptr<StmtNode>> pStmts = p->getStmtLst()->getStatements();
    for (auto j: pStmts) {
        visit(j, SPConstants::PROCEDURE);
    }
}

void FollowsExtractor::visit(std::shared_ptr<StmtLstNode> sl, int lineNo) {

    std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
    vector<int> stmtLines;
    for (auto i: stmts) {
        if (!stmtLines.empty()) {
            int left = (stmtLines[stmtLines.size() - 1]);
            int right = i->getLine();
            pkbPopulator->addFollows(left, right);
        }
        stmtLines.push_back(i->getLine());
    }
}

void FollowsStarExtractor::visit(std::shared_ptr<StmtLstNode> sl, int lineNo) {
    std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
    vector<int> stmtLines;
    for (auto i: stmts) {
        stmtLines.push_back(i->getLine());
    }

    while (stmtLines.size() != 1) {
        std::unordered_set<int> follows = std::unordered_set<int>(stmtLines.begin() + 1, stmtLines.end());
        int key = stmtLines[0];
        pkbPopulator->addFollowsStar(key, follows);

        stmtLines.erase(stmtLines.begin());
    }

}

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
    for (auto i: ifStmts) {
        stmtLines.push_back(i->getLine());
    }
    for (auto i: elseStmts) {
        stmtLines.push_back(i->getLine());
    }
    for (auto j: stmtLines) {
        pkbPopulator->addParent(line, j);
    }
}

void ParentsExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    int line = wh->getLine();
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    vector<int> stmtLines;
    for (auto i: whStmts) {
        stmtLines.push_back(i->getLine());
    }
    for (auto j: stmtLines) {
        pkbPopulator->addParent(line, j);
    }
}

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
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    int ifLineNo = ifs->getLine();
    vector<int> stmtLines;
    stmtLines.push_back(ifLineNo);
    for (auto i: ifStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
            stmtLines.push_back(i->getLine());
        } else {
            visit(i, lineNo);
        }
    }
    for (auto i: elseStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
            stmtLines.push_back(i->getLine());
        } else {
            visit(i, lineNo);
        }
    }
    for (auto j: stmtLines) {
        if (lineNo != j) {
            pkbPopulator->addParentStar(lineNo, j);
        }
    }
}

void ParentsStarExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
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
    for (auto j: stmtLines) {
        if (lineNo != j) {
            pkbPopulator->addParentStar(lineNo, j);
        }
    }
}

void CallsExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isCallNode(n)) {
        std::shared_ptr<AssignNode> v = std::dynamic_pointer_cast<AssignNode>(n);
        CallsExtractor::visit(v, lineNo);
    } else if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        CallsExtractor::visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        CallsExtractor::visit(wh, lineNo);
    }
}

void CallsExtractor::visit(std::shared_ptr<CallNode> c, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = c->getLine();
    }
    pkbPopulator->addCalls(c->getProc(),c->getVar());
}

void CallsExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    for (auto i: ifStmts) {
        visit(i, lineNo);
    }
    for (auto i: elseStmts) {
        visit(i, lineNo);
    }
}

void CallsExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = wh->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    for (auto j: whStmts) {
        visit(j, lineNo);
    }
}

void CallsStarExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isCallNode(n)) {
        std::shared_ptr<CallNode> v = std::dynamic_pointer_cast<CallNode>(n);
        CallsStarExtractor::visit(v, lineNo);
    } else if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        CallsStarExtractor::visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        CallsStarExtractor::visit(wh, lineNo);
    }
}

void CallsStarExtractor::visit(std::shared_ptr<CallNode> c, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = c->getLine();
    }
    std::vector<std::string> keys;
    std::string callingProc = c->getProc();
    std::string calledProc = c->getVar();
    if (this->callingStorage.find(callingProc) == this->callingStorage.end()) {
        std::vector<std::string> procs;
        procs.push_back(calledProc);
        this->callingStorage.emplace(callingProc,procs);
    } else {
        std::vector<std::string> procs = this->callingStorage.at(callingProc);
        procs.push_back(calledProc);
        this->callingStorage.emplace(callingProc,procs);
    }
    // cyclic call ( A calls A)
    if (callingProc == calledProc) {
        throw std::invalid_argument("Cyclic Call in SPA Program");
    }
    // cyclic call ( A calls B, B calls A)
    if (this->callsStorage.find(callingProc) != this->callsStorage.end()) {
        // check for cyclic calls
        std::vector<std::string> callingValue =  this->callsStorage.at(callingProc);
        if (std::count(callingValue.begin(), callingValue.end(), calledProc)) {
            throw std::invalid_argument("Cyclic Call in SPA Program");
        }
    }

    if (this->callsStorage.find(calledProc) == this->callsStorage.end()) {
        std::vector<std::string> procs;
        if (this->callsStorage.find(callingProc) != this->callsStorage.end()) {
            procs = this->callsStorage.at(callingProc);
        }
        procs.push_back(callingProc);
        this->callsStorage.emplace(calledProc,procs);
        for (auto i: procs) {
            pkbPopulator->addCallsStar(i,calledProc);
        }
    } else {
        std::vector<std::string> calledValue =  this->callsStorage.at(calledProc);
        calledValue.push_back(callingProc);
        this->callsStorage.emplace(calledProc, calledValue);
        if (this->callsStorage.find(callingProc) == this->callsStorage.end()) {
            pkbPopulator->addCallsStar(callingProc,calledProc);
        }else {
            for (auto i: this->callsStorage.at(callingProc)) {
                pkbPopulator->addCallsStar(i,calledProc);
            }
            pkbPopulator->addCallsStar(callingProc,calledProc);
        }
        if(this->callingStorage.find(callingProc) != this->callingStorage.end()) {
            if (this->callingStorage.find(calledProc) != this->callingStorage.end()) {
                for (auto i : this->callingStorage.at(calledProc)) {
                  pkbPopulator->addCallsStar(callingProc, i);
                  std::vector<std::string> procs = this->callsStorage.at(i);
                  procs.push_back(callingProc);
                  callsStorage.emplace(i, procs);
                }
            }
        }
    }
//    for (auto const &pair: callsStorage) {
//        std::cout << "{" << pair.first << ": " ;
//        for(auto i : pair.second) {
//            std::cout<<i<<endl;
//        }
//    }
//    std::cout<<"END"<<endl;
}

void CallsStarExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    for (auto i: ifStmts) {
        visit(i, lineNo);
    }
    for (auto i: elseStmts) {
        visit(i, lineNo);
    }
}

void CallsStarExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = wh->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    for (auto j: whStmts) {
        visit(j, lineNo);
    }
}



void PatternExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isAssignNode(n)) {
        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
        PatternExtractor::visit(a, lineNo);
    } else if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        PatternExtractor::visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        PatternExtractor::visit(wh, lineNo);
    }
}

void PatternExtractor::visit(std::shared_ptr<AssignNode> a, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = a->getLine();
    }
    pkbPopulator->addAssignLhs(a->getVar(), lineNo);
    pkbPopulator->addAssignRhs(lineNo, a->getExpr());
}

void PatternExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    vector<std::string> condExpr = tok.tokenize(ifs->getCondExpr());
    for (std::string i : condExpr) {
        if (Token::isValidName((i))) {
            pkbPopulator->addIfStatement(lineNo,i);
            pkbPopulator->addIfStatementVar(i,lineNo);
        }
    }
}

void PatternExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = wh->getLine();
    }
    vector<std::string> condExpr = tok.tokenize(wh->getCondExpr());
    for (std::string i : condExpr) {
        if (Token::isValidName((i))) {
            pkbPopulator->addWhileStatement(lineNo,i);
            pkbPopulator->addWhileStatementVar(i,lineNo);
        }
    }
}


void AttributeExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isCallNode(n)) {
        std::shared_ptr<CallNode> v = std::dynamic_pointer_cast<CallNode>(n);
        AttributeExtractor::visit(v, lineNo);
    } else if (isReadNode(n)) {
        std::shared_ptr<ReadNode> r = std::dynamic_pointer_cast<ReadNode>(n);
        AttributeExtractor::visit(r, lineNo);
    } else if (isPrintNode(n)) {
        std::shared_ptr<PrintNode> p = std::dynamic_pointer_cast<PrintNode>(n);
        AttributeExtractor::visit(p, lineNo);
    } else if (isAssignNode(n)) {
        std::shared_ptr<AssignNode> a = std::dynamic_pointer_cast<AssignNode>(n);
        AttributeExtractor::visit(a, lineNo);
    } else if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        AttributeExtractor::visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        AttributeExtractor::visit(wh, lineNo);
    }
}

void AttributeExtractor::visit(std::shared_ptr<CallNode> c, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = c->getLine();
    }
    pkbPopulator->addCallAttr(c->getVar(), lineNo);
}

void AttributeExtractor::visit(std::shared_ptr<PrintNode> p, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = p->getLine();
    }
    pkbPopulator->addVar(p->getVar());
    pkbPopulator->addPrintAttr(p->getVar(), lineNo);
}

void AttributeExtractor::visit(std::shared_ptr<ReadNode> r, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = r->getLine();
    }
    pkbPopulator->addVar(r->getVar());
    pkbPopulator->addReadAttr(r->getVar(), lineNo);
}

void AttributeExtractor::visit(std::shared_ptr<AssignNode> a, int lineNo) {
    pkbPopulator->addVar(a->getVar());
    vector<std::string> rhs = tok.tokenize(a->getExpr());
    extractVar(rhs);
    extractConst(rhs);
}

void AttributeExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    vector<std::string> expr = tok.tokenize(wh->getCondExpr());
    extractVar(expr);
    extractConst(expr);
}

void AttributeExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    vector<std::string> expr = tok.tokenize(ifs->getCondExpr());
    extractVar(expr);
    extractConst(expr);
}

void ProcedureCallsExtractor::visit(std::shared_ptr<TNode> n, int lineNo) {
    if (isIfNode(n)) {
        std::shared_ptr<IfNode> ifs = std::dynamic_pointer_cast<IfNode>(n);
        visit(ifs, lineNo);
    } else if (isWhileNode(n)) {
        std::shared_ptr<WhileNode> wh = std::dynamic_pointer_cast<WhileNode>(n);
        visit(wh, lineNo);
    } else if (isCallNode(n)) {
        std::shared_ptr<CallNode> c = std::dynamic_pointer_cast<CallNode>(n);
        visit(c, lineNo);
    }
}
void ProcedureCallsExtractor::visit(std::shared_ptr<CallNode> c,int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = c->getLine();
    }
//    std::cout<<"calls contain: " << lineNo << " " << c->getVar() <<endl;
    pkbPopulator->addContainCalls(lineNo,c->getVar());
}

void ProcedureCallsExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    int ifLineNo = ifs->getLine();

    for (auto i: ifStmts) {
        visit(i, lineNo);
    }
    for (auto i: elseStmts) {
        visit(i, lineNo);
    }
}

void ProcedureCallsExtractor::visit(std::shared_ptr<WhileNode> wh, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = wh->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> whStmts = wh->getStmtLst()->getStatements();
    int whLineNo = wh->getLine();

    for (auto i: whStmts) {
        visit(i, lineNo);
    }
}

void StatementExtractor::visit(std::shared_ptr<AssignNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::ASSIGN_TYPE, n->getLine());
    pkbPopulator->addProc(n->getProc(),n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<ReadNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::READ_TYPE, n->getLine());
    pkbPopulator->addProc(n->getProc(),n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<PrintNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::PRINT_TYPE, n->getLine());
    pkbPopulator->addProc(n->getProc(),n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<IfNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::IF_TYPE, n->getLine());
    pkbPopulator->addProc(n->getProc(),n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<WhileNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::WHILE_TYPE, n->getLine());
    pkbPopulator->addProc(n->getProc(),n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<CallNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::CALL_TYPE, n->getLine());
    pkbPopulator->addProc(n->getProc(),n->getLine());
}
