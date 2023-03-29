#include "QPS/constants/Clause.h"
#include "catch.hpp"


// Scenario for testing CallsStClause::resolve
SCENARIO("Mocking behavior of CallsStClause::resolve") {
	GIVEN("An instance of a PkbRetriever class") {
		VariableStore vs;
		ConstantStore cs;
		FollowsStore fs;
		ProcedureStore ps;
		StatementStore ss;
		PatternStore patts;
		FollowsStarStore fstars;
		ModifiesProcStore mprocs;
		ModifiesStore ms;
		ParentStarStore pStars;
		ParentStore parents;
		UsesProcStore uprocs;
		UsesStore uses;
		CallsStore calls;
		CallsStarStore cStars;
		PrintAttribute printA;
		ReadAttribute readA;
		CallAttribute callA;
		NextStore next;
		CFGStore cfg;
		ContainCallsStore concall;

		std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
		std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
		std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
		std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
		std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
		std::shared_ptr<PatternStore> pattsPointer = std::make_shared<PatternStore>(patts);
		std::shared_ptr<FollowsStarStore> fstarsPointer = std::make_shared<FollowsStarStore>(fstars);
		std::shared_ptr<ModifiesProcStore> mprocsPointer = std::make_shared<ModifiesProcStore>(mprocs);
		std::shared_ptr<ModifiesStore> msPointer = std::make_shared<ModifiesStore>(ms);
		std::shared_ptr<ParentStarStore> pStarsPointer = std::make_shared<ParentStarStore>(pStars);
		std::shared_ptr<ParentStore> parentsPointer = std::make_shared<ParentStore>(parents);
		std::shared_ptr<UsesProcStore> uprocsPointer = std::make_shared<UsesProcStore>(uprocs);
		std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);
		std::shared_ptr<CallsStore> callsPointer = std::make_shared<CallsStore>(calls);
		std::shared_ptr<CallsStarStore> cStarsPointer = std::make_shared<CallsStarStore>(cStars);
		std::shared_ptr<PrintAttribute> printAPointer = std::make_shared<PrintAttribute>(printA);
		std::shared_ptr<ReadAttribute> readAPointer = std::make_shared<ReadAttribute>(readA);
		std::shared_ptr<CallAttribute> callAPointer = std::make_shared<CallAttribute>(callA);
		std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);
		std::shared_ptr<CFGStore> cfgPointer = std::make_shared<CFGStore>(cfg);
		std::shared_ptr<ContainCallsStore> concallPointer = std::make_shared<ContainCallsStore>(concall);

		PkbRetriever pkbRetriever(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer,
			fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, 
			usesPointer, callsPointer, cStarsPointer, printAPointer, readAPointer, callAPointer, nextPointer, 
			cfgPointer, concallPointer);
		std::shared_ptr<PkbRetriever> pkbRet = std::make_shared<PkbRetriever>(pkbRetriever);

		WHEN("PkbRetriever are populated queries that return a non-empty result") {
			// Mock variables appearing in the SIMPLE program
			vsPointer->addVar("x");
			vsPointer->addVar("y");
			vsPointer->addVar("z");

			// Mock constants appearing in the SIMPLE program
			csPointer->addConst(1);

			// Mock procedures appearing in the SIMPLE program
			psPointer->addProc("main", 1);
			psPointer->addProc("factorial", 1);
			psPointer->addProc("beta", 1);
			psPointer->addProc("f3", 1);
			psPointer->addProc("f4", 1);

			// Mock statements appearing in the SIMPLE program
			ssPointer->addStmt(Constants::ASSIGN, 1);
			ssPointer->addStmt(Constants::WHILE, 2);
			ssPointer->addStmt(Constants::ASSIGN, 3);
			ssPointer->addStmt(Constants::ASSIGN, 4);
			ssPointer->addStmt(Constants::IF, 5);
			ssPointer->addStmt(Constants::ASSIGN, 6);
			ssPointer->addStmt(Constants::ASSIGN, 7);
			ssPointer->addStmt(Constants::PRINT, 8);
			ssPointer->addStmt(Constants::ASSIGN, 9);
			ssPointer->addStmt(Constants::WHILE, 10);
			ssPointer->addStmt(Constants::PRINT, 11);
			ssPointer->addStmt(Constants::READ, 12);
			ssPointer->addStmt(Constants::IF, 13);
			ssPointer->addStmt(Constants::ASSIGN, 14);
			ssPointer->addStmt(Constants::PRINT, 15);
			ssPointer->addStmt(Constants::READ, 16);

			// Mock callsSt relationship in SIMPLE program
			cStarsPointer->addCallsStar("main", "factorial");
			cStarsPointer->addCallsStar("main", "beta");
			cStarsPointer->addCallsStar("main", "f3");
			cStarsPointer->addCallsStar("factorial", "beta");
			cStarsPointer->addCallsStar("factorial", "f4");
			cStarsPointer->addCallsStar("beta", "f3");
			cStarsPointer->addCallsStar("f3", "f4");

			THEN("When CallsStClause resolves wrong syntax, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::SYN_ERR, QpsTable::create());

				std::shared_ptr<Value> wrongArg1 = Value::create("1");
				std::shared_ptr<Value> wrongArg2 = Value::create("2");
				std::shared_ptr<Synonym> stmtSynArg1 = Synonym::create(Constants::PROCEDURE, "s1");
				std::shared_ptr<Synonym> stmtSynArg2 = Synonym::create(Constants::PROCEDURE, "s2");

				std::shared_ptr<Clause> wrongClause1 = Clause::create(Constants::CALLSST, wrongArg1, stmtSynArg2);
				std::shared_ptr<Clause> wrongClause2 = Clause::create(Constants::CALLSST, stmtSynArg1, wrongArg2);

				REQUIRE(wrongClause1->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause1->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause2->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause2->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When CallsStClause resolves wrong semantics, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::SEM_ERR, QpsTable::create());

				std::shared_ptr<Synonym> wrongArg1 = Synonym::create(Constants::VARIABLE, "v1");
				std::shared_ptr<Synonym> wrongArg2 = Synonym::create(Constants::STMT, "c2");
				std::shared_ptr<Synonym> stmtSynArg1 = Synonym::create(Constants::PROCEDURE, "s1");
				std::shared_ptr<Synonym> stmtSynArg2 = Synonym::create(Constants::PROCEDURE, "s2");

				std::shared_ptr<Clause> wrongClause1 = Clause::create(Constants::CALLSST, wrongArg1, stmtSynArg2);
				std::shared_ptr<Clause> wrongClause2 = Clause::create(Constants::CALLSST, stmtSynArg1, wrongArg2);

				REQUIRE(wrongClause1->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause1->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause2->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause2->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When CallsStClause resolves case Calls*(_,_), it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::OK, QpsTable::create());

				std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, wcArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedClauseRes.second->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When CallsStClause resolves case Calls*(_,'f4'), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

				std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
				std::shared_ptr<Value> constArg2 = Value::create("f4");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, wcArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*(_,'main'), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

				std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
				std::shared_ptr<Value> constArg2 = Value::create("main");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, wcArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*(_,s2), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s2" });
				expectedTable->addRow({ "factorial" });
				expectedTable->addRow({ "beta" });
				expectedTable->addRow({ "f3" });
				expectedTable->addRow({ "f4" });

				std::shared_ptr<Wildcard> wcArg1 = Wildcard::create();
				std::shared_ptr<Synonym> synArg2 = Synonym::create(Constants::PROCEDURE, "s2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, wcArg1, synArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*('main',_), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

				std::shared_ptr<Value> constArg1 = Value::create("main");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, constArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*('f4',_), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

				std::shared_ptr<Value> constArg1 = Value::create("f4");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, constArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*('main', 'f3'), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

				std::shared_ptr<Value> constArg1 = Value::create("main");
				std::shared_ptr<Value> constArg2 = Value::create("f3");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*('main','f4'), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

				std::shared_ptr<Value> constArg1 = Value::create("main");
				std::shared_ptr<Value> constArg2 = Value::create("f4");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*('main' ,s2), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s2" });
				expectedTable->addRow({ "factorial" });
				expectedTable->addRow({ "beta" });
				expectedTable->addRow({ "f3" });

				std::shared_ptr<Value> constArg1 = Value::create("main");
				std::shared_ptr<Synonym> synArg2 = Synonym::create(Constants::PROCEDURE, "s2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, constArg1, synArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*('f4',s2), it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s2" });

				std::shared_ptr<Value> constArg1 = Value::create("f4");
				std::shared_ptr<Synonym> synArg2 = Synonym::create(Constants::PROCEDURE, "s2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, constArg1, synArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*(s1,_), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1" });
				expectedTable->addRow({ "main" });
				expectedTable->addRow({ "factorial" });
				expectedTable->addRow({ "f3" });
				expectedTable->addRow({ "beta" });

				std::shared_ptr<Synonym> synArg1 = Synonym::create(Constants::PROCEDURE, "s1");
				std::shared_ptr<Wildcard> wcArg2 = Wildcard::create();

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, synArg1, wcArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsClause resolves case Calls*(s1,'beta'), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1" });
				expectedTable->addRow({ "main" });
				expectedTable->addRow({ "factorial" });

				std::shared_ptr<Synonym> synArg1 = Synonym::create(Constants::PROCEDURE, "s1");
				std::shared_ptr<Value> constArg2 = Value::create("beta");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, synArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*(s1,'main'), it should return no match") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1" });

				std::shared_ptr<Synonym> synArg1 = Synonym::create(Constants::PROCEDURE, "s1");
				std::shared_ptr<Value> constArg2 = Value::create("main");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, synArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*(a1,a2), it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a1", "a2" });
				expectedTable->addRow({ "main", "factorial" });
				expectedTable->addRow({ "main", "beta" });
				expectedTable->addRow({ "main", "f3" });
				expectedTable->addRow({ "factorial", "beta" });
				expectedTable->addRow({ "factorial", "f4" });
				expectedTable->addRow({ "beta", "f3" });
				expectedTable->addRow({ "f3", "f4" });

				std::shared_ptr<Synonym> synArg1 = Synonym::create(Constants::PROCEDURE, "a1");
				std::shared_ptr<Synonym> synArg2 = Synonym::create(Constants::PROCEDURE, "a2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, synArg1, synArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When CallsStClause resolves case Calls*(s1,s1), it should return no match") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create();

				std::shared_ptr<Synonym> synArg1 = Synonym::create(Constants::PROCEDURE, "s1");
				std::shared_ptr<Synonym> synArg2 = Synonym::create(Constants::PROCEDURE, "s1");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::CALLSST, synArg1, synArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}
		}
	}
}