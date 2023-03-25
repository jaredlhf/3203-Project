#include <algorithm>
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

std::unordered_set<std::string> getAllVarModByProc(const std::string& proc, std::shared_ptr<PkbRetriever> pkbRet) {
    std::unordered_set<std::string> res;
    std::unordered_set<std::string> allProcs = pkbRet->getRightCallStar(proc);
    // Add proc to the full list of procs that we need to check
    allProcs.insert(proc);

    for (const std::string& currProc : allProcs) {
        std::unordered_set<std::string> currProcVars = pkbRet->getModPVar(currProc);
        for (const std::string& var : currProcVars) {
            res.insert(var);
        }
    }

    return res;
}

std::unordered_set<std::string> getAllVarModByStmt(int lineNum, std::shared_ptr<PkbRetriever> pkbRet) {
    std::unordered_set<std::string> res;

    // Insert all vars modified by stmt (without considering called procs within stmt yet)
    std::unordered_set<std::string> stmtVars = pkbRet->getModVar(lineNum);
    res.insert(stmtVars.begin(), stmtVars.end());

    // Add vars for all procs called within stmt
    std::unordered_set<std::string> calledProcs = pkbRet->getConProc(lineNum);
    for (const std::string& proc : calledProcs) {
        std::unordered_set<std::string> procVars = getAllVarModByProc(proc, pkbRet);
        res.insert(procVars.begin(), procVars.end());
    }

    return res;
}

bool isModIndirectly(const std::string& proc, const std::string& var, std::shared_ptr<PkbRetriever> pkbRet) {
    std::unordered_set<std::string> modVars = getAllVarModByProc(proc, pkbRet);
    return find(modVars.begin(), modVars.end(), var) != modVars.end();
}

bool doesProcModAny(const std::string& proc, std::shared_ptr<PkbRetriever> pkbRet) {
    std::unordered_set<std::string> modVars = getAllVarModByProc(proc, pkbRet);
    return modVars.size() > 0;
}

// Case: Modifies(1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::constWildcard() {
    std::shared_ptr<Value> v1 = std::static_pointer_cast<Value>(this->arg1);
    const std::string& arg1Val = v1->getVal();
    std::unordered_set<std::string> res = v1->isInt()
        ? getAllVarModByStmt(std::stoi(arg1Val), pkbRet)
        : getAllVarModByProc(arg1Val, pkbRet);
    return !res.empty()
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Modifies(1, "x")
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::constConst() {
    std::shared_ptr<Value> v1 = std::static_pointer_cast<Value>(this->arg1);
    const std::string& arg1Val = v1->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

    std::unordered_set<std::string> pkbRes = v1->isInt()
        ? getAllVarModByStmt(std::stoi(arg1Val), pkbRet)
        : getAllVarModByProc(arg1Val, pkbRet);
    return std::find(pkbRes.begin(), pkbRes.end(), arg2Val) != pkbRes.end()
        ? QpsTable::getDefaultOk()
        : QpsTable::getDefaultNoMatch();
}

// Case: Modifies(1, v1)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModStrat::constSyn() {
    std::shared_ptr<Value> v1 = std::static_pointer_cast<Value>(this->arg1);
    const std::string& arg1Val = v1->getVal();
    const std::string& arg2Name = std::static_pointer_cast<Synonym>(this->arg2)->getName();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ arg2Name });

    std::unordered_set<std::string> pkbRes = v1->isInt()
        ? getAllVarModByStmt(std::stoi(arg1Val), pkbRet)
        : getAllVarModByProc(arg1Val, pkbRet);
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

    // Account for cases of procedure or stmtref
    if (arg1Syn->matchesKeyword(Constants::PROCEDURE)) {
        std::unordered_set<std::string> arg1Procs = pkbRet->getAllProc();
        for (std::string proc : arg1Procs) {
            if (doesProcModAny(proc, pkbRet)) {
                resTable->addRow({ proc });
            }
        }
    }
    else {
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            std::unordered_set<std::string> pkbRes = getAllVarModByStmt(stmtNum, pkbRet);
            if (!pkbRes.empty()) {
                resTable->addRow({ std::to_string(stmtNum) });
            }
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

    // Account for procedures
    if (arg1Syn->matchesKeyword(Constants::PROCEDURE)) {
        std::unordered_set<std::string> arg1Procs = pkbRet->getAllProc();
        for (std::string proc : arg1Procs) {
            std::unordered_set<std::string> pkbRes = getAllVarModByProc(proc, pkbRet);
            if (std::find(pkbRes.begin(), pkbRes.end(), arg2Val) != pkbRes.end()) {
                resTable->addRow({ proc });
            }
        }
    }
    else {
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            std::unordered_set<std::string> pkbRes = getAllVarModByStmt(stmtNum, pkbRet);
            if (std::find(pkbRes.begin(), pkbRes.end(), arg2Val) != pkbRes.end()) {
                resTable->addRow({ std::to_string(stmtNum) });
            }
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

    // Account for procedures
    if (arg1Syn->matchesKeyword(Constants::PROCEDURE)) {
        std::unordered_set<std::string> arg1Procs = pkbRet->getAllProc();
        for (std::string proc : arg1Procs) {
            std::unordered_set<std::string> pkbRes = getAllVarModByProc(proc, pkbRet);
            for (const std::string& arg2Match : pkbRes) {
                resTable->addRow({ proc, arg2Match });
            }
        }
    }
    else {
        std::unordered_set<int> arg1Stmts = arg1Syn->matchesKeyword(Constants::STMT)
            ? Clause::getEveryStmt(pkbRet)
            : pkbRet->getAllStmt(arg1Syn->getKeyword());
        for (int stmtNum : arg1Stmts) {
            std::unordered_set<std::string> pkbRes = getAllVarModByStmt(stmtNum, pkbRet);
            for (const std::string& res : pkbRes) {
                resTable->addRow({ std::to_string(stmtNum), res });
            }
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
