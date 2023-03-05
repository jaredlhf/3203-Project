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
    } else if (isCallNode(n)) {
        std::shared_ptr<CallNode> c = std::dynamic_pointer_cast<CallNode>(n);
        ModifiesExtractor::visit(c, lineNo);
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
        std::cout << "populate procedure modifies: " << a->getProc() + " " + a->getVar() << " " << endl;
    } else {
        pkbPopulator->addModifies(lineNo, a->getVar());
        pkbPopulator->addVar(a->getVar());
    }

    pkbPopulator->addAssignLhs(a->getVar(), lineNo);
    pkbPopulator->addAssignRhs(lineNo, a->getExpr());
}

void ModifiesExtractor::visit(std::shared_ptr<ReadNode> r, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = r->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }

    if (lineNo == SPConstants::PROCEDURE) {
        std::cout << "populate procedure modifies: " << r->getProc() + " " + r->getVar() << " " << endl;
    } else {
        pkbPopulator->addModifies(lineNo, r->getVar());
        pkbPopulator->addVar(r->getVar());
    }
}

void ModifiesExtractor::visit(std::shared_ptr<CallNode> c, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = c->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }

    if (lineNo == SPConstants::PROCEDURE) {
        std::cout << "populate procedure modifies: " << c->getProc() + " " + c->getVar() << " " << endl;
    } else {
        //pkbPopulator->addCalls(lineNo, c->getVar());
        //pkbPopulator->addVar(c->getVar());
        std::cout << "Populating modifies for calls: " << c->getVar() << std::endl;
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
    extractVar(rhs);
    extractConst(rhs);

    for (auto const token: rhs) {
        if (Token::isValidName(token)) {
            if (lineNo == SPConstants::PROCEDURE) {
                std::cout << "populate procedure use: " << a->getProc() + " " + token << " " << endl;
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
        std::cout << "populate procedure use: " << r->getProc() + " " + r->getVar() << " " << endl;
    } else {
        pkbPopulator->addUses(lineNo, r->getVar());
        pkbPopulator->addVar(r->getVar());
    }
}

void UsesExtractor::visit(std::shared_ptr<CallNode> c, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = c->getLine();
    } else if (lineNo == SPConstants::PROCEDURE) {
        lineNo = SPConstants::PROCEDURE;
    }
    //pkbPopulator->addUses(lineNo, c->getVar());
    //pkbPopulator->addVar(c->getVar());
    if (lineNo == SPConstants::PROCEDURE) {
        std::cout << "Populating procedure use: " << c->getProc() + " " + c->getVar() << std::endl;
    } else {
        std::cout << "Populating modifies for calls: " << c->getVar() << std::endl;
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
    extractVar(tokens);
    extractConst(tokens);

    for (const auto token: tokens) {
        if (Token::isValidName(token)) {
            if (lineNo == SPConstants::PROCEDURE) {
                std::cout << "populate procedure use: " << ifs->getProc() + " " + token << " " << endl;
            } else {
                pkbPopulator->addUses(lineNo, token);
            }
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
    extractVar(tokens);
    extractConst(tokens);

    for (const auto token: tokens) {
        if (lineNo == SPConstants::PROCEDURE) {
            std::cout << "populate procedure use: " << wh->getProc() + " " + token << " " << endl;
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
    std::cout << "Populating call: " << c->getProc() + " " + c->getVar() << std::endl;
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
        std::shared_ptr<AssignNode> v = std::dynamic_pointer_cast<AssignNode>(n);
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
    std::cout<<  "callingProc: " <<callingProc <<endl;
    std::cout<< "calledProc: "<< calledProc<< endl;
    if(this->callsStorage.find(callingProc) != this->callsStorage.end()) {
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
            std::cout<<"Added to callsStar Storage1: " << i << " " <<  calledProc << endl;
            pkbPopulator->addCallsStar(i,calledProc);
        }
    } else {
        std::vector<std::string> calledValue =  this->callsStorage.at(calledProc);
        calledValue.push_back(callingProc);
        this->callsStorage.emplace(calledProc, calledValue);
        if (this->callsStorage.find(callingProc) == this->callsStorage.end()) {
            std::cout << "Added to callsStar Storage2: " << callingProc << " " << calledProc << endl;
            pkbPopulator->addCallsStar(callingProc,calledProc);
        }else {
            for (auto i: this->callsStorage.at(callingProc)) {
                std::cout << "Added to callsStar Storage3: " << i << " " << calledProc << endl;
                pkbPopulator->addCallsStar(i,calledProc);
            }
        }
    }
    for(auto kv : this->getCallsStorage()) {
        keys.push_back(kv.first);
        std::cout<<"Keys: " << kv.first<<endl;
        for (auto i : kv.second) {
            std::cout<<"Values: " << i <<endl;
        }
    }
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


void StatementExtractor::visit(std::shared_ptr<AssignNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::ASSIGN_TYPE, n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<ReadNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::READ_TYPE, n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<PrintNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::PRINT_TYPE, n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<IfNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::IF_TYPE, n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<WhileNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::WHILE_TYPE, n->getLine());
}

void StatementExtractor::visit(std::shared_ptr<CallNode> n, int lineNo) {
    pkbPopulator->addStmt(SPConstants::CALL_TYPE, n->getLine());
}
