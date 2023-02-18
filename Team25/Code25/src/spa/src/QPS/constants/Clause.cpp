#include <iostream>
#include "Clause.h"


// Protected static functions
std::unordered_set<int> Clause::getEveryStmt(std::shared_ptr<PkbRetriever> pkbRet) {
    std::vector<std::string> stmtTypes({ Constants::ASSIGN, Constants::CALL, Constants::IF,
            Constants::WHILE, Constants::PRINT, Constants::READ });
    std::unordered_set<int> res;

    for (const std::string& stmtType : stmtTypes) {
        std::unordered_set<int> results = pkbRet->getAllStmt(stmtType);
        for (int ans : results) {
            res.insert(ans);
        }
    }

    return res;
}

// Constructor function for Clause
Clause::Clause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) {
	this->arg1 = arg1;
	this->arg2 = arg2;
}

// Clause functions
std::string Clause::getKeyword() {
    return this->keyword;
}

bool Clause::compare(std::shared_ptr<Clause> other) {
    if (this->getKeyword() != other->getKeyword()) {
        return false;
    }

    bool isSameArg1 = false;
    bool isSameArg2 = false;

    if (this->arg1->isConstant() && other->arg1->isConstant()) {
        isSameArg1 = std::static_pointer_cast<Value>(this->arg1)->compare(std::static_pointer_cast<Value>(other->arg1));
    }
    else if (this->arg1->isWildcard() && other->arg1->isWildcard()) {
        isSameArg1 = std::static_pointer_cast<Wildcard>(this->arg1)->compare(std::static_pointer_cast<Wildcard>(other->arg1));
    }
    else if (this->arg1->isSynonym() && other->arg1->isSynonym()) {
        isSameArg1 = std::static_pointer_cast<Synonym>(this->arg1)->compare(std::static_pointer_cast<Synonym>(other->arg1));
    }

    if (this->arg2->isConstant() && other->arg2->isConstant()) {
        isSameArg2 = std::static_pointer_cast<Value>(this->arg2)->compare(std::static_pointer_cast<Value>(other->arg2));
    }
    else if (this->arg2->isWildcard() && other->arg2->isWildcard()) {
        isSameArg2 = std::static_pointer_cast<Wildcard>(this->arg2)->compare(std::static_pointer_cast<Wildcard>(other->arg2));
    }
    else if (this->arg2->isSynonym() && other->arg2->isSynonym()) {
        isSameArg2 = std::static_pointer_cast<Synonym>(this->arg2)->compare(std::static_pointer_cast<Synonym>(other->arg2));
    }

    return isSameArg1 && isSameArg2;
}

// Factory function for Clause
std::shared_ptr<Clause> Clause::create(const std::string clauseType, std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) {
    std::shared_ptr<Clause> res;

    if (clauseType == Constants::USES) res = std::make_shared<UsesClause>(UsesClause(arg1, arg2));
    if (clauseType == Constants::MODIFIES) res = std::make_shared<ModifiesClause>(ModifiesClause(arg1, arg2));
    if (clauseType == Constants::PARENT) res = std::make_shared<ParentClause>(ParentClause(arg1, arg2));
    if (clauseType == Constants::PARENTST) res = std::make_shared<ParentStClause>(ParentStClause(arg1, arg2));
    if (clauseType == Constants::FOLLOWS) res = std::make_shared<FollowsClause>(FollowsClause(arg1, arg2));
    if (clauseType == Constants::FOLLOWSST) res = std::make_shared<FollowsStClause>(FollowsStClause(arg1, arg2));
    if (clauseType == Constants::PATTERN) res = std::make_shared<PatternClause>(PatternClause(arg1, arg2));

    return res;
}

// Overriden clause constructor functions
UsesClause::UsesClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::USES;
}

ModifiesClause::ModifiesClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::MODIFIES;
}

ParentClause::ParentClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::PARENT;
}

ParentStClause::ParentStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::PARENTST;
}

FollowsClause::FollowsClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::FOLLOWS;
}

FollowsStClause::FollowsStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::FOLLOWSST;
}

PatternClause::PatternClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::PATTERN;
}

// Overriden clause functions
bool Clause::isWrongArgs() {
    return true;
}

bool Clause::isSemInvalid() {
    return true;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> Clause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    std::cout << "resolve clause" << std::endl;
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();
}

bool Clause::isPatternClause() {
    return false;
}


// UsesClause overriden clause functions
/*
    For uses clauses, args is wrong if arg1 is not int, or arg2 is int
*/
bool UsesClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }
    return false;
}

/*
    For uses clauses, args is sem invalid if arg1 is not stmtsyn, or arg2 is not varsyn
*/
bool UsesClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isVariableSyn()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> UsesClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err) 
    // OR arg1 is wildcard (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    if (this->arg1->isWildcard()) {
        return QpsTable::getDefaultSemErr();
    }

    // Case: Uses(1, _)
    if (this->arg1->isConstant() && this->arg2->isWildcard()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        return !pkbRet->getUsesVar(std::stoi(arg1Val)).empty()
            ? QpsTable::getDefaultOk()
            : QpsTable::getDefaultNoMatch();
    }

    // Case: Uses(1, "x")
    if (this->arg1->isConstant() && this->arg2->isConstant()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        /*TODO add line to find results: std::unordered_set<std::string> pkbRes = getUsesVar(arg1Val); */
        const std::string& pkbRes = pkbRet->getUsesVar(std::stoi(arg1Val));
        std::cout << "Uses test" << pkbRes << " " << arg2Val << std::endl;
        return pkbRes == arg2Val /* TODO replace condition with std::find(pkbRes.begin(), pkbRes.end(), arg2Val) != pkbRes.end()  */
            ? QpsTable::getDefaultOk()
            : QpsTable::getDefaultNoMatch();
    }

    // Case: Uses(1, v1)
    if (this->arg1->isConstant() && this->arg2->isSynonym()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        const std::string& arg2Name = std::static_pointer_cast<Synonym>(this->arg2)->getName();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg2Name });
        std::unordered_set<std::string> pkbRes = {} /*TODO replace computation with getUsesVar(arg1Val);*/;
        for (const std::string& val : pkbRes) {
            resTable->addRow({ val });
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Uses(s1, _)
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
        std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        const std::string& arg1Name = arg1Syn->getName();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name });
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            std::unordered_set<std::string> pkbRes = {} /*TODO replace computation with getUsesVar(stmtNum);*/;
            if (pkbRes.size() > 0) {
                resTable->addRow({ std::to_string(stmtNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Uses(s1, "x")
    if (this->arg1->isSynonym() && this->arg2->isConstant()) {
        std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        const std::string& arg1Name = arg1Syn->getName();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name });
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            std::unordered_set<std::string> pkbRes = {} /*TODO replace computation with getUsesVar(stmtNum);*/;
            if (std::find(pkbRes.begin(), pkbRes.end(), arg2Val) != pkbRes.end()) {
                resTable->addRow({ std::to_string(stmtNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Uses(s1, v2)
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::shared_ptr<Synonym> arg2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        const std::string& arg1Name = arg1Syn->getName();
        const std::string& arg2Name = arg2Syn->getName();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name, arg2Name });
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            std::unordered_set<std::string> pkbRes = {} /*TODO replace computation with getUsesVar(stmtNum);*/;
            for (const std::string& arg2Match : pkbRes) {
                resTable->addRow({ std::to_string(stmtNum), arg2Match });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    return QpsTable::getDefaultSynErr();
}


// Modifies overriden clause functions
/*
    For modifies clauses, args is wrong if arg1 is not int, or arg2 is int
*/
bool ModifiesClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For modifies clauses, args is sem invalid if arg1 is not stmtsyn, or arg2 is not varsyn
*/
bool ModifiesClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isVariableSyn()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModifiesClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err) 
     // OR arg1 is wildcard (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    if (this->arg1->isWildcard()) {
        return QpsTable::getDefaultSemErr();
    }

    // Case: Modifies(1, _)
    if (this->arg1->isConstant() && this->arg2->isWildcard()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        return !pkbRet->getModVar(std::stoi(arg1Val)).empty()
            ? QpsTable::getDefaultOk()
            : QpsTable::getDefaultNoMatch();
    }

    // Case: Modifies(1, "x")
    if (this->arg1->isConstant() && this->arg2->isConstant()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        const std::string& pkbRes = pkbRet->getModVar(std::stoi(arg1Val));
        return pkbRes == arg2Val
            ? QpsTable::getDefaultOk()
            : QpsTable::getDefaultNoMatch();
    }

    // Case: Modifies(1, v1)
    if (this->arg1->isConstant() && this->arg2->isSynonym()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        const std::string& arg2Name = std::static_pointer_cast<Synonym>(this->arg2)->getName();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg2Name });
        const std::string& pkbRes = pkbRet->getModVar(std::stoi(arg1Val));
        if (!pkbRes.empty()) {
            resTable->addRow({ pkbRes });
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Modifies(s1, _)
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
        std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        const std::string& arg1Name = arg1Syn->getName();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name });
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            const std::string& pkbRes = pkbRet->getModVar(stmtNum) /*TODO replace computation with getUsesVar(stmtNum);*/;
            if (!pkbRes.empty()) {
                resTable->addRow({ std::to_string(stmtNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Modifies(s1, "x")
    if (this->arg1->isSynonym() && this->arg2->isConstant()) {
        std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        const std::string& arg1Name = arg1Syn->getName();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name });
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            const std::string& pkbRes = pkbRet->getModVar(stmtNum);
            if (pkbRes == arg2Val) {
                resTable->addRow({ std::to_string(stmtNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Modifies(s1, v2)
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::shared_ptr<Synonym> arg2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        const std::string& arg1Name = arg1Syn->getName();
        const std::string& arg2Name = arg2Syn->getName();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name, arg2Name });
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            const std::string& pkbRes = pkbRet->getModVar(stmtNum);
            resTable->addRow({ std::to_string(stmtNum), pkbRes });
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    return QpsTable::getDefaultSynErr();
}

// Parent overriden clause functions
/*
    For parent clauses, args is wrong both args are not int
*/
bool ParentClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For parent clauses, args is sem invalid if either syns is not stmtsyn
*/
bool ParentClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    // Case: Parent(_, _)
    if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        for (int stNum : stmts) {
            if (pkbRet->getChildren(stNum).size() > 0) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: Parent(_, 2)
    if (this->arg1->isWildcard() && this->arg2->isConstant()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        for (int stNum : stmts) {
            if (pkbRet->getChildren(stNum).count(std::stoi(arg2Val)) > 0) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: Parent(_, s2)
    if (this->arg1->isWildcard() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });
        for (int stNum : s2Stmts) {
            if (pkbRet->getParent(stNum) != -1) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Parent(1, _)
    if (this->arg1->isConstant() && this->arg2->isWildcard()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        for (int stNum : stmts) {
            if (pkbRet->getParent(stNum) == std::stoi(arg1Val)) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: Parent(1, 2)
    if (this->arg1->isConstant() && this->arg2->isConstant()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

        if (pkbRet->getChildren(std::stoi(arg1Val)).count(std::stoi(arg2Val)) > 0) {
            return QpsTable::getDefaultOk();
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: Parent(1, s2)
    if (this->arg1->isConstant() && this->arg2->isSynonym()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

        for (int stNum : s2Stmts) {
            if (pkbRet->getParent(stNum) == std::stoi(arg1Val)) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }
        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Parent(s1, _)
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });
        for (int stNum : s1Stmts) {
            if (pkbRet->getChildren(stNum).size() > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Parent(s1, 2)
    if (this->arg1->isSynonym() && this->arg2->isConstant()) {
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

        for (int stNum : s1Stmts) {
            if (pkbRet->getParent(std::stoi(arg2Val)) == stNum) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }
        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Parent(s1, s2)
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());

        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());

        // Edge case: if s1 and s2 are the same var name, return no match
        if (s1Syn->getName() == s2Syn->getName()) {
            return QpsTable::getDefaultNoMatch();
        }

        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });

        for (int arg1StNum : s1Stmts) {
            for (int arg2StNum : s2Stmts) {
                if (pkbRet->getParent(arg2StNum) == arg1StNum) {
                    resTable->addRow({ std::to_string(arg1StNum), std::to_string(arg2StNum) });
                }
            }

        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    return QpsTable::getDefaultSynErr();
}

// Follows overriden clause functions
/*
    For follows clauses, args is wrong both args are not int
*/
bool FollowsClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For follows clauses, args is sem invalid if either syns is not stmtsyn
*/
bool FollowsClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    // Case: Follows(_, _)
    if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
        return pkbRet->getAllFollowees().size() > 0 
            ? QpsTable::getDefaultOk()
            : QpsTable::getDefaultNoMatch();
    }

    // Case: Follows(_, 2)
    if (this->arg1->isWildcard() && this->arg2->isConstant()) {
        std::unordered_set<int> stmts = pkbRet->getAllFollowers();
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        return stmts.count(std::stoi(arg2Val)) > 0
            ? QpsTable::getDefaultOk()
            : QpsTable::getDefaultNoMatch();
    }

    // Case: Follows(_, s2)
    if (this->arg1->isWildcard() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });
        for (int stNum : s2Stmts) {
            if (pkbRet->getFollowee(stNum) != -1) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Follows(1, _)
    if (this->arg1->isConstant() && this->arg2->isWildcard()) {
        std::unordered_set<int> stmts = pkbRet->getAllFollowees();
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        return stmts.count(std::stoi(arg1Val)) > 0
            ? QpsTable::getDefaultOk()
            : QpsTable::getDefaultNoMatch();
    }

    // Case: Follows(1, 2)
    if (this->arg1->isConstant() && this->arg2->isConstant()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

        if (pkbRet->getFollower(std::stoi(arg1Val)) == std::stoi(arg2Val)) {
            return QpsTable::getDefaultOk();
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: Follows(1, s2)
    if (this->arg1->isConstant() && this->arg2->isSynonym()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

        for (int stNum : s2Stmts) {
            if (pkbRet->getFollower(std::stoi(arg1Val)) == stNum) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }
        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Follows(s1, _)
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });
        for (int stNum : s1Stmts) {
            if (pkbRet->getFollower(stNum) != -1) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Follows(s1, 2)
    if (this->arg1->isSynonym() && this->arg2->isConstant()) {
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

        for (int stNum : s1Stmts) {
            if (pkbRet->getFollowee(std::stoi(arg2Val)) == stNum) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }
        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: Follows(s1, s2)
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());

        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());

        // Edge case: if s1 and s2 are the same var name, return no match
        if (s1Syn->getName() == s2Syn->getName()) {
            return QpsTable::getDefaultNoMatch();
        }

        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });

        for (int arg1StNum : s1Stmts) {
            for (int arg2StNum : s2Stmts) {
                if (pkbRet->getFollower(arg1StNum) == arg2StNum /*TODO replace with getChild(arg1StNum) == arg2StNum  */) {
                    resTable->addRow({ std::to_string(arg1StNum), std::to_string(arg2StNum) });
                }
            }

        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    return QpsTable::getDefaultSynErr();
}

// ParentSt overriden clause functions
/*
    For ParentSt clauses, args is wrong both args are not int
*/
bool ParentStClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For parentst clauses, args is sem invalid if either syns is not stmtsyn
*/
bool ParentStClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    // Case: ParentSt(_, _)
    if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        for (int stNum : stmts) {
            if (pkbRet->getChildrenStar(stNum).size() > 0) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: ParentSt(_, 2)
    if (this->arg1->isWildcard() && this->arg2->isConstant()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        for (int stNum : stmts) {
            if (pkbRet->getChildrenStar(stNum).count(std::stoi(arg2Val)) > 0) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: ParentSt(_, s2)
    if (this->arg1->isWildcard() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });
        for (int stNum : s2Stmts) {
            if (pkbRet->getParentStar(stNum).size() > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: ParentSt(1, _)
    if (this->arg1->isConstant() && this->arg2->isWildcard()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        for (int stNum : stmts) {
            if (pkbRet->getParentStar(stNum).count(std::stoi(arg1Val)) > 0) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: ParentSt(1, 2)
    if (this->arg1->isConstant() && this->arg2->isConstant()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

        if (pkbRet->getChildrenStar(std::stoi(arg1Val)).count(std::stoi(arg2Val)) > 0) {
            return QpsTable::getDefaultOk();
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: ParentSt(1, s2)
    if (this->arg1->isConstant() && this->arg2->isSynonym()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

        for (int stNum : s2Stmts) {
            if (pkbRet->getParentStar(stNum).count(std::stoi(arg1Val)) > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }
        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: ParentSt(s1, _)
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });
        for (int stNum : s1Stmts) {
            if (pkbRet->getChildrenStar(stNum).size() > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: ParentSt(s1, 2)
    if (this->arg1->isSynonym() && this->arg2->isConstant()) {
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

        for (int stNum : s1Stmts) {
            if (pkbRet->getChildrenStar(stNum).count(std::stoi(arg2Val)) > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }
        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: ParentSt(s1, s2)
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());

        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());

        // Edge case: if s1 and s2 are the same var name, return no match
        if (s1Syn->getName() == s2Syn->getName()) {
            return QpsTable::getDefaultNoMatch();
        }

        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });

        for (int arg1StNum : s1Stmts) {
            for (int arg2StNum : s2Stmts) {
                if (pkbRet->getParentStar(arg2StNum).count(arg1StNum) > 0) {
                    resTable->addRow({ std::to_string(arg1StNum), std::to_string(arg2StNum) });
                }
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    return QpsTable::getDefaultSynErr();
}

// FollowsSt overriden clause functions
/*
    For FollowsSt clauses, args is wrong both args are not int
*/
bool FollowsStClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For followsst clauses, args is sem invalid if either syns is not stmtsyn
*/
bool FollowsStClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    // Case: FollowsSt(_, _)
    if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        for (int stNum : stmts) {
            if (pkbRet->getFollowerStar(stNum).size() > 0) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: FollowsSt(_, 2)
    if (this->arg1->isWildcard() && this->arg2->isConstant()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        for (int stNum : stmts) {
            if (pkbRet->getFollowerStar(stNum).count(std::stoi(arg2Val)) > 0) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: FollowsSt(_, s2)
    if (this->arg1->isWildcard() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });
        for (int stNum : s2Stmts) {
            if (pkbRet->getFolloweeStar(stNum).size() > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: FollowsSt(1, _)
    if (this->arg1->isConstant() && this->arg2->isWildcard()) {
        std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        for (int stNum : stmts) {
            if (pkbRet->getFolloweeStar(stNum).count(std::stoi(arg1Val)) > 0) {
                return QpsTable::getDefaultOk();
            }
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: FollowsSt(1, 2)
    if (this->arg1->isConstant() && this->arg2->isConstant()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

        if (pkbRet->getFollowerStar(std::stoi(arg1Val)).count(std::stoi(arg2Val)) > 0) {
            return QpsTable::getDefaultOk();
        }
        return QpsTable::getDefaultNoMatch();
    }

    // Case: FollowsSt(1, s2)
    if (this->arg1->isConstant() && this->arg2->isSynonym()) {
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

        for (int stNum : s2Stmts) {
            if (pkbRet->getFolloweeStar(stNum).count(std::stoi(arg1Val)) > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }
        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: FollowsSt(s1, _)
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });
        for (int stNum : s1Stmts) {
            if (pkbRet->getFollowerStar(stNum).size() > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: FollowsSt(s1, 2)
    if (this->arg1->isSynonym() && this->arg2->isConstant()) {
        const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

        for (int stNum : s1Stmts) {
            if (pkbRet->getFollowerStar(stNum).count(std::stoi(arg2Val)) > 0) {
                resTable->addRow({ std::to_string(stNum) });
            }
        }
        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // Case: FollowsSt(s1, s2)
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
        std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s1Syn->getKeyword());

        std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
        std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(s2Syn->getKeyword());

        // Edge case: if s1 and s2 are the same var name, return no match
        if (s1Syn->getName() == s2Syn->getName()) {
            return QpsTable::getDefaultNoMatch();
        }

        std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });

        for (int arg1StNum : s1Stmts) {
            for (int arg2StNum : s2Stmts) {
                if (pkbRet->getFolloweeStar(arg2StNum).count(arg1StNum) > 0) {
                    resTable->addRow({ std::to_string(arg1StNum), std::to_string(arg2StNum) });
                }
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    return QpsTable::getDefaultSynErr();
}

// Pattern overriden clause functions
/*
    For Pattern clauses, args is wrong if arg1 is int const, or if arg2 is synonym or is int const
*/
bool PatternClause::isWrongArgs() {
    if (this->arg1->isConstant() && std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    if (this->arg2->isSynonym()) {
        return true;
    }

    return false;
}

/*
    For pattern clauses, args is sem invalid if arg1 is not variable syn
*/
bool PatternClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isVariableSyn()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternClause::resolve(
    std::shared_ptr<PkbRetriever> pkbRet, std::shared_ptr<Synonym> patternSynonym) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) or wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid() || !patternSynonym->matchesKeyword(Constants::ASSIGN)) {
        return QpsTable::getDefaultSemErr();
    }

    // Preprocessing: Get all matches for the assign/while/if synonym
    std::vector<std::string> synMatches;
    const std::string& synName = patternSynonym->getName();
    for (int val : pkbRet->getAllStmt(patternSynonym->getKeyword())) {
        synMatches.push_back(std::to_string(val));
    }
    
    // If both args are wildcard
    if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
        std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);

        std::cout << "This is 2 wildcard pattern clause" << std::endl;
        std::cout << "arg2 val is " << wcArg2->getVal() << std::endl;

        // Case: pattern a1 (_, _)
        if (wcArg2->isGenericWildcard()) {
            std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
            for (const std::string& val : synMatches) {
                resTable->addRow({ val });
            }

            return resTable->getData().size() > 0
                ? std::make_pair(Constants::ClauseResult::OK, resTable)
                : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
        }

        // Case: pattern a1 (_, _"x"_)
        const std::string& wcPattern = wcArg2->getVal();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
        for (const std::string& stNum : synMatches) {
            const std::string& pkbPattern = pkbRet->getAssignRhs(std::stoi(stNum));
            if (StringUtils::tokenInOp(pkbPattern, wcPattern)) {
                resTable->addRow({ stNum });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // If arg1 is constant and arg2 is wildcard
    if (this->arg1->isConstant() && this->arg2->isWildcard()) {
        std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
        const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();

        // Case: pattern a1 ("x", _)
        if (wcArg2->isGenericWildcard()) {
            std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
            std::unordered_set<int> pkbStmtMatches = pkbRet->getAssignLhs(arg1Val);
            for (int intVal : pkbStmtMatches) {
                resTable->addRow({ std::to_string(intVal) });
            }

            return resTable->getData().size() > 0
                ? std::make_pair(Constants::ClauseResult::OK, resTable)
                : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
        }

        // Case: pattern a1 ("x", _"y"_)
        const std::string& wcPattern = wcArg2->getVal();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
        std::unordered_set<int> pkbStmtMatches = pkbRet->getAssignLhs(arg1Val);
        for (int intVal : pkbStmtMatches) {
            const std::string& pkbPattern = pkbRet->getAssignRhs(intVal);
            if (StringUtils::tokenInOp(pkbPattern, wcPattern)) {
                resTable->addRow({ std::to_string(intVal) });
            }
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    // If arg1 is VariableSynonym and arg2 is wildcard
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
        std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
        std::shared_ptr<Synonym> synArg1 = std::static_pointer_cast<Synonym>(this->arg1);

        // Case: pattern a1 (v1, _)
        if (wcArg2->isGenericWildcard()) {
            std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName, synArg1->getName() });
            for (const std::string& a1SynMatch : synMatches) {
                const std::string& v1Match = pkbRet->getModVar(std::stoi(a1SynMatch)) /*TODO replace with getModVar(std::atoi(a1SynMatch))*/;
                if (!v1Match.empty()) {
                    resTable->addRow({ a1SynMatch, v1Match });
                }
            }

            return resTable->getData().size() > 0
                ? std::make_pair(Constants::ClauseResult::OK, resTable)
                : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
        }

        // Case: pattern a1 (v1, _"y"_)
        const std::string& wcPattern = wcArg2->getVal();
        std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName, synArg1->getName() });
        for (const std::string& a1SynMatch : synMatches) {
            const std::string& pkbPattern = pkbRet->getAssignRhs(std::stoi(a1SynMatch));
            if (StringUtils::tokenInOp(pkbPattern, wcPattern)) {
                const std::string& v1Match = pkbRet->getModVar(std::stoi(a1SynMatch));
                if (!v1Match.empty()) {
                    resTable->addRow({ a1SynMatch, v1Match });
                }
            }
            
        }

        return resTable->getData().size() > 0
            ? std::make_pair(Constants::ClauseResult::OK, resTable)
            : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
    }

    return QpsTable::getDefaultSynErr();
}

bool PatternClause::isPatternClause() {
    return true;
}