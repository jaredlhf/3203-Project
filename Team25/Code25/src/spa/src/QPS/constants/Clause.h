#pragma once

#include <string>
#include <memory>
#include "Constants.h"
#include "Entity.h"

class Clause {
protected:
	std::string keyword;
	std::shared_ptr<Entity> arg1;
	std::shared_ptr<Entity> arg2;
public:
	// Constructor functions
	Clause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);

	// Clause functions
	std::string getKeyword();

	// Functions to be overriden by subclasses of Clause
	virtual void resolve();

	// Factory method for Clause subclasses
	static std::shared_ptr<Clause> create(const std::string clauseType, std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
};

class UsesClause : public Clause {
public:
	UsesClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual void resolve() override;
};

class ModifiesClause : public Clause {
public:
	ModifiesClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual void resolve() override;
};

class ParentClause : public Clause {
public:
	ParentClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual void resolve() override;
};

class FollowsClause : public Clause {
public:
	FollowsClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual void resolve() override;
};

class ParentStClause : public Clause {
public:
	ParentStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual void resolve() override;
};

class FollowsStClause : public Clause {
public:
	FollowsStClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual void resolve() override;
};

class PatternClause : public Clause {
public:
	PatternClause(std::shared_ptr<Entity> arg1, std::shared_ptr<Entity> arg2);
	virtual void resolve() override;
};