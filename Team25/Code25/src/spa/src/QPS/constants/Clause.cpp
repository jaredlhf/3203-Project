#include "Clause.h"


// Protected static functions
std::unordered_set<int> Clause::getEveryStmt(std::shared_ptr<PkbRetriever> pkbRet) {
    std::vector<std::string> stmtTypes({ Constants::ASSIGN, Constants::CALL, Constants::IF,
            Constants::WHILE, Constants::PRINT, Constants::READ });
    std::unordered_set<int> res;

    for (const std::string& stmtType : stmtTypes) {
        std::unordered_set<int> results = pkbRet->getAllStmt(stmtType);
        for (int ans : results) {
            res.insert(ans);
        }
    }

    return res;
}

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
    if (clauseType == Constants::CALLS) res = std::make_shared<CallsClause>(CallsClause(arg1, arg2));
    if (clauseType == Constants::CALLSST) res = std::make_shared<CallsStClause>(CallsStClause(arg1, arg2));
    if (clauseType == Constants::NEXT) res = std::make_shared<NextClause>(NextClause(arg1, arg2));
    if (clauseType == Constants::NEXTST) res = std::make_shared<NextStClause>(NextStClause(arg1, arg2));
    if (clauseType == Constants::WITH) res = std::make_shared<WithClause>(WithClause(arg1, arg2));

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

CallsClause::CallsClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::CALLS;
}

CallsStClause::CallsStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::CALLSST;
}

NextClause::NextClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::NEXT;
}

NextStClause::NextStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::NEXTST;
}

PatternClause::PatternClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::PATTERN;
}

WithClause::WithClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2) : Clause(arg1, arg2) {
    this->keyword = Constants::WITH;
}

// Overriden clause functions
bool Clause::isWrongArgs() {
    return true;
}

bool Clause::isSemInvalid() {
    return true;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> Clause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
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
    For uses clauses, args is wrong if arg2 is int
*/
bool UsesClause::isWrongArgs() {
    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }
    return false;
}

/*
    For uses clauses, args is sem invalid if arg1 is not stmtsyn or procedure, or arg2 is not varsyn
*/
bool UsesClause::isSemInvalid() {
    if (this->arg1->isSynonym() && 
        !(std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()
            || std::static_pointer_cast<Synonym>(this->arg1)->matchesKeyword(Constants::PROCEDURE))) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isVariableSyn()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> UsesClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err) 
    // OR arg1 is wildcard (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    if (this->arg1->isWildcard()) {
        return QpsTable::getDefaultSemErr();
    }
    
    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
}


// Modifies overriden clause functions
/*
    For modifies clauses, args is wrong if arg2 is int
*/
bool ModifiesClause::isWrongArgs() {
    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For modifies clauses, args is sem invalid if arg1 is not stmtsyn, or arg2 is not varsyn
*/
bool ModifiesClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !(std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()
        || std::static_pointer_cast<Synonym>(this->arg1)->matchesKeyword(Constants::PROCEDURE))) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isVariableSyn()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> ModifiesClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err) 
     // OR arg1 is wildcard (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    if (this->arg1->isWildcard()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
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
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
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
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
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
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
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
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
}

// Calls overriden clause functions
/*
    For calls clauses, args is wrong if either args are int
*/
bool CallsClause::isWrongArgs() {
    if (this->arg1->isConstant() && std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For calls clauses, args is sem invalid if either syns is not proc syn
*/
bool CallsClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->matchesKeyword(Constants::PROCEDURE)) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->matchesKeyword(Constants::PROCEDURE)) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
}

// Next overriden clause functions
/*
    For next clauses, args is wrong both args are not int
*/
bool NextClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For Next clauses, args is sem invalid if either syns is not stmtsyn
*/
bool NextClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
}

// CallsSt overriden clause functions
/*
    For CallsSt clauses, args is wrong if either args are int
*/
bool CallsStClause::isWrongArgs() {
    if (this->arg1->isConstant() && std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For callsst clauses, args is sem invalid if either syns is not proc syn
*/
bool CallsStClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->matchesKeyword(Constants::PROCEDURE)) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->matchesKeyword(Constants::PROCEDURE)) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> CallsStClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
}

// NextSt overriden clause functions
/*
    For NextSt clauses, args is wrong both args are not int
*/
bool NextStClause::isWrongArgs() {
    if (this->arg1->isConstant() && !std::static_pointer_cast<Value>(this->arg1)->isInt()) {
        return true;
    }

    if (this->arg2->isConstant() && !std::static_pointer_cast<Value>(this->arg2)->isInt()) {
        return true;
    }

    return false;
}

/*
    For nextst clauses, args is sem invalid if either syns is not stmtsyn
*/
bool NextStClause::isSemInvalid() {
    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->isStmtRef()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->isStmtRef()) {
        return true;
    }

    return false;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> NextStClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
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
    // GUARD CLAUSES: Return if either wrongs args (syntax err) or wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid() || !patternSynonym->matchesKeyword(Constants::ASSIGN)) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet, patternSynonym)->resolve();
}

bool PatternClause::isPatternClause() {
    return true;
}

// With clause overriden clause functions
/*
    For With clauses, args is wrong if either is a wildcard, or either doesnt have attrName
*/
bool WithClause::isWrongArgs() {
    if (this->arg1->isWildcard() || this->arg2->isWildcard()) {
        return true;
    }

    if (this->arg1->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg1)->hasAttrName()) {
        return true;
    }

    if (this->arg2->isSynonym() && !std::static_pointer_cast<Synonym>(this->arg2)->hasAttrName()) {
        return true;
    }

    return false;
}

/*
    For with clauses, semantics are incorrect if types are not both int or both string
*/
bool WithClause::isSemInvalid() {
    bool isArg1Int = false;
    bool isArg2Int = false;

    if (this->arg1->isConstant()) {
        isArg1Int = std::static_pointer_cast<Value>(this->arg1)->isInt();
    }

    if (this->arg2->isConstant()) {
        isArg2Int = std::static_pointer_cast<Value>(this->arg2)->isInt();
    }

    if (this->arg1->isSynonym()) {
        std::shared_ptr<Synonym> syn1 = std::static_pointer_cast<Synonym>(this->arg1);
        if (!AttrUtils::hasValidAttr(syn1, syn1->getAttrName())) {
            return true;
        }
        isArg1Int = Constants::isAttrNameInt(syn1->getAttrName());
    }

    if (this->arg2->isSynonym()) {
        std::shared_ptr<Synonym> syn2 = std::static_pointer_cast<Synonym>(this->arg2);
        if (!AttrUtils::hasValidAttr(syn2, syn2->getAttrName())) {
            return true;
        }
        isArg2Int = Constants::isAttrNameInt(syn2->getAttrName());
    }

    return isArg1Int != isArg2Int;
}

std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> WithClause::resolve(std::shared_ptr<PkbRetriever> pkbRet) {
    // GUARD CLAUSES: Return if either wrongs args (syntax err) OR wrong type of args (semantic err)
    if (this->isWrongArgs()) {
        return QpsTable::getDefaultSynErr();
    }

    if (this->isSemInvalid()) {
        return QpsTable::getDefaultSemErr();
    }

    return ClauseStrat::create(this->getKeyword(), this->arg1, this->arg2, pkbRet)->resolve();
}
