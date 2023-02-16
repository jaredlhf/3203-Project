#include <iostream>
#include "Clause.h"

// Constructor function for Clause
Clause::Clause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) {
	this->arg1 = arg1;
	this->arg2 = arg2;
}

// Clause functions
std::string Clause::getKeyword() {
    return this->keyword;
}

bool Clause::compare(std::shared_ptr<Clause> other) {
    if (this->getKeyword() != other->getKeyword()) {
        return false;
    }

    bool isSameArg1 = false;
    bool isSameArg2 = false;

    if (this->arg1->isConstant() && other->arg1->isConstant()) {
        isSameArg1 = std::static_pointer_cast<Value>(this->arg1)->compare(std::static_pointer_cast<Value>(other->arg1));
    }
    else if (this->arg1->isWildcard() && other->arg1->isWildcard()) {
        isSameArg1 = std::static_pointer_cast<Wildcard>(this->arg1)->compare(std::static_pointer_cast<Wildcard>(other->arg1));
    }
    else if (this->arg1->isSynonym() && other->arg1->isSynonym()) {
        isSameArg1 = std::static_pointer_cast<Synonym>(this->arg1)->compare(std::static_pointer_cast<Synonym>(other->arg1));
    }

    if (this->arg2->isConstant() && other->arg2->isConstant()) {
        isSameArg2 = std::static_pointer_cast<Value>(this->arg2)->compare(std::static_pointer_cast<Value>(other->arg2));
    }
    else if (this->arg2->isWildcard() && other->arg2->isWildcard()) {
        isSameArg2 = std::static_pointer_cast<Wildcard>(this->arg2)->compare(std::static_pointer_cast<Wildcard>(other->arg2));
    }
    else if (this->arg2->isSynonym() && other->arg2->isSynonym()) {
        isSameArg2 = std::static_pointer_cast<Synonym>(this->arg2)->compare(std::static_pointer_cast<Synonym>(other->arg2));
    }

    return isSameArg1 && isSameArg2;
}

// Factory function for Clause
std::shared_ptr<Clause> Clause::create(const std::string clauseType, std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) {
    std::shared_ptr<Clause> res;

    if (clauseType == Constants::USES) res = std::make_shared<UsesClause>(UsesClause(arg1, arg2));
    if (clauseType == Constants::MODIFIES) res = std::make_shared<ModifiesClause>(ModifiesClause(arg1, arg2));
    if (clauseType == Constants::PARENT) res = std::make_shared<ParentClause>(ParentClause(arg1, arg2));
    if (clauseType == Constants::PARENTST) res = std::make_shared<ParentStClause>(ParentStClause(arg1, arg2));
    if (clauseType == Constants::FOLLOWS) res = std::make_shared<FollowsClause>(FollowsClause(arg1, arg2));
    if (clauseType == Constants::FOLLOWSST) res = std::make_shared<FollowsStClause>(FollowsStClause(arg1, arg2));
    if (clauseType == Constants::PATTERN) res = std::make_shared<PatternClause>(PatternClause(arg1, arg2));

    return res;
}

// Overriden clause constructor functions
UsesClause::UsesClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::USES;
}

ModifiesClause::ModifiesClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::MODIFIES;
}

ParentClause::ParentClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::PARENT;
}

ParentStClause::ParentStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::PARENTST;
}

FollowsClause::FollowsClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::FOLLOWS;
}

FollowsStClause::FollowsStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::FOLLOWSST;
}

PatternClause::PatternClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::PATTERN;
}

// Overriden clause functions
bool Clause::isWrongArgs() {
    return true;
}

bool Clause::isSemInvalid() {
    return true;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> Clause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    std::cout << "resolve clause" << std::endl;
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();
}

bool Clause::isPatternClause() {
    return false;
}


// UsesClause overriden clause functions
/*
    For uses clauses, args is wrong if arg1 is not int, or arg2 is int
*/
bool UsesClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }
    return false;
}

/*
    For uses clauses, args is sem invalid if arg1 is not stmtsyn, or arg2 is not varsyn
*/
bool UsesClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isVariableSyn()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> UsesClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    std::cout << "resolve uses clause" << std::endl;
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();

    // Guard clause: First arg of Uses cannot be a wildcard
    if (this->arg1->isWildcard()) {
    }

    // If neither args are synonyms, just check if clause returns a result
    if (this->arg1->isConstant()) {
        // Return syntax error result if arg1 is not a integer constant
        if (!std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        }

        std::string v1Val = std::static_pointer_cast<Value>(this->arg1)->getVal();

        // Call pkb getAllUsesVal(v1Val) if arg2 is wildcard
        if (this->arg2->isWildcard()) {
            bool validWildcard = std::static_pointer_cast<Wildcard>(this->arg2)->isGenericWildcard();
        }

        if (this->arg2->isConstant()) {
            // Check if these 2 args are a key-value pair in pkb if arg2 is constant, or result err if arg2 not string constant
            std::shared_ptr<Value> v2 = std::static_pointer_cast<Value>(this->arg2);
            if (v2->isInt()) {
            }
            std::string v2Val = v2->getVal();
            /* If v2 constant is in pkb, call getUsesStmt(v2Val). If its an empty set, return NOMATCH, else OK*/
            // TODO replace with match logic | return Constants::ClauseResult::OK;
        }

        if (this->arg2->isSynonym()) {
            std::shared_ptr<Synonym> s2 = std::static_pointer_cast<Synonym>(this->arg2);
            if (!s2->matchesKeyword(Constants::VARIABLE)) {
            }

            /*TODO Call getUsesVal(v1Val) and store answers in s2*/
            // TODO return ok if matches found else no match
        }
    }

    // If at least one arg contains a synonym, resolve the answer and store it in the synonym
    std::shared_ptr<Synonym> s1 = std::static_pointer_cast<Synonym>(this->arg1);
    if (!s1->isStmtRef()) {
    }
    // If arg2 is wildcard, getAllUsesStmt and add to s1
    if (this->arg2->isWildcard()) {
        // TODO call getAllUsesStmt() and add all results to s1
    }

    if (this->arg2->isConstant()) {
        bool isIntConst = std::static_pointer_cast<Value>(this->arg2)->isInt();
        if (isIntConst) {
        }
        std::string v2Val = std::static_pointer_cast<Value>(this->arg2)->getVal();
        // TODO call getUsesStmt(v2Val) and add all results to s1
    }

    // Both arg1 and 2 are Synonyms, so query and store it in each of them
    std::shared_ptr<Synonym> s2 = std::static_pointer_cast<Synonym>(this->arg2);
    if (!s2->matchesKeyword(Constants::VARIABLE)) {
    }

    // TODO call getAllUsesStmt() and store in s1
    // TODO call getAllUsesVar() and store in s2
    // TODO return no match if no results match else ok
    return QpsTable::getDefaultNoMatch();
}


// Modifies overriden clause functions
/*
    For modifies clauses, args is wrong if arg1 is not int, or arg2 is int
*/
bool ModifiesClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For modifies clauses, args is sem invalid if arg1 is not stmtsyn, or arg2 is not varsyn
*/
bool ModifiesClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isVariableSyn()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModifiesClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    std::cout << "resolve modifies clause" << std::endl;
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();
}

// Parent overriden clause functions
/*
    For parent clauses, args is wrong both args are not int
*/
bool ParentClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For parent clauses, args is sem invalid if either syns is not stmtsyn
*/
bool ParentClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    std::cout << "resolve parent clause" << std::endl;
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();
}

// Follows overriden clause functions
/*
    For follows clauses, args is wrong both args are not int
*/
bool FollowsClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For follows clauses, args is sem invalid if either syns is not stmtsyn
*/
bool FollowsClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    std::cout << "resolve follows clause" << std::endl;
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();
}

// ParentSt overriden clause functions
/*
    For ParentSt clauses, args is wrong both args are not int
*/
bool ParentStClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For parentst clauses, args is sem invalid if either syns is not stmtsyn
*/
bool ParentStClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ParentStClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    std::cout << "resolve parent* clause" << std::endl;
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();
}

// FollowsSt overriden clause functions
/*
    For FollowsSt clauses, args is wrong both args are not int
*/
bool FollowsStClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For followsst clauses, args is sem invalid if either syns is not stmtsyn
*/
bool FollowsStClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> FollowsStClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    std::cout << "resolve follows* clause" << std::endl;
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();
}

// Pattern overriden clause functions
/*
    For Pattern clauses, args is wrong if arg1 is int const, or if arg2 is synonym or is int const
*/
bool PatternClause::isWrongArgs() {
    if (this->arg1->isConstant() && std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    if (this->arg2->isSynonym()) {
        return true;
    }

    return false;
}

/*
    For pattern clauses, args is sem invalid if arg1 is not variable syn
*/
bool PatternClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isVariableSyn()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> PatternClause::resolve(
    std::shared_ptr<PkbRetriever> pkbRet, std::shared_ptr<Synonym> patternSynonym) {
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    return QpsTable::getDefaultNoMatch();
}

bool PatternClause::isPatternClause() {
    return true;
}