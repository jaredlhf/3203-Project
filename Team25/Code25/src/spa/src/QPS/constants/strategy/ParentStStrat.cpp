#include "ParentStStrat.h"

// Constructor function for Strat
ParentStStrat::ParentStStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::resolve() {
    return createReturnStrategy();
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::createReturnStrategy() {
    if (this->arg1->isWildcard() && this->arg2->isWildcard()) return wildcardWildcard();
    if (this->arg1->isWildcard() && this->arg2->isConstant()) return wildcardConst();
    if (this->arg1->isWildcard() && this->arg2->isSynonym()) return wildcardSyn();
    if (this->arg1->isConstant() && this->arg2->isWildcard()) return constWildcard();
    if (this->arg1->isConstant() && this->arg2->isConstant()) return constConst();
    if (this->arg1->isConstant() && this->arg2->isSynonym()) return constSyn();
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) return synWildcard();
    if (this->arg1->isSynonym() && this->arg2->isConstant()) return synConst();
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) return synSyn();

    return QpsTable::getDefaultSynErr();
}

// Case: ParentSt(_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::wildcardWildcard() {
    std::unordered_set<int> stmts = Clause::getEveryStmt(pkbRet);
    for (int stNum : stmts) {
        if (pkbRet->getChildrenStar(stNum).size() > 0) {
            return QpsTable::getDefaultOk();
        }
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: ParentSt(_, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::wildcardConst() {
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
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::wildcardSyn() {
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
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::constWildcard() {
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
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::constConst() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

    if (pkbRet->getChildrenStar(std::stoi(arg1Val)).count(std::stoi(arg2Val)) > 0) {
        return QpsTable::getDefaultOk();
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: ParentSt(1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::constSyn() {
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
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::synWildcard() {
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
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::synConst() {
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
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStStrat::synSyn() {
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
