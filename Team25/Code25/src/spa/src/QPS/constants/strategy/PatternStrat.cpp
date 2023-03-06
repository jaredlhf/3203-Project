#include "PatternStrat.h"

// Constructor function for Strat
PatternStrat::PatternStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet, std::shared_ptr<Synonym> pairedSyn)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
    this->pairedSyn = pairedSyn;

    // Preprocessing: Get all matches for the assign/while/if synonym
    this->synName = pairedSyn->getName();
    for (int val : pkbRet->getAllStmt(pairedSyn->getKeyword())) {
        this->synMatches.push_back(std::to_string(val));
    }
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::resolve() {
    return createReturnStrategy();
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::createReturnStrategy() {
    // Case if both are wildcards
    if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
        std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
        if (wcArg2->isGenericWildcard()) {
            return wildcardWildcard();
        } else {
            return wildcardSoftwildcard();
        }
    }
    // Case if arg1 is wildcard and arg2 is constant
    if (this->arg1->isWildcard() && this->arg2->isConstant()) {
        return wildcardConst();
    }

    // Case if arg1 is a constant and arg2 is a wildcard
    if (this->arg1->isConstant() && this->arg2->isWildcard()) {
        std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
        if (wcArg2->isGenericWildcard()) {
            return constWildcard();
        } else {
            return constSoftwildcard();
        }
    }

    // Case if both arg1 and arg2 are constants
    if (this->arg1->isConstant() && this->arg2->isConstant()) {
        return constConst();
    }

    // Case if arg1 is a synonym and arg2 is a wildcard
    if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
        std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
        if (wcArg2->isGenericWildcard()) {
            return synWildcard();
        } else {
            return synSoftwildcard();
        }
    }

    // Case if arg 1 is a synonym and arg 2 is a constant
    if (this->arg1->isSynonym() && this->arg2->isConstant()) {
        return synConst();
    }

    return QpsTable::getDefaultSynErr();
}

// Case: pattern a1 (_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::wildcardWildcard() {
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    for (const std::string& val : synMatches) {
        resTable->addRow({ val });
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern a1 (_, _"x + y"_)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::wildcardSoftwildcard() {
    std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
    const std::string& wcPattern = wcArg2->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    for (const std::string& stNum : synMatches) {
        const std::string& pkbPattern = pkbRet->getAssignRhs(std::stoi(stNum));
        if (StringUtils::postFixInFullpostFix(StringUtils::createPostFixNotation(wcPattern), StringUtils::createPostFixNotation(pkbPattern))) { // can optimise
            resTable->addRow({ stNum });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern a1 (_, "x + y")
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::wildcardConst() {
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });

    for (const std::string& stNum : synMatches) {
        const std::string& pkbPattern = pkbRet->getAssignRhs(std::stoi(stNum));
        if (pkbPattern.compare(arg2Val) == 0) { // check with Yu Hang, but if the right hand side assign and the const value matches, you add to resTable
            resTable->addRow({ stNum });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}



// Case: pattern a1 ("x", _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::constWildcard() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    std::unordered_set<int> pkbStmtMatches = pkbRet->getAssignLhs(arg1Val);
    for (int intVal : pkbStmtMatches) {
        resTable->addRow({ std::to_string(intVal) });
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern a1 ("x", _"y + x"_)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::constSoftwildcard() {
    std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& wcPattern = wcArg2->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    std::unordered_set<int> pkbStmtMatches = pkbRet->getAssignLhs(arg1Val);
    for (int intVal : pkbStmtMatches) {
        const std::string& pkbPattern = pkbRet->getAssignRhs(intVal);
        if (StringUtils::postFixInFullpostFix(StringUtils::createPostFixNotation(wcPattern),StringUtils::createPostFixNotation(pkbPattern))) { // can optimise 
            resTable->addRow({ std::to_string(intVal) });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern a1 ("x", "y + x") TODO
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::constConst() {  
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    std::unordered_set<int> pkbStmtMatches = pkbRet->getAssignLhs(arg1Val);

    for (int intVal : pkbStmtMatches) {
        const std::string& pkbPattern = pkbRet->getAssignRhs(intVal);
        if (pkbPattern.compare(arg2Val) == 0) {
            resTable->addRow({ std::to_string(intVal) });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern a1 (v1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::synWildcard() {
    std::shared_ptr<Synonym> synArg1 = std::static_pointer_cast<Synonym>(this->arg1);
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName, synArg1->getName() });
    for (const std::string& a1SynMatch : synMatches) {
        std::unordered_set<std::string> v1Match = pkbRet->getModVar(std::stoi(a1SynMatch));
        for (const std::string& res : v1Match) {
            resTable->addRow({ a1SynMatch, res });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern a1 (v1, _"x + y"_)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::synSoftwildcard() {
    std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
    std::shared_ptr<Synonym> synArg1 = std::static_pointer_cast<Synonym>(this->arg1);
    const std::string& wcPattern = wcArg2->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName, synArg1->getName() });
    for (const std::string& a1SynMatch : synMatches) {
        const std::string& pkbPattern = pkbRet->getAssignRhs(std::stoi(a1SynMatch));
        if (StringUtils::postFixInFullpostFix(StringUtils::createPostFixNotation(wcPattern), StringUtils::createPostFixNotation(pkbPattern))) { // can optimise
            std::unordered_set<std::string> v1Match = pkbRet->getModVar(std::stoi(a1SynMatch));
            for (const std::string& res : v1Match) {
                resTable->addRow({ a1SynMatch, res });
            }
        }

    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern a1 (v1, "x + y") TODO
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::synConst() { 
    std::shared_ptr<Synonym> synArg1 = std::static_pointer_cast<Synonym>(this->arg1);
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();    
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName, synArg1->getName() });

    for (const std::string& a1SynMatch : synMatches) {
        const std::string& pkbPattern = pkbRet->getAssignRhs(std::stoi(a1SynMatch));
        if (pkbPattern.compare(arg2Val) == 0) {
            std::unordered_set<std::string> v1Match = pkbRet->getModVar(std::stoi(a1SynMatch));
            for (const std::string& res : v1Match) {
                resTable->addRow({ a1SynMatch, res });
            }
        }
    }


    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
