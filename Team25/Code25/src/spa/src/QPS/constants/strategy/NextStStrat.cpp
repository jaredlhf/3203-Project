#include <memory>
#include "NextStStrat.h"

// Constructor function for NextStStrat
NextStStrat::NextStStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::resolve() {
    return createReturnStrategy();
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::createReturnStrategy() {
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

// Case: NextSt(_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::wildcardWildcard() {
    return QueryUtils::isNotEmpty(pkbRet->getAllLeftNext())
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: NextSt(_, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::wildcardConst() {
    std::unordered_set<int> stmts = pkbRet->getAllRightNext();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    return QueryUtils::contains(stmts, std::stoi(arg2Val))
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: NextSt(_, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::wildcardSyn() {
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s2Syn->getKeyword());
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });
    for (int stNum : s2Stmts) {
        if (QueryUtils::isNotEmpty(pkbRet->getLeftNextStar(stNum))) {
            resTable->addRow({ std::to_string(stNum) });
        }
    }

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: NextSt(1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::constWildcard() {
    std::unordered_set<int> stmts = pkbRet->getAllLeftNext();
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    return QueryUtils::contains(stmts, std::stoi(arg1Val))
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: NextSt(1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::constConst() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

    if (QueryUtils::contains(pkbRet->getRightNextStar(std::stoi(arg1Val)), std::stoi(arg2Val))) {
        return QpsTable::getDefaultOk();
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: NextSt(1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::constSyn() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s2Syn->getKeyword());
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

    for (int stNum : s2Stmts) {
        if (QueryUtils::contains(pkbRet->getRightNextStar(std::stoi(arg1Val)), stNum)) {
            resTable->addRow({ std::to_string(stNum) });
        }
    }
    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: NextSt(s1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::synWildcard() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s1Syn->getKeyword());
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });
    for (int stNum : s1Stmts) {
        if (QueryUtils::isNotEmpty(pkbRet->getRightNextStar(stNum))) {
            resTable->addRow({ std::to_string(stNum) });
        }
    }

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: NextSt(s1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::synConst() {
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s1Syn->getKeyword());
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

    for (int stNum : s1Stmts) {
        if (QueryUtils::contains(pkbRet->getLeftNextStar(std::stoi(arg2Val)), stNum)) {
            resTable->addRow({ std::to_string(stNum) });
        }
    }
    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: NextSt(s1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStStrat::synSyn() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<int> s1Stmts = s1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s1Syn->getKeyword());

    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<int> s2Stmts = s2Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(s2Syn->getKeyword());

    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });
    std::vector<std::pair<int, int>> argCombis;
    for (int arg1StNum : s1Stmts) {
        for (int arg2StNum : s2Stmts) {
            argCombis.push_back({ arg1StNum, arg2StNum });
        }
    }

    for (std::pair<int, int> argPair : argCombis) {
        int arg1StNum = argPair.first;
        int arg2StNum = argPair.second;
        if (QueryUtils::contains(pkbRet->getRightNextStar(arg1StNum), arg2StNum)) {
            // If s1 and s2 refer to the same synonym, only add if they are the same value
            if ((s1Syn->getName() != s2Syn->getName()) || (arg1StNum == arg2StNum)) {
                resTable->addRow({ std::to_string(arg1StNum), std::to_string(arg2StNum) });
            }
        }

    }

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
