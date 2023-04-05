#include <algorithm>
#include "CallsStStrat.h"

// Constructor function for CallsStStrat
CallsStStrat::CallsStStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::resolve() {
    return createReturnStrategy();
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::createReturnStrategy() {
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

// Case: CallsSt(_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::wildcardWildcard() {
    return QueryUtils::isNotEmpty(pkbRet->getAllLeftCallStar())
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: CallsSt(_, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::wildcardConst() {
    std::unordered_set<std::string> procs = pkbRet->getAllRightCallStar();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    return QueryUtils::contains(procs, arg2Val)
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: CallsSt(_, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::wildcardSyn() {
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<std::string> s2Procs = pkbRet->getAllProc();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });
    for (std::string proc : s2Procs) {
        if (QueryUtils::isNotEmpty(pkbRet->getLeftCallStar(proc))) {
            resTable->addRow({ proc });
        }
    }

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: CallsSt(1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::constWildcard() {
    std::unordered_set<std::string> stmts = pkbRet->getAllLeftCallStar();
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    return QueryUtils::contains(stmts, arg1Val)
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: CallsSt(1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::constConst() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

    if (QueryUtils::contains(pkbRet->getRightCallStar(arg1Val), arg2Val)) {
        return QpsTable::getDefaultOk();
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: CallsSt(1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::constSyn() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<std::string> s2Procs = pkbRet->getAllProc();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

    for (std::string proc : s2Procs) {
        if (QueryUtils::contains(pkbRet->getRightCallStar(arg1Val), proc)) {
            resTable->addRow({ proc });
        }
    }
    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: CallsSt(s1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::synWildcard() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<std::string> s1Procs = pkbRet->getAllProc();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });
    for (std::string proc : s1Procs) {
        if (QueryUtils::isNotEmpty(pkbRet->getRightCallStar(proc))) {
            resTable->addRow({ proc });
        }
    }

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: CallsSt(s1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::synConst() {
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<std::string> s1Procs = pkbRet->getAllProc();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

    for (std::string proc : s1Procs) {
        if (QueryUtils::contains(pkbRet->getLeftCallStar(arg2Val), proc)) {
            resTable->addRow({ proc });
        }
    }
    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: CallsSt(s1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStStrat::synSyn() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<std::string> s1Procs = pkbRet->getAllProc();

    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<std::string> s2Procs = pkbRet->getAllProc();

    // Edge case: if s1 and s2 are the same var name, return no match
    if (s1Syn->getName() == s2Syn->getName()) {
        return QpsTable::getDefaultNoMatch();
    }

    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });
    std::vector<std::pair<std::string, std::string>> argCombis;

    for (std::string arg1Proc : s1Procs) {
        for (std::string arg2Proc : s2Procs) {
            argCombis.push_back({ arg1Proc, arg2Proc });
        }
    }

    for (std::pair<std::string, std::string> argPair : argCombis) {
        std::string arg1Proc = argPair.first;
        std::string arg2Proc = argPair.second;
        if (pkbRet->getRightCallStar(arg1Proc).count(arg2Proc) > 0) {
            resTable->addRow({ arg1Proc, arg2Proc });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
