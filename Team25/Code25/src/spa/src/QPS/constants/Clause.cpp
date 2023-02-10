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
Constants::ClauseResult Clause::resolve() {
    std::cout << "resolve clause" << std::endl;
    return Constants::ClauseResult::SEM_ERR;
}

bool Clause::isPatternClause() {
    return false;
}

Constants::ClauseResult UsesClause::resolve() {
    std::cout << "resolve uses clause" << std::endl;

    // Guard clause: First arg of Uses cannot be a wildcard
    if (this->arg1->isWildcard()) {
        return Constants::ClauseResult::SEM_ERR;
    }

    // If neither args are synonyms, just check if clause returns a result
    if (this->arg1->isConstant()) {
        // Return syntax error result if arg1 is not a integer constant
        // 
        // Call pkb getAllModStmt if arg2 is wildcard

        // Check if these 2 args are a key-value pair in pkb if arg2 is constant, or result err if arg2 not string constant
    }

    // If at least one arg contains a synonym, resolve the answer and store it in the synonym
    return Constants::ClauseResult::OK;
}

Constants::ClauseResult ModifiesClause::resolve() {
    std::cout << "resolve modifies clause" << std::endl;
    return Constants::ClauseResult::OK;
}

Constants::ClauseResult ParentClause::resolve() {
    std::cout << "resolve parent clause" << std::endl;
    return Constants::ClauseResult::OK;
}

Constants::ClauseResult ParentStClause::resolve() {
    std::cout << "resolve parent* clause" << std::endl;
    return Constants::ClauseResult::OK;
}

Constants::ClauseResult FollowsClause::resolve() {
    std::cout << "resolve follows clause" << std::endl;
    return Constants::ClauseResult::OK;
}

Constants::ClauseResult FollowsStClause::resolve() {
    std::cout << "resolve follows* clause" << std::endl;
    return Constants::ClauseResult::OK;
}

Constants::ClauseResult PatternClause::resolve() {
    std::cout << "resolve pattern clause" << std::endl;
    return Constants::ClauseResult::OK;
}

bool PatternClause::isPatternClause() {
    return true;
}