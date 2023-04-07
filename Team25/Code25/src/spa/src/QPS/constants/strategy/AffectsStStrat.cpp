#include <algorithm>
#include "AffectsStStrat.h"

// Constructor function for AffectsStStrat
AffectsStStrat::AffectsStStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
}

bool AffectsStStrat::hasNonAssignArgs() {
    if (this->arg1->isSynonym() &&
        (!std::static_pointer_cast<Synonym>(this->arg1)->matchesKeyword(Constants::ASSIGN)
            && !std::static_pointer_cast<Synonym>(this->arg1)->matchesKeyword(Constants::STMT))) {
        return true;
    }

    if (this->arg2->isSynonym() &&
        (!std::static_pointer_cast<Synonym>(this->arg2)->matchesKeyword(Constants::ASSIGN)
            && !std::static_pointer_cast<Synonym>(this->arg2)->matchesKeyword(Constants::STMT))) {
        return true;
    }

    if (this->arg1->isConstant() && !QueryUtils::isAssignStmt(std::stoi(std::static_pointer_cast<Value>(this->arg1)->getVal()), pkbRet)) {
        return true;
    }

    if (this->arg2->isConstant() && !QueryUtils::isAssignStmt(std::stoi(std::static_pointer_cast<Value>(this->arg2)->getVal()), pkbRet)) {
        return true;
    }

    return false;
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::resolve() {
    if (hasNonAssignArgs()) {
        return QpsTable::getDefaultNoMatch();
    }
    else {
        return createReturnStrategy();
    }
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::createReturnStrategy() {
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

// Case: Affects*(_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::wildcardWildcard() {
    std::unordered_set<std::string> procs = pkbRet->getAllProc();
    for (std::string proc : procs) {
        std::unordered_set<int> stmts = pkbRet->getStmt(proc);
        std::vector<std::pair<int, int>> stmtCombis;

        for (int stmt1 : stmts) {
            for (int stmt2 : stmts) {
                stmtCombis.push_back({ stmt1, stmt2 });
            }
        }

        for (std::pair<int, int> stmts : stmtCombis) {
            int stmt1 = stmts.first;
            int stmt2 = stmts.second;
            if (QueryUtils::affects(stmt1, stmt2, pkbRet)) {
                return QpsTable::getDefaultOk();
            }
        }
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: Affects*(_, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::wildcardConst() {
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    int arg2Stmt = std::stoi(arg2Val);
    std::string proc = pkbRet->getProc(arg2Stmt);
    std::unordered_set<int> stmts = pkbRet->getStmt(proc);

    for (int stmt1 : stmts) {
        if (QueryUtils::affects(stmt1, std::stoi(arg2Val), pkbRet)) {
            return QpsTable::getDefaultOk();
        }
    }

    return QpsTable::getDefaultNoMatch();
}

// Case: Affects*(_, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::wildcardSyn() {
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

    std::unordered_set<std::string> procs = pkbRet->getAllProc();
    for (std::string proc : procs) {
        std::unordered_set<int> stmts = pkbRet->getStmt(proc);
        std::vector<std::pair<int, int>> stmtCombis;

        for (int stmt2 : stmts) {
            for (int stmt1 : stmts) {
                if (QueryUtils::affects(stmt1, stmt2, pkbRet)) {
                    resTable->addRow({ std::to_string(stmt2) });
                    break;
                }
            }
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Affects*(1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::constWildcard() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    int arg1Stmt = std::stoi(arg1Val);
    std::string proc = pkbRet->getProc(arg1Stmt);

    std::unordered_set<int> stmts = pkbRet->getStmt(proc);

    for (int stmt2 : stmts) {
        if (QueryUtils::affects(std::stoi(arg1Val), stmt2, pkbRet)) {
            return QpsTable::getDefaultOk();
        }
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: Affects*(1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::constConst() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

    if (QueryUtils::affectsStar(std::stoi(arg1Val), std::stoi(arg2Val), pkbRet)) {
        QueryUtils::clearCache();
        return QpsTable::getDefaultOk();
    }
    return QpsTable::getDefaultNoMatch();
}

// Case: Affects*(1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::constSyn() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s2Syn->getName() });

    int arg1Stmt = std::stoi(arg1Val);
    std::string proc = pkbRet->getProc(arg1Stmt);
    std::unordered_set<int> stmts = pkbRet->getStmt(proc);

    for (int stmt2 : stmts) {
        if (QueryUtils::affectsStar(std::stoi(arg1Val), stmt2, pkbRet)) {
            resTable->addRow({ std::to_string(stmt2) });
        }
    }

    QueryUtils::clearCache();

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Affects*(s1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::synWildcard() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

    std::unordered_set<std::string> procs = pkbRet->getAllProc();
    for (std::string proc : procs) {
        std::unordered_set<int> stmts = pkbRet->getStmt(proc);
        std::vector<std::pair<int, int>> stmtCombis;

        for (int stmt1 : stmts) {
            for (int stmt2 : stmts) {
                if (QueryUtils::affects(stmt1, stmt2, pkbRet)) {
                    resTable->addRow({ std::to_string(stmt1) });
                    break;
                }
            }
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Affects*(s1, 2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::synConst() {
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName() });

    int arg2Stmt = std::stoi(arg2Val);
    std::string proc = pkbRet->getProc(arg2Stmt);
    std::unordered_set<int> stmts = pkbRet->getStmt(proc);

    for (int stmt1 : stmts) {
        if (QueryUtils::affectsStar(stmt1, std::stoi(arg2Val), pkbRet)) {
            resTable->addRow({ std::to_string(stmt1) });
        }
    }

    QueryUtils::clearCache();

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: Affects*(s1, s2)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> AffectsStStrat::synSyn() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s2Syn->getName() });

    std::unordered_set<std::string> procs = pkbRet->getAllProc();
    for (std::string proc : procs) {
        std::unordered_set<int> stmts = pkbRet->getStmt(proc);
        std::vector<std::pair<int, int>> stmtCombis;

        for (int stmt1 : stmts) {
            for (int stmt2 : stmts) {
                stmtCombis.push_back({ stmt1, stmt2 });
            }
        }

        for (std::pair<int, int> stmts : stmtCombis) {
            int stmt1 = stmts.first;
            int stmt2 = stmts.second;
            if (QueryUtils::affectsStar(stmt1, stmt2, pkbRet)) {
                resTable->addRow({ std::to_string(stmt1), std::to_string(stmt2) });
            }
        }
    }

    QueryUtils::clearCache();

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
