#include "PatternStrat.h"

// Constructor function for Strat
PatternStrat::PatternStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet, std::shared_ptr<Synonym> pairedSyn)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
    this->pairedSyn = pairedSyn;
    this->synKeyword = pairedSyn->getKeyword();

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
    // Case for assign
    if (this->synKeyword == Constants::ASSIGN) {
        // Case if both are wildcards
        if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
            std::shared_ptr<Wildcard> wcArg2 = std::static_pointer_cast<Wildcard>(this->arg2);
            if (wcArg2->isGenericWildcard()) {
                return wildcardWildcard();
            }
            else {
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
            }
            else {
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
            }
            else {
                return synSoftwildcard();
            }
        }

        // Case if arg 1 is a synonym and arg 2 is a constant
        if (this->arg1->isSynonym() && this->arg2->isConstant()) {
            return synConst();
        }
    }
    // Case for IF Patterns
    else if (this->synKeyword == Constants::IF) {
        // Case if arg 1 is wildcard and arg2 is wildcard
        if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
            return ifWildcardWildcard();
        }
        if (this->arg1->isConstant() && this->arg2->isWildcard()) {
            return ifConstWildcard();
        }
        if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
            return ifSynWildcard();
        }
    }
    // Case for WHILE Patterns
    else if (this->synKeyword == Constants::WHILE) {
        if (this->arg1->isWildcard() && this->arg2->isWildcard()) {
            return whileWildcardWildcard();
        }
        if (this->arg1->isConstant() && this->arg2->isWildcard()) {
            return whileConstWildcard();
        }
        if (this->arg1->isSynonym() && this->arg2->isWildcard()) {
            return whileSynWildcard();
        }
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
        if (StringUtils::createPostFixNotation(arg2Val) == StringUtils::createPostFixNotation(pkbPattern)) { //check if postfix notation for both expressions are the same
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

// Case: pattern a1 ("x", "y + x")
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::constConst() {  
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    std::unordered_set<int> pkbStmtMatches = pkbRet->getAssignLhs(arg1Val);

    for (int intVal : pkbStmtMatches) {
        const std::string& pkbPattern = pkbRet->getAssignRhs(intVal);
        if (StringUtils::createPostFixNotation(arg2Val) == StringUtils::createPostFixNotation(pkbPattern)) {
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

// Case: pattern a1 (v1, "x + y")
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::synConst() { 
    std::shared_ptr<Synonym> synArg1 = std::static_pointer_cast<Synonym>(this->arg1);
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();    
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName, synArg1->getName() });

    for (const std::string& a1SynMatch : synMatches) {
        const std::string& pkbPattern = pkbRet->getAssignRhs(std::stoi(a1SynMatch));
        if (StringUtils::createPostFixNotation(arg2Val) == StringUtils::createPostFixNotation(pkbPattern)) {
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

// Case: pattern if (_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::ifWildcardWildcard() {
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    for (const std::string& val : synMatches) {
        resTable->addRow({ val });
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern if ("x", _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::ifConstWildcard() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    std::unordered_set<int> pkbStmtMatches = pkbRet->getIfStatements(arg1Val);
    for (int intVal : pkbStmtMatches) {
        resTable->addRow({ std::to_string(intVal) });
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern if (v1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::ifSynWildcard() {
    std::shared_ptr<Synonym> synArg1 = std::static_pointer_cast<Synonym>(this->arg1);
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName, synArg1->getName() });
    for (const std::string& a1SynMatch : synMatches) {
        std::unordered_set<std::string> v1Match = pkbRet->getIfVars(std::stoi(a1SynMatch));
        for (const std::string& res : v1Match) {
            resTable->addRow({ a1SynMatch, res });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern while (_, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::whileWildcardWildcard() {
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    for (const std::string& val : synMatches) {
        resTable->addRow({ val });
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern while ("x", _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::whileConstWildcard() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName });
    std::unordered_set<int> pkbStmtMatches = pkbRet->getWhileStatements(arg1Val);
    for (int intVal : pkbStmtMatches) {
        resTable->addRow({ std::to_string(intVal) });
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: pattern while (v1, _)
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternStrat::whileSynWildcard() {
    std::shared_ptr<Synonym> synArg1 = std::static_pointer_cast<Synonym>(this->arg1);
    std::shared_ptr<QpsTable> resTable = QpsTable::create({ synName, synArg1->getName() });
    for (const std::string& a1SynMatch : synMatches) {
        std::unordered_set<std::string> v1Match = pkbRet->getWhileVars(std::stoi(a1SynMatch));
        for (const std::string& res : v1Match) {
            resTable->addRow({ a1SynMatch, res });
        }
    }

    return resTable->getData().size() > 0
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
