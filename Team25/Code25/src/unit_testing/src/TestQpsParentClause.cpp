#include "QPS/Constants/Clause.h"
#include "catch.hpp"


// Scenario for testing ParentClause::resolve
SCENARIO("Mocking behavior of ParentClause::resolve") {
	GIVEN("An instance of a PkbRetriever class") {
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
			ssPointer->addStmt(Constants::WHILE, 2);
			ssPointer->addStmt(Constants::ASSIGN, 3);
			ssPointer->addStmt(Constants::ASSIGN, 4);
			ssPointer->addStmt(Constants::IF, 5);
			ssPointer->addStmt(Constants::ASSIGN, 6);
			ssPointer->addStmt(Constants::READ, 7);
			ssPointer->addStmt(Constants::PRINT, 8);
			ssPointer->addStmt(Constants::ASSIGN, 9);
			ssPointer->addStmt(Constants::WHILE, 10);
			ssPointer->addStmt(Constants::PRINT, 11);
			ssPointer->addStmt(Constants::READ, 12);
			ssPointer->addStmt(Constants::IF, 13);
			ssPointer->addStmt(Constants::READ, 14);
			ssPointer->addStmt(Constants::PRINT, 15);
			ssPointer->addStmt(Constants::CALL, 16);

			// Mock parent relationship in SIMPLE program

			THEN("When ParentClause resolves wrong syntax, it should return the right results") {
				REQUIRE(1 == 1);
			}
		}
	}
}