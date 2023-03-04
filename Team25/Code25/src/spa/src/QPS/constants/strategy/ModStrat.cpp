#include "ModStrat.h"

// Constructor function for UsesStrat
ModStrat::ModStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::resolve() {
    return createReturnStrategy();
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::createReturnStrategy() {
    if (this->arg1->isConstant() && this->arg2->isWildcard()) return constWildcard();
    if (this->arg1->isConstant() && this->arg2->isConstant()) return constConst();
    if (this->arg1->isConstant() && this->arg2->isSynonym()) return constSyn();
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) return synWildcard();
    if (this->arg1->isSynonym() && this->arg2->isConstant()) return synConst();
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) return synSyn();

    return QpsTable::getDefaultSynErr();
}

// Case: Modifies(1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::constWildcard() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    return !pkbRet->getModVar(std::stoi(arg1Val)).empty()
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Modifies(1, "x")
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::constConst() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::unordered_set<std::string> pkbRes = pkbRet->getModVar(std::stoi(arg1Val));
    return std::find(pkbRes.begin(), pkbRes.end(), arg2Val) != pkbRes.end()
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Modifies(1, v1)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::constSyn() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Name = std::static_pointer_cast<Synonym>(this->arg2)->getName();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg2Name });
    std::unordered_set<std::string> pkbRes = pkbRet->getModVar(std::stoi(arg1Val));
    for (const std::string& res : pkbRes) {
        resTable->addRow({ res });
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Modifies(s1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::synWildcard() {
    std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    const std::string& arg1Name = arg1Syn->getName();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name });
    std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(arg1Syn->getKeyword());
    for (int stmtNum : arg1Stmts) {
        std::unordered_set<std::string> pkbRes = pkbRet->getModVar(stmtNum);
        if (!pkbRes.empty()) {
            resTable->addRow({ std::to_string(stmtNum) });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Modifies(s1, "x")
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::synConst() {
    std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    const std::string& arg1Name = arg1Syn->getName();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name });
    std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(arg1Syn->getKeyword());
    for (int stmtNum : arg1Stmts) {
        std::unordered_set<std::string> pkbRes = pkbRet->getModVar(stmtNum);
        if (std::find(pkbRes.begin(), pkbRes.end(), arg2Val) != pkbRes.end()) {
            resTable->addRow({ std::to_string(stmtNum) });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Modifies(s1, v2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::synSyn() {
    std::shared_ptr<Synonym> arg1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::shared_ptr<Synonym> arg2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    const std::string& arg1Name = arg1Syn->getName();
    const std::string& arg2Name = arg2Syn->getName();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg1Name, arg2Name });
    std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
        ? Clause::getEveryStmt(pkbRet)
        : pkbRet->getAllStmt(arg1Syn->getKeyword());
    for (int stmtNum : arg1Stmts) {
        std::unordered_set<std::string> pkbRes = pkbRet->getModVar(stmtNum);
        for (const std::string& res : pkbRes) {
            resTable->addRow({ std::to_string(stmtNum), res });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
