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
void Clause::resolve() {
    std::cout << "resolve clause" << std::endl;
    return;
}

void UsesClause::resolve() {
    std::cout << "resolve uses clause" << std::endl;
    return;
}

void ModifiesClause::resolve() {
    std::cout << "resolve modifies clause" << std::endl;
    return;
}

void ParentClause::resolve() {
    std::cout << "resolve parent clause" << std::endl;
    return;
}

void ParentStClause::resolve() {
    std::cout << "resolve parent* clause" << std::endl;
    return;
}

void FollowsClause::resolve() {
    std::cout << "resolve follows clause" << std::endl;
    return;
}

void FollowsStClause::resolve() {
    std::cout << "resolve follows* clause" << std::endl;
    return;
}

void PatternClause::resolve() {
    std::cout << "resolve pattern clause" << std::endl;
    return;
}