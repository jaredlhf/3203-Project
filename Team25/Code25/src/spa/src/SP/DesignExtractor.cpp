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
        ModifiesExtractor::visit(p);
    }
}

void ModifiesExtractor::visit(std::shared_ptr<AssignNode> a, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = a->getLine();
    }

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
}

void ModifiesExtractor::visit(std::shared_ptr<CallNode> c, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = c->getLine();
    }
    //pkbPopulator->addCalls(lineNo, c->getVar());
    //pkbPopulator->addVar(c->getVar());
    std::cout<<"Populating calls: " << c->getVar() <<std::endl;
}


void ModifiesExtractor::visit(std::shared_ptr<IfNode> ifs, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = ifs->getLine();
    }
    std::vector<std::shared_ptr<StmtNode>> ifStmts = ifs->getIfLst()->getStatements();
    std::vector<std::shared_ptr<StmtNode>> elseStmts = ifs->getElseLst()->getStatements();
    for (auto i : ifStmts) {
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

void ModifiesExtractor::visit(std::shared_ptr<ProcedureNode> p) {
    std::vector<std::shared_ptr<StmtNode>> pStmts = p->getStmtLst()->getStatements();
    for (auto j: pStmts) {
//        TODO: add vist and populate (proc,v)
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
        UsesExtractor::visit(p, lineNo);
    }
}

void UsesExtractor::visit(std::shared_ptr<AssignNode> a, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = a->getLine();
    }

    vector<std::string> rhs = tok.tokenize(a->getExpr());
    extractVar(rhs);
    extractConst(rhs);

    for (auto const token: rhs) {
        if (Token::isValidName(token)) {
            pkbPopulator->addUses(lineNo, token);
        }
    }
}

void UsesExtractor::visit(std::shared_ptr<PrintNode> r, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = r->getLine();
    }
    pkbPopulator->addUses(lineNo, r->getVar());
    pkbPopulator->addVar(r->getVar());
}

void UsesExtractor::visit(std::shared_ptr<CallNode> c, int lineNo) {
    if (lineNo == SPConstants::INVALID_LINE_NO) {
        lineNo = c->getLine();
    }
    //pkbPopulator->addUses(lineNo, c->getVar());
    //pkbPopulator->addVar(c->getVar());
    std::cout<<"Populating calls: " << c->getVar() <<std::endl;
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
        if (Token::isValidName(token)) {
            pkbPopulator->addUses(lineNo, token);
        }
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
        if (Token::isValidName(token)) {
            pkbPopulator->addUses(lineNo, token);
        }
    }
    for (auto j: whStmts) {
        visit(j, lineNo);
    }
}

void UsesExtractor::visit(std::shared_ptr<ProcedureNode> p) {
    std::vector<std::shared_ptr<StmtNode>> pStmts = p->getStmtLst()->getStatements();
    for (auto j: pStmts) {
//        TODO: add vist and populate (proc,v)
    }
}


void FollowsExtractor::visit(std::shared_ptr<StmtLstNode> sl, int lineNo) {

    std::vector<std::shared_ptr<StmtNode>> stmts = sl->getStatements();
    vector<int> stmtLines;
    for(auto i: stmts) {
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
    for(auto i: stmts) {
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
        for(auto i: ifStmts) {
                stmtLines.push_back(i->getLine());
        }
        for(auto i: elseStmts) {
                stmtLines.push_back(i->getLine());
        }
        for(auto j: stmtLines) {
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
        for(auto j: stmtLines) {
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
    for(auto i: ifStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
            stmtLines.push_back(i->getLine());
        } else {
            visit(i, lineNo);
        }
    }
    for(auto i: elseStmts) {
        if (!(isIfNode(i) || isWhileNode(i))) {
            stmtLines.push_back(i->getLine());
        } else {
            visit(i, lineNo);
        }
    }
    for(auto j: stmtLines) {
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
    for(auto j: stmtLines) {
        if (lineNo != j) {
            pkbPopulator->addParentStar(lineNo, j);
        }
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
