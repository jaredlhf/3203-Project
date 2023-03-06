#include "CallsStrat.h"

// Constructor function for CallsStrat
CallsStrat::CallsStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::resolve() {
    return createReturnStrategy();
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::createReturnStrategy() {
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

// Case: Calls(_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::wildcardWildcard() {
    return pkbRet->getAllLeftCall().size() > 0
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Calls(_, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::wildcardConst() {
    std::unordered_set<std::string> procs = pkbRet->getAllRightCall();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    return procs.count(arg2Val) > 0
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Calls(_, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::wildcardSyn() {
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<std::string> s2Procs = pkbRet->getAllProc();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });
    for (std::string proc : s2Procs) {
        if (pkbRet->getLeftCall(proc).size() > 0) {
            resTable->addRow({ proc });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Calls(1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::constWildcard() {
    std::unordered_set<std::string> procs = pkbRet->getAllLeftCall();
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    return procs.count(arg1Val) > 0
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Calls(1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::constConst() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

    if (pkbRet->getRightCall(arg1Val).count(arg2Val) > 0) {
        return QpsTable::getDefaultOk();
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: Calls(1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::constSyn() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<std::string> s2Procs = pkbRet->getAllProc();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

    for (std::string proc : s2Procs) {
        if (pkbRet->getRightCall(arg1Val).count(proc) > 0) {
            resTable->addRow({ proc });
        }
    }
    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Calls(s1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::synWildcard() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<std::string> s1Procs = pkbRet->getAllProc();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });
    for (std::string proc : s1Procs) {
        if (pkbRet->getRightCall(proc).size() > 0) {
            resTable->addRow({ proc });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Calls(s1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::synConst() {
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<std::string> s1Procs = pkbRet->getAllProc();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

    for (std::string proc : s1Procs) {
        if (pkbRet->getLeftCall(arg2Val).count(proc) > 0) {
            resTable->addRow({ proc });
        }
    }
    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Calls(s1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStrat::synSyn() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::unordered_set<std::string> s1Procs = pkbRet->getAllProc();

    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::unordered_set<std::string> s2Procs = pkbRet->getAllProc();

    // Edge case: if s1 and s2 are the same var name, return no match
    if (s1Syn->getName() == s2Syn->getName()) {
        return QpsTable::getDefaultNoMatch();
    }

    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });

    for (std::string arg1Proc : s1Procs) {
        for (std::string arg2Proc : s2Procs) {
            if (pkbRet->getRightCall(arg1Proc).count(arg2Proc) > 0) {
                resTable->addRow({ arg1Proc, arg2Proc });
            }
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
