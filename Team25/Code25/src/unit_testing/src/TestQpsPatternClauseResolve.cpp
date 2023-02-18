#pragma once

#include <memory>
#include "QPS/Constants/Clause.h"
#include "catch.hpp"


// Scenario for testing UsesClause::resolve
SCENARIO("Mocking behavior of PatternClause::resolve") {
	GIVEN("An instance of a PkbRetriever class and a target assign synonym") {
		VariableStore vs;
		ConstantStore cs;
		FollowsStore fs;
		ProcedureStore ps;
		StatementStore ss;
		PatternStore patts;

		std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
		std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
		std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
		std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
		std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
		std::shared_ptr<PatternStore> pattsPointer = std::make_shared<PatternStore>(patts);

		PkbRetriever pkbRetriever(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer);
		std::shared_ptr<PkbRetriever> pkbRet = std::make_shared<PkbRetriever>(pkbRetriever);

		std::shared_ptr<Synonym> a1 = Synonym::create(Constants::ASSIGN, "a1");
		std::shared_ptr<Synonym> wrongA1 = Synonym::create(Constants::VARIABLE, "x1");

		WHEN("PkbRetriever are populated queries that return a non-empty result") {
			// Mock variables appearing in the SIMPLE program
			vsPointer->add("x");
			vsPointer->add("y");
			vsPointer->add("z");

			// Mock constants appearing in the SIMPLE program
			csPointer->add(1);

			// Mock procedures appearing in the SIMPLE program
			psPointer->add("main");

			// Mock statements appearing in the SIMPLE program
			ssPointer->addStmt(Constants::ASSIGN, 1);
			ssPointer->addStmt(Constants::ASSIGN, 2);
			ssPointer->addStmt(Constants::PRINT, 3);
			ssPointer->addStmt(Constants::READ, 4);

			// Mock Patterns in SIMPLE program
			pattsPointer->addAssignLhs("z", 1);
			pattsPointer->addAssignLhs("x", 2);
			pattsPointer->addAssignRhs(1, "x+y+1");
			pattsPointer->addAssignRhs(2, "z+x");

			THEN("When PatternClause resolves wrong syntax, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::SYN_ERR, QpsTable::create());

				std::shared_ptr<Value> wrongArg1 = Value::create("1");
				std::shared_ptr<Value> wrongArg2 = Value::create("1");
				std::shared_ptr<Synonym> wrongSynArg2 = Synonym::create(Constants::VARIABLE, "v2");

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "v1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create("1");

				std::shared_ptr<Clause> wrongClause1 = Clause::create(Constants::PATTERN, wrongArg1, wcArg2);
				std::shared_ptr<Clause> wrongClause2 = Clause::create(Constants::PATTERN, varSynArg1, wrongArg2);
				std::shared_ptr<Clause> wrongClause3 = Clause::create(Constants::PATTERN, varSynArg1, wrongSynArg2);
				std::shared_ptr<PatternClause> wrongClause1Ptn = std::static_pointer_cast<PatternClause>(wrongClause1);
				std::shared_ptr<PatternClause> wrongClause2Ptn = std::static_pointer_cast<PatternClause>(wrongClause2);
				std::shared_ptr<PatternClause> wrongClause3Ptn = std::static_pointer_cast<PatternClause>(wrongClause3);

				REQUIRE(wrongClause1Ptn->resolve(pkbRet, a1).first == expectedClauseRes.first);
				REQUIRE(wrongClause1Ptn->resolve(pkbRet, a1).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause2Ptn->resolve(pkbRet, a1).first == expectedClauseRes.first);
				REQUIRE(wrongClause2Ptn->resolve(pkbRet, a1).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause3Ptn->resolve(pkbRet, a1).first == expectedClauseRes.first);
				REQUIRE(wrongClause3Ptn->resolve(pkbRet, a1).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When PatternClause resolves wrong semantics, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::SEM_ERR, QpsTable::create());

				std::shared_ptr<Synonym> wrongArg1 = Synonym::create(Constants::CONSTANT, "v1");
				std::shared_ptr<Synonym> wrongTargetAsg = Synonym::create(Constants::STMT, "s1");

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "v1");
				std::shared_ptr<Value> constArg2 = Value::create("x");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> wrongClause1 = Clause::create(Constants::PATTERN, wrongArg1, wcArg2);
				std::shared_ptr<Clause> validClause2 = Clause::create(Constants::PATTERN, varSynArg1, wcArg2);
				std::shared_ptr<PatternClause> wrongClause1Ptn = std::static_pointer_cast<PatternClause>(wrongClause1);
				std::shared_ptr<PatternClause> validClause2Ptn = std::static_pointer_cast<PatternClause>(validClause2);

				REQUIRE(wrongClause1Ptn->resolve(pkbRet, a1).first == expectedClauseRes.first);
				REQUIRE(wrongClause1Ptn->resolve(pkbRet, a1).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(validClause2Ptn->resolve(pkbRet, wrongTargetAsg).first == expectedClauseRes.first);
				REQUIRE(validClause2Ptn->resolve(pkbRet, wrongTargetAsg).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When PatternClause resolves case pattern a1 (_, _), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName() });
				expectedTable->addRow({ "1" });
				expectedTable->addRow({ "2" });

				std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, wcArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 (_, _'y'_), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName() });
				expectedTable->addRow({ "1" });

				std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create("y");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, wcArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 (_, _'w'_), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName() });

				std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create("w");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, wcArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 ('x', _), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName() });
				expectedTable->addRow({ "2" });

				std::shared_ptr<Value> constArg1 = Value::create("x");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, constArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 ('w', _), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName() });

				std::shared_ptr<Value> constArg1 = Value::create("w");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, constArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 ('x', _'z'_), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName() });
				expectedTable->addRow({ "2" });

				std::shared_ptr<Value> constArg1 = Value::create("x");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create("z");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, constArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 ('x', _'w'_), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName() });

				std::shared_ptr<Value> constArg1 = Value::create("x");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create("w");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, constArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 (v1, _), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName(), "v1" });
				expectedTable->addRow({ "1", "z" });
				expectedTable->addRow({ "2", "x" });

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "v1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, varSynArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 (v1, _'x'_), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName(), "v1" });
				expectedTable->addRow({ "2", "x" });

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "v1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create("x");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, varSynArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}

			THEN("When PatternClause resolves case pattern a1 (v1, _'w'_), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ a1->getName(), "v1" });

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "v1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create("w");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::PATTERN, varSynArg1, wcArg2);
				std::shared_ptr<PatternClause> testClausePtn = std::static_pointer_cast<PatternClause>(testClause);

				REQUIRE(testClausePtn->resolve(pkbRet, a1).first == expectedStatus);
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClausePtn->resolve(pkbRet, a1).second->getData() == expectedTable->getData());
			}
		}
	}
}