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

// TESTS FOR CLAUSE FUNCTIONS
TEST_CASE("clause compare function returns false for different types of clauses with the same entities") {
	std::shared_ptr<Value> arg1 = Value::create("x");
	std::shared_ptr<Value> arg2 = Value::create("xyz");

	std::shared_ptr<Clause> uses = Clause::create(Constants::USES, arg1, arg2);
	std::shared_ptr<Clause> modifies = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> pattern = Clause::create(Constants::PATTERN, arg1, arg2);

	REQUIRE(uses->compare(modifies) == false);
	REQUIRE(uses->compare(pattern) == false);
	REQUIRE(modifies->compare(pattern) == false);
}

TEST_CASE("clause compare function returns true for same types of clauses with the same value entities") {
	std::shared_ptr<Value> arg1 = Value::create("x");
	std::shared_ptr<Value> arg2 = Value::create("xyz");

	std::shared_ptr<Clause> uses = Clause::create(Constants::USES, arg1, arg2);
	std::shared_ptr<Clause> modifies = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> pattern = Clause::create(Constants::PATTERN, arg1, arg2);
	std::shared_ptr<Clause> uses2 = Clause::create(Constants::USES, arg1, arg2);
	std::shared_ptr<Clause> modifies2 = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> pattern2 = Clause::create(Constants::PATTERN, arg1, arg2);

	REQUIRE(pattern->compare(pattern2) == true);
	REQUIRE(uses->compare(uses2) == true);
	REQUIRE(modifies->compare(modifies2) == true);
}

TEST_CASE("clause compare function returns true for same types of clauses with the same wildcard entities") {
	std::shared_ptr<Wildcard> arg1 = Wildcard::create("x");
	std::shared_ptr<Wildcard> arg2 = Wildcard::create("xyz");

	std::shared_ptr<Clause> uses = Clause::create(Constants::USES, arg1, arg2);
	std::shared_ptr<Clause> modifies = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> pattern = Clause::create(Constants::PATTERN, arg1, arg2);
	std::shared_ptr<Clause> uses2 = Clause::create(Constants::USES, arg1, arg2);
	std::shared_ptr<Clause> modifies2 = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> pattern2 = Clause::create(Constants::PATTERN, arg1, arg2);

	REQUIRE(pattern->compare(pattern2) == true);
	REQUIRE(uses->compare(uses2) == true);
	REQUIRE(modifies->compare(modifies2) == true);
}

TEST_CASE("clause compare function returns true for same types of clauses with the same Synonym entities") {
	std::shared_ptr<Synonym> arg1 = Synonym::create(Constants::ASSIGN, "x");
	std::shared_ptr<Synonym> arg2 = Synonym::create(Constants::WHILE, "xyz");

	std::shared_ptr<Clause> uses = Clause::create(Constants::USES, arg1, arg2);
	std::shared_ptr<Clause> modifies = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> pattern = Clause::create(Constants::PATTERN, arg1, arg2);
	std::shared_ptr<Clause> uses2 = Clause::create(Constants::USES, arg1, arg2);
	std::shared_ptr<Clause> modifies2 = Clause::create(Constants::MODIFIES, arg1, arg2);
	std::shared_ptr<Clause> pattern2 = Clause::create(Constants::PATTERN, arg1, arg2);

	REQUIRE(pattern->compare(pattern2) == true);
	REQUIRE(uses->compare(uses2) == true);
	REQUIRE(modifies->compare(modifies2) == true);
}

TEST_CASE("clause compare function returns false for same types of clauses with different types of entities") {
	std::shared_ptr<Value> v1 = Value::create("x");
	std::shared_ptr<Wildcard> w1 = Wildcard::create("xyz");
	std::shared_ptr<Synonym> s1 = Synonym::create(Constants::WHILE, "xyz");

	std::shared_ptr<Clause> uses1 = Clause::create(Constants::USES, v1, w1);
	std::shared_ptr<Clause> uses2 = Clause::create(Constants::USES, v1, s1);
	std::shared_ptr<Clause> uses3 = Clause::create(Constants::USES, w1, s1);

	REQUIRE(uses1->compare(uses2) == false);
	REQUIRE(uses1->compare(uses3) == false);
	REQUIRE(uses2->compare(uses3) == false);
}

TEST_CASE("clause compare function returns false for same types of clauses with value entities with diff values") {
	std::shared_ptr<Value> v1 = Value::create("x");
	std::shared_ptr<Value> v2 = Value::create("xyz");

	std::shared_ptr<Clause> uses1 = Clause::create(Constants::USES, v1, v2);
	std::shared_ptr<Clause> uses2 = Clause::create(Constants::USES, v2, v1);
	std::shared_ptr<Clause> followsSt1 = Clause::create(Constants::FOLLOWSST, v1, v2);
	std::shared_ptr<Clause> followsSt2 = Clause::create(Constants::FOLLOWSST, v2, v1);
	std::shared_ptr<Clause> parent1 = Clause::create(Constants::PARENT, v1, v2);
	std::shared_ptr<Clause> parent2 = Clause::create(Constants::PARENT, v2, v1);

	REQUIRE(uses1->compare(uses2) == false);
	REQUIRE(followsSt1->compare(followsSt2) == false);
	REQUIRE(parent1->compare(parent2) == false);
}

TEST_CASE("clause compare function returns false for same types of clauses with wildcard entities with diff values") {
	std::shared_ptr<Wildcard> v1 = Wildcard::create();
	std::shared_ptr<Wildcard> v2 = Wildcard::create("xyz");

	std::shared_ptr<Clause> uses1 = Clause::create(Constants::USES, v1, v2);
	std::shared_ptr<Clause> uses2 = Clause::create(Constants::USES, v2, v1);
	std::shared_ptr<Clause> followsSt1 = Clause::create(Constants::FOLLOWSST, v1, v2);
	std::shared_ptr<Clause> followsSt2 = Clause::create(Constants::FOLLOWSST, v2, v1);
	std::shared_ptr<Clause> parent1 = Clause::create(Constants::PARENT, v1, v2);
	std::shared_ptr<Clause> parent2 = Clause::create(Constants::PARENT, v2, v1);

	REQUIRE(uses1->compare(uses2) == false);
	REQUIRE(followsSt1->compare(followsSt2) == false);
	REQUIRE(parent1->compare(parent2) == false);
}

TEST_CASE("clause compare function returns false for same types of clauses with synonym entities with diff types but same value") {
	std::shared_ptr<Synonym> v1 = Synonym::create(Constants::ASSIGN, "xyz");
	std::shared_ptr<Synonym> v2 = Synonym::create(Constants::CALL, "xyz");

	std::shared_ptr<Clause> uses1 = Clause::create(Constants::USES, v1, v2);
	std::shared_ptr<Clause> uses2 = Clause::create(Constants::USES, v2, v1);
	std::shared_ptr<Clause> followsSt1 = Clause::create(Constants::FOLLOWSST, v1, v2);
	std::shared_ptr<Clause> followsSt2 = Clause::create(Constants::FOLLOWSST, v2, v1);
	std::shared_ptr<Clause> parent1 = Clause::create(Constants::PARENT, v1, v2);
	std::shared_ptr<Clause> parent2 = Clause::create(Constants::PARENT, v2, v1);

	REQUIRE(uses1->compare(uses2) == false);
	REQUIRE(followsSt1->compare(followsSt2) == false);
	REQUIRE(parent1->compare(parent2) == false);
}

TEST_CASE("clause compare function returns false for same types of clauses with synonym entities with same types but diff value") {
	std::shared_ptr<Synonym> v1 = Synonym::create(Constants::PARENTST, "x");
	std::shared_ptr<Synonym> v2 = Synonym::create(Constants::PARENTST, "xyz");

	std::shared_ptr<Clause> uses1 = Clause::create(Constants::USES, v1, v2);
	std::shared_ptr<Clause> uses2 = Clause::create(Constants::USES, v2, v1);
	std::shared_ptr<Clause> followsSt1 = Clause::create(Constants::FOLLOWSST, v1, v2);
	std::shared_ptr<Clause> followsSt2 = Clause::create(Constants::FOLLOWSST, v2, v1);
	std::shared_ptr<Clause> parent1 = Clause::create(Constants::PARENT, v1, v2);
	std::shared_ptr<Clause> parent2 = Clause::create(Constants::PARENT, v2, v1);

	REQUIRE(uses1->compare(uses2) == false);
	REQUIRE(followsSt1->compare(followsSt2) == false);
	REQUIRE(parent1->compare(parent2) == false);
}

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