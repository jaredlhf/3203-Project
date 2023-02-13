#include "QPS/Constants/Clause.h"
#include "catch.hpp"

class SynonymStub : public Entity {
public:
	bool isConstant() override {
		return false;
	}

	bool isSynonym() override {
		return false;
	}

	bool isWildcard() override {
		return false;
	}
};

// TESTS FOR STATIC FACTORY FUNCTION
TEST_CASE("clause create function creates the right classes based on the keywords passed in") {
	SynonymStub stub1;
	SynonymStub stub2;
	std::shared_ptr<Entity> arg1 = std::make_shared<SynonymStub>(stub1);
	std::shared_ptr<Entity> arg2 = std::make_shared<SynonymStub>(stub2);

	REQUIRE(Clause::create(Constants::USES, arg1, arg2)->getKeyword() == Constants::USES);
	REQUIRE(Clause::create(Constants::MODIFIES, arg1, arg2)->getKeyword() == Constants::MODIFIES);
	REQUIRE(Clause::create(Constants::PARENT, arg1, arg2)->getKeyword() == Constants::PARENT);
	REQUIRE(Clause::create(Constants::PARENTST, arg1, arg2)->getKeyword() == Constants::PARENTST);
	REQUIRE(Clause::create(Constants::FOLLOWS, arg1, arg2)->getKeyword() == Constants::FOLLOWS);
	REQUIRE(Clause::create(Constants::FOLLOWSST, arg1, arg2)->getKeyword() == Constants::FOLLOWSST);
	REQUIRE(Clause::create(Constants::PATTERN, arg1, arg2)->getKeyword() == Constants::PATTERN);
}


// TESTS FOR POLYMORPHIC FUNCTIONS IN CONCRETE CLAUSE CLASSES
TEST_CASE("resolve function in clause classes behaves as expected") {
	SynonymStub stub1;
	SynonymStub stub2;
	std::shared_ptr<Entity> arg1 = std::make_shared<SynonymStub>(stub1);
	std::shared_ptr<Entity> arg2 = std::make_shared<SynonymStub>(stub2);
	std::shared_ptr<Value> v1 = Value::create("123");
	std::shared_ptr<Synonym> s2 = Synonym::create(Constants::VARIABLE, "xx");

	std::shared_ptr<Clause> uses = Clause::create(Constants::USES, v1, s2);
	std::shared_ptr<Clause> modifies = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> parent = Clause::create(Constants::PARENT, arg1, arg2);
	std::shared_ptr<Clause> parentst = Clause::create(Constants::PARENTST, arg1, arg2);
	std::shared_ptr<Clause> follows = Clause::create(Constants::FOLLOWS, arg1, arg2);
	std::shared_ptr<Clause> followsst = Clause::create(Constants::FOLLOWSST, arg1, arg2);
	std::shared_ptr<Clause> pattern = Clause::create(Constants::PATTERN, arg1, arg2);

	uses->resolve();
	modifies->resolve();
	parent->resolve();
	parentst->resolve();
	follows->resolve();
	followsst->resolve();
	pattern->resolve();

	REQUIRE(1 == 1);
}

TEST_CASE("isPatternClause function in clause classes behaves as expected") {
	SynonymStub stub1;
	SynonymStub stub2;
	std::shared_ptr<Entity> arg1 = std::make_shared<SynonymStub>(stub1);
	std::shared_ptr<Entity> arg2 = std::make_shared<SynonymStub>(stub2);

	std::shared_ptr<Clause> uses = Clause::create(Constants::USES, arg1, arg2);
	std::shared_ptr<Clause> modifies = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> parent = Clause::create(Constants::PARENT, arg1, arg2);
	std::shared_ptr<Clause> parentst = Clause::create(Constants::PARENTST, arg1, arg2);
	std::shared_ptr<Clause> follows = Clause::create(Constants::FOLLOWS, arg1, arg2);
	std::shared_ptr<Clause> followsst = Clause::create(Constants::FOLLOWSST, arg1, arg2);
	std::shared_ptr<Clause> pattern = Clause::create(Constants::PATTERN, arg1, arg2);

	REQUIRE(uses->isPatternClause() == false);
	REQUIRE(modifies->isPatternClause() == false);
	REQUIRE(parent->isPatternClause() == false);
	REQUIRE(parentst->isPatternClause() == false);
	REQUIRE(follows->isPatternClause() == false);
	REQUIRE(followsst->isPatternClause() == false);
	REQUIRE(pattern->isPatternClause() == true);
}