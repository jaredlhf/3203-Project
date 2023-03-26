#include "QPS/constants/Clause.h"
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
	REQUIRE(Clause::create(Constants::CALLS, arg1, arg2)->getKeyword() == Constants::CALLS);
	REQUIRE(Clause::create(Constants::CALLSST, arg1, arg2)->getKeyword() == Constants::CALLSST);
	REQUIRE(Clause::create(Constants::NEXT, arg1, arg2)->getKeyword() == Constants::NEXT);
	REQUIRE(Clause::create(Constants::NEXTST, arg1, arg2)->getKeyword() == Constants::NEXTST);
	REQUIRE(Clause::create(Constants::AFFECTS, arg1, arg2)->getKeyword() == Constants::AFFECTS);
	REQUIRE(Clause::create(Constants::AFFECTSST, arg1, arg2)->getKeyword() == Constants::AFFECTSST);
	REQUIRE(Clause::create(Constants::WITH, arg1, arg2)->getKeyword() == Constants::WITH);
}


// TESTS FOR POLYMORPHIC FUNCTIONS IN CONCRETE CLAUSE CLASSES
TEST_CASE("isWrongArgs function in UsesClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> varSyn = Synonym::create(Constants::VARIABLE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");
	std::shared_ptr<Synonym> procSyn = Synonym::create(Constants::PROCEDURE, "yy");

	std::shared_ptr<Clause> intArg2Clause = Clause::create(Constants::USES, intValue, intValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::USES, nonIntValue, intValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::USES, intValue, nonIntValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::USES, stmtSyn, varSyn);
	std::shared_ptr<Clause> validProcSynClause = Clause::create(Constants::USES, procSyn, varSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::USES, stmtSyn, nonIntValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::USES, intValue, varSyn);

	REQUIRE(intArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
	REQUIRE(validProcSynClause->isWrongArgs() == false);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in UsesClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> varSyn = Synonym::create(Constants::VARIABLE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");
	std::shared_ptr<Synonym> procSyn = Synonym::create(Constants::PROCEDURE, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::USES, varSyn, varSyn);
	std::shared_ptr<Clause> nonVarArg2Clause = Clause::create(Constants::USES, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::USES, varSyn, stmtSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::USES, intValue, nonIntValue);
	std::shared_ptr<Clause> validProcSynClause = Clause::create(Constants::USES, procSyn, varSyn);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::USES, stmtSyn, varSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::USES, stmtSyn, nonIntValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::USES, intValue, varSyn);

	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonVarArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
	REQUIRE(validProcSynClause->isSemInvalid() == false);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in ModifiesClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> varSyn = Synonym::create(Constants::VARIABLE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> intArg2Clause = Clause::create(Constants::MODIFIES, intValue, intValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::MODIFIES, nonIntValue, intValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::MODIFIES, intValue, nonIntValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::MODIFIES, stmtSyn, varSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::MODIFIES, stmtSyn, nonIntValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::MODIFIES, intValue, varSyn);

	REQUIRE(intArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in ModifiesClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> varSyn = Synonym::create(Constants::VARIABLE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");
	std::shared_ptr<Synonym> procSyn = Synonym::create(Constants::PROCEDURE, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::MODIFIES, varSyn, varSyn);
	std::shared_ptr<Clause> nonVarArg2Clause = Clause::create(Constants::MODIFIES, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::MODIFIES, varSyn, stmtSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::MODIFIES, intValue, nonIntValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::MODIFIES, stmtSyn, varSyn);	
	std::shared_ptr<Clause> validProcSynClause = Clause::create(Constants::MODIFIES, procSyn, varSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::MODIFIES, stmtSyn, nonIntValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::MODIFIES, intValue, varSyn);

	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonVarArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
	REQUIRE(validProcSynClause->isSemInvalid() == false);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in ParentClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonIntArg1Clause = Clause::create(Constants::PARENT, nonIntValue, intValue);
	std::shared_ptr<Clause> nonIntArg2Clause = Clause::create(Constants::PARENT, intValue, nonIntValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::PARENT, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::PARENT, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::PARENT, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::PARENT, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::PARENT, intValue, stmtSyn);

	REQUIRE(nonIntArg1Clause->isWrongArgs() == true);
	REQUIRE(nonIntArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in ParentClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::PARENT, constSyn, stmtSyn);
	std::shared_ptr<Clause> nonStmtArg2Clause = Clause::create(Constants::PARENT, stmtSyn, constSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::PARENT, constSyn, constSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::PARENT, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::PARENT, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::PARENT, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::PARENT, intValue, stmtSyn);


	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonStmtArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in Follows class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonIntArg1Clause = Clause::create(Constants::FOLLOWS, nonIntValue, intValue);
	std::shared_ptr<Clause> nonIntArg2Clause = Clause::create(Constants::FOLLOWS, intValue, nonIntValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::PARENT, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::FOLLOWS, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::FOLLOWS, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::PARENT, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::PARENT, intValue, stmtSyn);

	REQUIRE(nonIntArg1Clause->isWrongArgs() == true);
	REQUIRE(nonIntArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in FollowsClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::FOLLOWS, constSyn, stmtSyn);
	std::shared_ptr<Clause> nonStmtArg2Clause = Clause::create(Constants::FOLLOWS, stmtSyn, constSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::FOLLOWS, constSyn, constSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::FOLLOWS, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::FOLLOWS, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::FOLLOWS, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::FOLLOWS, intValue, stmtSyn);


	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonStmtArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in ParentSt class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonIntArg1Clause = Clause::create(Constants::PARENTST, nonIntValue, intValue);
	std::shared_ptr<Clause> nonIntArg2Clause = Clause::create(Constants::PARENTST, intValue, nonIntValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::PARENTST, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::PARENTST, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::PARENTST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::PARENTST, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::PARENTST, intValue, stmtSyn);

	REQUIRE(nonIntArg1Clause->isWrongArgs() == true);
	REQUIRE(nonIntArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in ParentStClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::PARENTST, constSyn, stmtSyn);
	std::shared_ptr<Clause> nonStmtArg2Clause = Clause::create(Constants::PARENTST, stmtSyn, constSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::PARENTST, constSyn, constSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::PARENTST, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::PARENTST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::PARENTST, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::PARENTST, intValue, stmtSyn);


	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonStmtArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in FollowsSt class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonIntArg1Clause = Clause::create(Constants::FOLLOWSST, nonIntValue, intValue);
	std::shared_ptr<Clause> nonIntArg2Clause = Clause::create(Constants::FOLLOWSST, intValue, nonIntValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::FOLLOWSST, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::FOLLOWSST, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::FOLLOWSST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::FOLLOWSST, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::FOLLOWSST, intValue, stmtSyn);

	REQUIRE(nonIntArg1Clause->isWrongArgs() == true);
	REQUIRE(nonIntArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in FollowsStClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::FOLLOWSST, constSyn, stmtSyn);
	std::shared_ptr<Clause> nonStmtArg2Clause = Clause::create(Constants::FOLLOWSST, stmtSyn, constSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::FOLLOWSST, constSyn, constSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::FOLLOWSST, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::FOLLOWSST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::FOLLOWSST, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::FOLLOWSST, intValue, stmtSyn);


	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonStmtArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in CallsClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> procSyn = Synonym::create(Constants::PROCEDURE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::WHILE, "yy");

	std::shared_ptr<Clause> intArg1Clause = Clause::create(Constants::CALLS, intValue, nonIntValue);
	std::shared_ptr<Clause> intArg2Clause = Clause::create(Constants::CALLS, nonIntValue, intValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::CALLS, intValue, intValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::CALLS, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::CALLS, procSyn, procSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::CALLS, procSyn, nonIntValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::CALLS, nonIntValue, procSyn);

	REQUIRE(intArg1Clause->isWrongArgs() == true);
	REQUIRE(intArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in CallsClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> procSyn = Synonym::create(Constants::PROCEDURE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::READ, "yy");

	std::shared_ptr<Clause> nonProcArg1Clause = Clause::create(Constants::CALLS, stmtSyn, procSyn);
	std::shared_ptr<Clause> nonProcArg2Clause = Clause::create(Constants::CALLS, procSyn, stmtSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::CALLS, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::CALLS, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::CALLS, procSyn, procSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::CALLS, procSyn, nonIntValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::CALLS, nonIntValue, procSyn);


	REQUIRE(nonProcArg1Clause->isSemInvalid() == true);
	REQUIRE(nonProcArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in CallsStClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> procSyn = Synonym::create(Constants::PROCEDURE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::WHILE, "yy");

	std::shared_ptr<Clause> intArg1Clause = Clause::create(Constants::CALLSST, intValue, nonIntValue);
	std::shared_ptr<Clause> intArg2Clause = Clause::create(Constants::CALLSST, nonIntValue, intValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::CALLSST, intValue, intValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::CALLSST, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::CALLSST, procSyn, procSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::CALLSST, procSyn, nonIntValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::CALLSST, nonIntValue, procSyn);

	REQUIRE(intArg1Clause->isWrongArgs() == true);
	REQUIRE(intArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in CallsStClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> procSyn = Synonym::create(Constants::PROCEDURE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::READ, "yy");

	std::shared_ptr<Clause> nonProcArg1Clause = Clause::create(Constants::CALLSST, stmtSyn, procSyn);
	std::shared_ptr<Clause> nonProcArg2Clause = Clause::create(Constants::CALLSST, procSyn, stmtSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::CALLSST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::CALLSST, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::CALLSST, procSyn, procSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::CALLSST, procSyn, nonIntValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::CALLSST, nonIntValue, procSyn);


	REQUIRE(nonProcArg1Clause->isSemInvalid() == true);
	REQUIRE(nonProcArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in NextClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::PRINT, "yy");

	std::shared_ptr<Clause> nonIntArg1Clause = Clause::create(Constants::NEXT, nonIntValue, intValue);
	std::shared_ptr<Clause> nonIntArg2Clause = Clause::create(Constants::NEXT, intValue, nonIntValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::NEXT, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::NEXT, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::NEXT, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::NEXT, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::NEXT, intValue, stmtSyn);

	REQUIRE(nonIntArg1Clause->isWrongArgs() == true);
	REQUIRE(nonIntArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in NextClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::NEXT, constSyn, stmtSyn);
	std::shared_ptr<Clause> nonStmtArg2Clause = Clause::create(Constants::NEXT, stmtSyn, constSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::NEXT, constSyn, constSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::NEXT, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::NEXT, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::NEXT, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::NEXT, intValue, stmtSyn);


	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonStmtArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in NextStClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::PRINT, "yy");

	std::shared_ptr<Clause> nonIntArg1Clause = Clause::create(Constants::NEXTST, nonIntValue, intValue);
	std::shared_ptr<Clause> nonIntArg2Clause = Clause::create(Constants::NEXTST, intValue, nonIntValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::NEXTST, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::NEXTST, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::NEXTST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::NEXTST, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::NEXTST, intValue, stmtSyn);

	REQUIRE(nonIntArg1Clause->isWrongArgs() == true);
	REQUIRE(nonIntArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in NextStClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::NEXTST, constSyn, stmtSyn);
	std::shared_ptr<Clause> nonStmtArg2Clause = Clause::create(Constants::NEXTST, stmtSyn, constSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::NEXTST, constSyn, constSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::NEXTST, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::NEXTST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::NEXTST, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::NEXTST, intValue, stmtSyn);


	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonStmtArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in AffectsClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::PRINT, "yy");

	std::shared_ptr<Clause> nonIntArg1Clause = Clause::create(Constants::AFFECTS, nonIntValue, intValue);
	std::shared_ptr<Clause> nonIntArg2Clause = Clause::create(Constants::AFFECTS, intValue, nonIntValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::AFFECTS, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::AFFECTS, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::AFFECTS, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::AFFECTS, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::AFFECTS, intValue, stmtSyn);

	REQUIRE(nonIntArg1Clause->isWrongArgs() == true);
	REQUIRE(nonIntArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in AffectsClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::AFFECTS, constSyn, stmtSyn);
	std::shared_ptr<Clause> nonStmtArg2Clause = Clause::create(Constants::AFFECTS, stmtSyn, constSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::AFFECTS, constSyn, constSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::AFFECTS, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::AFFECTS, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::AFFECTS, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::AFFECTS, intValue, stmtSyn);


	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonStmtArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in AffectsStClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::PRINT, "yy");

	std::shared_ptr<Clause> nonIntArg1Clause = Clause::create(Constants::AFFECTSST, nonIntValue, intValue);
	std::shared_ptr<Clause> nonIntArg2Clause = Clause::create(Constants::AFFECTSST, intValue, nonIntValue);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::AFFECTSST, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::AFFECTSST, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::AFFECTSST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::AFFECTSST, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::AFFECTSST, intValue, stmtSyn);

	REQUIRE(nonIntArg1Clause->isWrongArgs() == true);
	REQUIRE(nonIntArg2Clause->isWrongArgs() == true);
	REQUIRE(bothInvalidClause->isWrongArgs() == true);
	REQUIRE(validMixed1Clause->isWrongArgs() == false);
	REQUIRE(validMixed2Clause->isWrongArgs() == false);
	REQUIRE(validConstClause->isWrongArgs() == false);
	REQUIRE(validSynClause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in AffectsStClause class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> constSyn = Synonym::create(Constants::CONSTANT, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonStmtArg1Clause = Clause::create(Constants::AFFECTSST, constSyn, stmtSyn);
	std::shared_ptr<Clause> nonStmtArg2Clause = Clause::create(Constants::AFFECTSST, stmtSyn, constSyn);
	std::shared_ptr<Clause> bothInvalidClause = Clause::create(Constants::AFFECTSST, constSyn, constSyn);
	std::shared_ptr<Clause> validConstClause = Clause::create(Constants::AFFECTSST, intValue, intValue);
	std::shared_ptr<Clause> validSynClause = Clause::create(Constants::AFFECTSST, stmtSyn, stmtSyn);
	std::shared_ptr<Clause> validMixed1Clause = Clause::create(Constants::AFFECTSST, stmtSyn, intValue);
	std::shared_ptr<Clause> validMixed2Clause = Clause::create(Constants::AFFECTSST, intValue, stmtSyn);


	REQUIRE(nonStmtArg1Clause->isSemInvalid() == true);
	REQUIRE(nonStmtArg2Clause->isSemInvalid() == true);
	REQUIRE(bothInvalidClause->isSemInvalid() == true);
	REQUIRE(validMixed1Clause->isSemInvalid() == false);
	REQUIRE(validMixed2Clause->isSemInvalid() == false);
	REQUIRE(validConstClause->isSemInvalid() == false);
	REQUIRE(validSynClause->isSemInvalid() == false);
}

TEST_CASE("isWrongArgs function in Pattern class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Wildcard> genericWildcard = Wildcard::create();
	std::shared_ptr<Wildcard> patternWildcard = Wildcard::create("x+y");
	std::shared_ptr<Synonym> varSyn = Synonym::create(Constants::VARIABLE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> intArg1Clause = Clause::create(Constants::PATTERN, intValue, patternWildcard);
	std::shared_ptr<Clause> intArg2Clause = Clause::create(Constants::PATTERN, varSyn, intValue);
	std::shared_ptr<Clause> synArg2Clause = Clause::create(Constants::PATTERN, nonIntValue, varSyn);
	std::shared_ptr<Clause> valid1Clause = Clause::create(Constants::PATTERN, nonIntValue, genericWildcard);
	std::shared_ptr<Clause> valid2Clause = Clause::create(Constants::PATTERN, genericWildcard, genericWildcard);
	std::shared_ptr<Clause> valid3Clause = Clause::create(Constants::PATTERN, varSyn, genericWildcard);
	std::shared_ptr<Clause> valid4Clause = Clause::create(Constants::PATTERN, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> valid5Clause = Clause::create(Constants::PATTERN, genericWildcard, nonIntValue);
	std::shared_ptr<Clause> valid6Clause = Clause::create(Constants::PATTERN, varSyn, nonIntValue);

	REQUIRE(intArg1Clause->isWrongArgs() == true);
	REQUIRE(intArg2Clause->isWrongArgs() == true);
	REQUIRE(synArg2Clause->isWrongArgs() == true);
	REQUIRE(valid1Clause->isWrongArgs() == false);
	REQUIRE(valid2Clause->isWrongArgs() == false);
	REQUIRE(valid3Clause->isWrongArgs() == false);
	REQUIRE(valid4Clause->isWrongArgs() == false);
	REQUIRE(valid5Clause->isWrongArgs() == false);
	REQUIRE(valid6Clause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in Pattern class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Wildcard> genericWildcard = Wildcard::create();
	std::shared_ptr<Wildcard> patternWildcard = Wildcard::create("x+y");
	std::shared_ptr<Synonym> varSyn = Synonym::create(Constants::VARIABLE, "xx");
	std::shared_ptr<Synonym> stmtSyn = Synonym::create(Constants::CALL, "yy");

	std::shared_ptr<Clause> nonVarArg1Clause = Clause::create(Constants::PATTERN, stmtSyn, patternWildcard);
	std::shared_ptr<Clause> valid1Clause = Clause::create(Constants::PATTERN, nonIntValue, genericWildcard);
	std::shared_ptr<Clause> valid2Clause = Clause::create(Constants::PATTERN, genericWildcard, genericWildcard);
	std::shared_ptr<Clause> valid3Clause = Clause::create(Constants::PATTERN, varSyn, genericWildcard);
	std::shared_ptr<Clause> valid4Clause = Clause::create(Constants::PATTERN, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> valid5Clause = Clause::create(Constants::PATTERN, genericWildcard, nonIntValue);
	std::shared_ptr<Clause> valid6Clause = Clause::create(Constants::PATTERN, varSyn, nonIntValue);

	REQUIRE(nonVarArg1Clause->isSemInvalid() == true);
	REQUIRE(valid1Clause->isSemInvalid() == false);
	REQUIRE(valid2Clause->isSemInvalid() == false);
	REQUIRE(valid3Clause->isSemInvalid() == false);
	REQUIRE(valid4Clause->isSemInvalid() == false);
	REQUIRE(valid5Clause->isSemInvalid() == false);
	REQUIRE(valid6Clause->isSemInvalid() == false);
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

TEST_CASE("isWrongArgs function in With class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Wildcard> genericWildcard = Wildcard::create();
	std::shared_ptr<Synonym> noAttrSyn = Synonym::create(Constants::VARIABLE, "xx");
	std::shared_ptr<Synonym> attrSyn = Synonym::create(Constants::CALL, "yy", Constants::VALUE);

	std::shared_ptr<Clause> wildcardArg1 = Clause::create(Constants::WITH, genericWildcard, intValue);
	std::shared_ptr<Clause> wildcardArg2 = Clause::create(Constants::WITH, intValue, genericWildcard);
	std::shared_ptr<Clause> noAttrArg1 = Clause::create(Constants::WITH, noAttrSyn, intValue);
	std::shared_ptr<Clause> noAttrArg2 = Clause::create(Constants::WITH, intValue, noAttrSyn);
	std::shared_ptr<Clause> valid2Clause = Clause::create(Constants::WITH, intValue, intValue);
	std::shared_ptr<Clause> valid3Clause = Clause::create(Constants::WITH, attrSyn, attrSyn);
	std::shared_ptr<Clause> valid4Clause = Clause::create(Constants::WITH, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> valid5Clause = Clause::create(Constants::WITH, attrSyn, intValue);
	std::shared_ptr<Clause> valid6Clause = Clause::create(Constants::WITH, intValue, attrSyn);

	REQUIRE(wildcardArg1->isWrongArgs() == true);
	REQUIRE(wildcardArg2->isWrongArgs() == true);
	REQUIRE(noAttrArg1->isWrongArgs() == true);
	REQUIRE(noAttrArg2->isWrongArgs() == true);
	REQUIRE(valid2Clause->isWrongArgs() == false);
	REQUIRE(valid3Clause->isWrongArgs() == false);
	REQUIRE(valid4Clause->isWrongArgs() == false);
	REQUIRE(valid5Clause->isWrongArgs() == false);
	REQUIRE(valid6Clause->isWrongArgs() == false);
}

TEST_CASE("isSemInvalid function in With class behaves as expected") {
	std::shared_ptr<Value> intValue = Value::create("123");
	std::shared_ptr<Value> nonIntValue = Value::create("12w");
	std::shared_ptr<Synonym> intAttrSyn1 = Synonym::create(Constants::STMT, "xx", Constants::STMTNUM);
	std::shared_ptr<Synonym> intAttrSyn2 = Synonym::create(Constants::CONSTANT, "yy", Constants::VALUE);
	std::shared_ptr<Synonym> nonIntAttrSyn1 = Synonym::create(Constants::PROCEDURE, "xx", Constants::PROCNAME);
	std::shared_ptr<Synonym> nonIntAttrSyn2 = Synonym::create(Constants::VARIABLE, "yy", Constants::VARNAME);

	std::shared_ptr<Clause> notMatchingValues1 = Clause::create(Constants::WITH, intValue, nonIntValue);
	std::shared_ptr<Clause> notMatchingValues2 = Clause::create(Constants::WITH, nonIntValue, intValue);
	std::shared_ptr<Clause> matchingValues1 = Clause::create(Constants::WITH, intValue, intValue);
	std::shared_ptr<Clause> matchingValues2 = Clause::create(Constants::WITH, nonIntValue, nonIntValue);
	std::shared_ptr<Clause> notMatchingSyn1 = Clause::create(Constants::WITH, intAttrSyn1, nonIntAttrSyn1);
	std::shared_ptr<Clause> notMatchingSyn2 = Clause::create(Constants::WITH, intAttrSyn2, nonIntAttrSyn2);
	std::shared_ptr<Clause> matchingSyn1 = Clause::create(Constants::WITH, intAttrSyn1, intAttrSyn2);
	std::shared_ptr<Clause> matchingSyn2 = Clause::create(Constants::WITH, nonIntAttrSyn2, nonIntAttrSyn1);
	std::shared_ptr<Clause> notMatchingMixed1 = Clause::create(Constants::WITH, intValue, nonIntAttrSyn1);
	std::shared_ptr<Clause> notMatchingMixed2 = Clause::create(Constants::WITH, intAttrSyn2, nonIntValue);
	std::shared_ptr<Clause> matchingMixed1 = Clause::create(Constants::WITH, intAttrSyn2, intValue);
	std::shared_ptr<Clause> matchingMixed2 = Clause::create(Constants::WITH, nonIntValue, nonIntAttrSyn1);


	REQUIRE(notMatchingValues1->isSemInvalid() == true);
	REQUIRE(notMatchingValues2->isSemInvalid() == true);
	REQUIRE(matchingValues1->isSemInvalid() == false);
	REQUIRE(matchingValues2->isSemInvalid() == false);
	REQUIRE(notMatchingSyn1->isSemInvalid() == true);
	REQUIRE(notMatchingSyn2->isSemInvalid() == true);
	REQUIRE(matchingSyn1->isSemInvalid() == false);
	REQUIRE(matchingSyn2->isSemInvalid() == false);
	REQUIRE(notMatchingMixed1->isSemInvalid() == true);
	REQUIRE(notMatchingMixed2->isSemInvalid() == true);
	REQUIRE(matchingMixed1->isSemInvalid() == false);
	REQUIRE(matchingMixed2->isSemInvalid() == false);
}
