#include "WithStrat.h"

// Constructor function for WithStrat
WithStrat::WithStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
    std::shared_ptr<Entity> arg2, std::shared_ptr<PkbRetriever> pkbRet)
    : ClauseStrat(clauseKeyword, arg1, arg2, pkbRet) {
}


std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> WithStrat::resolve() {
    return createReturnStrategy();
}

// Factory function for strategy used
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> WithStrat::createReturnStrategy() {
    if (this->arg1->isConstant() && this->arg2->isConstant()) return constConst();
    if (this->arg1->isConstant() && this->arg2->isSynonym()) return constSyn();
    if (this->arg1->isSynonym() && this->arg2->isConstant()) return synConst();
    if (this->arg1->isSynonym() && this->arg2->isSynonym()) return synSyn();

    return QpsTable::getDefaultSynErr();
}

// Case: with 1 = 2 
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> WithStrat::constConst() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();

    return arg1Val == arg2Val ? QpsTable::getDefaultOk() : QpsTable::getDefaultNoMatch();
}

// Case: with 2 = s2.stmt#
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> WithStrat::constSyn() {
    const std::string& arg1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);

    // Get all s2.stmt# results 
    std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> unfilteredS2Res = s2Syn->resolveAttrResult(pkbRet);
    
    // Filter and keep only results that match constant in arg1
    std::shared_ptr<QpsTable> constTable = QpsTable::create({ s2Syn->getNameWithAttr() });
    constTable->addRow({ arg1Val });
    std::shared_ptr<QpsTable> resTable = constTable->join(unfilteredS2Res.second);

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: with s1.stmt# = 12
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> WithStrat::synConst() {
    const std::string& arg2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    
    // Get all s1.stmt# results 
    std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> unfilteredS1Res = s1Syn->resolveAttrResult(pkbRet);

    // Filter and keep only results that match constant in arg2
    std::shared_ptr<QpsTable> constTable = QpsTable::create({ s1Syn->getNameWithAttr() });
    constTable->addRow({ arg2Val });
    std::shared_ptr<QpsTable> resTable = constTable->join(unfilteredS1Res.second);

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}

// Case: with s1.stmt# = s2.stmt#
std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> WithStrat::synSyn() {
    std::shared_ptr<Synonym> s1Syn = std::static_pointer_cast<Synonym>(this->arg1);
    std::shared_ptr<Synonym> s2Syn = std::static_pointer_cast<Synonym>(this->arg2);

    // Get all s1.stmt# and s2.stmt# results 
    std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> unfilteredS1Res = s1Syn->resolveAttrResult(pkbRet);
    std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> unfilteredS2Res = s2Syn->resolveAttrResult(pkbRet);

    std::shared_ptr<QpsTable> resTable = QpsTable::create({ s1Syn->getName(), s1Syn->getNameWithAttr(),
        s2Syn->getName(), s2Syn->getNameWithAttr() });

    // Join 2 tables on attrname col
    for (std::vector<std::string> s1Row : unfilteredS1Res.second->getData()) {
        for (std::vector<std::string> s2Row : unfilteredS2Res.second->getData()) {
            if (s1Row[1] == s2Row[1]) {
                resTable->addRow({ s1Row[0], s1Row[1], s2Row[0], s2Row[1] });
            }
        }
    }

    return QueryUtils::isNotEmpty(resTable->getData())
        ? std::make_pair(Constants::ClauseResult::OK, resTable)
        : std::make_pair(Constants::ClauseResult::NO_MATCH, resTable);
}
