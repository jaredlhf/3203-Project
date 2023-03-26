#include "QPS/constants/Clause.h"
#include "catch.hpp"


// Scenario for testing WithClause::resolve
SCENARIO("Mocking behavior of WithClause::resolve") {
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
        PrintAttribute prAtt;
        ReadAttribute readAtt;
        CallAttribute callAtt;
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
        std::shared_ptr<PrintAttribute> printAttrStorage = std::make_shared<PrintAttribute>(prAtt);
        std::shared_ptr<ReadAttribute> readAttrStorage = std::make_shared<ReadAttribute>(readAtt);
        std::shared_ptr<CallAttribute> callAttrStorage = std::make_shared<CallAttribute>(callAtt);
		std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);
		std::shared_ptr<CFGStore> cfgPointer = std::make_shared<CFGStore>(cfg);
		std::shared_ptr<ContainCallsStore> concallPointer = std::make_shared<ContainCallsStore>(concall);

		PkbRetriever pkbRetriever(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer,
			fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cStarsPointer,
                                  printAttrStorage, readAttrStorage, callAttrStorage, nextPointer, cfgPointer, concallPointer);
		std::shared_ptr<PkbRetriever> pkbRet = std::make_shared<PkbRetriever>(pkbRetriever);

		WHEN("PkbRetriever are populated queries that return a non-empty result") {
			// Mock variables appearing in the SIMPLE program
			vsPointer->addVar("w");
			vsPointer->addVar("x");
			vsPointer->addVar("y");
			vsPointer->addVar("z");

			// Mock constants appearing in the SIMPLE program
			csPointer->addConst(1);
			csPointer->addConst(2);
			csPointer->addConst(3);
			csPointer->addConst(8);

			// Mock procedures appearing in the SIMPLE program
			psPointer->addProc("main");
			psPointer->addProc("factorial");
			psPointer->addProc("beta");
			psPointer->addProc("x");
			psPointer->addProc("z");

			// Mock statements appearing in the SIMPLE program
			ssPointer->addStmt(Constants::ASSIGN, 1);
			ssPointer->addStmt(Constants::WHILE, 2);
			ssPointer->addStmt(Constants::ASSIGN, 3);
			ssPointer->addStmt(Constants::IF, 4);
			ssPointer->addStmt(Constants::READ, 5);
			ssPointer->addStmt(Constants::PRINT, 6);
			ssPointer->addStmt(Constants::ASSIGN, 7);
			ssPointer->addStmt(Constants::WHILE, 8);
			ssPointer->addStmt(Constants::ASSIGN, 9);
			ssPointer->addStmt(Constants::CALL, 10);
			ssPointer->addStmt(Constants::IF, 11);
			ssPointer->addStmt(Constants::READ, 12);
			ssPointer->addStmt(Constants::PRINT, 13);
			ssPointer->addStmt(Constants::CALL, 14);
			ssPointer->addStmt(Constants::WHILE, 15);

			// Mock Read varNames appearing in SIMPLE program
			readAttrStorage->addAttr("w", 5);
			readAttrStorage->addAttr("x", 12);

			// Mock Print varNames appearing in SIMPLE program
			printAttrStorage->addAttr("y", 6);
			printAttrStorage->addAttr("z", 13);

			// Mock Call varNames appearing in SIMPLE program
			callAttrStorage->addAttr("factorial", 10);
			callAttrStorage->addAttr("beta", 14);

			THEN("When WithClause resolves wrong syntax, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::SYN_ERR, QpsTable::create());

				std::shared_ptr<Wildcard> wcArg = Wildcard::create();
				std::shared_ptr<Synonym> synWithoutAttr = Synonym::create(Constants::STMT, "s1");
				std::shared_ptr<Synonym> synWithAttr = Synonym::create(Constants::VARIABLE, "v2", Constants::VARNAME);

				std::shared_ptr<Clause> wrongClause1 = Clause::create(Constants::WITH, wcArg, synWithAttr);
				std::shared_ptr<Clause> wrongClause2 = Clause::create(Constants::WITH, synWithAttr, wcArg);
				std::shared_ptr<Clause> wrongClause3 = Clause::create(Constants::WITH, synWithoutAttr, synWithAttr);
				std::shared_ptr<Clause> wrongClause4 = Clause::create(Constants::WITH, synWithAttr, synWithoutAttr);

				REQUIRE(wrongClause1->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause1->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause2->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause2->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause3->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause3->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause4->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause4->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When WithClause resolves wrong semantics, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::SEM_ERR, QpsTable::create());

				std::shared_ptr<Value> intArg = Value::create("12");
				std::shared_ptr<Value> nonIntArg = Value::create("w3w");
				std::shared_ptr<Synonym> intSyn = Synonym::create(Constants::ASSIGN, "a2", Constants::STMTNUM);
				std::shared_ptr<Synonym> nonIntSyn = Synonym::create(Constants::VARIABLE, "a2", Constants::VARNAME);
				std::shared_ptr<Synonym> mismatchSyn1 = Synonym::create(Constants::CONSTANT, "a2", Constants::PROCNAME);
				std::shared_ptr<Synonym> mismatchSyn2 = Synonym::create(Constants::PROCEDURE, "a2", Constants::VALUE);


				std::shared_ptr<Clause> wrongClause1 = Clause::create(Constants::WITH, intArg, nonIntSyn);
				std::shared_ptr<Clause> wrongClause2 = Clause::create(Constants::WITH, intSyn, nonIntArg);
				std::shared_ptr<Clause> wrongClause3 = Clause::create(Constants::WITH, intArg, nonIntArg);
				std::shared_ptr<Clause> wrongClause4 = Clause::create(Constants::WITH, intSyn, nonIntSyn);
				std::shared_ptr<Clause> wrongClause5 = Clause::create(Constants::WITH, mismatchSyn1, nonIntSyn);
				std::shared_ptr<Clause> wrongClause6 = Clause::create(Constants::WITH, intSyn, mismatchSyn2);

				REQUIRE(wrongClause1->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause1->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause2->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause2->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause3->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause3->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause4->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause4->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause5->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause5->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
				REQUIRE(wrongClause6->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(wrongClause6->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When WithClause resolves case with 1 = 1, it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::OK, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("1");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, constArg1);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When WithClause resolves case with 1 = 2, it should return no matches") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::NO_MATCH, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("1");
				std::shared_ptr<Value> constArg2 = Value::create("2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When WithClause resolves case with 'x' = 'x', it should return the right results") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::OK, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("x");
				std::shared_ptr<Value> constArg2 = Value::create("x");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When WithClause resolves case with 'x' = 'xyz', it should return no matches") {
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> expectedClauseRes =
					std::make_pair(Constants::ClauseResult::NO_MATCH, QpsTable::create());

				std::shared_ptr<Value> constArg1 = Value::create("x");
				std::shared_ptr<Value> constArg2 = Value::create("xyz");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedClauseRes.first);
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedClauseRes.second->getData());
			}

			THEN("When WithClause resolves case with a.stmt# = 1, it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a.stmt#", "a"  });
				expectedTable->addRow({ "1", "1" });

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::ASSIGN, "a", Constants::STMTNUM);
				std::shared_ptr<Value> constArg2 = Value::create("1");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, varSynArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case with a.stmt# = 2, it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a.stmt#", "a" });

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::ASSIGN, "a", Constants::STMTNUM);
				std::shared_ptr<Value> constArg2 = Value::create("2");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, varSynArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case with v.varName = 'x', it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a.varName", "a" });
				expectedTable->addRow({ "x", "x" });

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "a", Constants::VARNAME);
				std::shared_ptr<Value> constArg2 = Value::create("x");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, varSynArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case v.varName = 't', it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a.varName", "a" });

				std::shared_ptr<Synonym> varSynArg1 = Synonym::create(Constants::VARIABLE, "a", Constants::VARNAME);
				std::shared_ptr<Value> constArg2 = Value::create("t");

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, varSynArg1, constArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case with 1 = a.stmt#, it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a.stmt#", "a" });
				expectedTable->addRow({ "1", "1" });

				std::shared_ptr<Value> constArg1 = Value::create("1");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::ASSIGN, "a", Constants::STMTNUM);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case with 2 = a.stmt#, it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a.stmt#", "a" });

				std::shared_ptr<Value> constArg1 = Value::create("2");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::ASSIGN, "a", Constants::STMTNUM);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case with 'x' = v.varName, it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a.varName", "a" });
				expectedTable->addRow({ "x", "x" });

				std::shared_ptr<Value> constArg1 = Value::create("x");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::VARIABLE, "a", Constants::VARNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case 't' = v.varName, it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "a.varName", "a" });

				std::shared_ptr<Value> constArg1 = Value::create("t");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::VARIABLE, "a", Constants::VARNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case w.stmt# = c.value, it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "w", "w.stmt#", "c", "c.value" });
				expectedTable->addRow({ "2", "2", "2", "2" });
				expectedTable->addRow({ "8", "8", "8", "8" });


				std::shared_ptr<Synonym> stmtSynArg1 = Synonym::create(Constants::WHILE, "w", Constants::STMTNUM);
				std::shared_ptr<Synonym> constSynArg2 = Synonym::create(Constants::CONSTANT, "c", Constants::VALUE);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, stmtSynArg1, constSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case p.procName = v.varName, it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "p", "p.procName", "v", "v.varName" });
				expectedTable->addRow({ "x", "x", "x", "x" });
				expectedTable->addRow({ "z", "z", "z", "z" });


				std::shared_ptr<Synonym> synArg1 = Synonym::create(Constants::PROCEDURE, "p", Constants::PROCNAME);
				std::shared_ptr<Synonym> synArg2 = Synonym::create(Constants::VARIABLE, "v", Constants::VARNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, synArg1, synArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case with 'x' = read.varName, it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "r.varName", "r" });
				expectedTable->addRow({ "x", "12" });

				std::shared_ptr<Value> constArg1 = Value::create("x");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::READ, "r", Constants::VARNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case 'z' = read.varName, it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "r.varName", "r" });

				std::shared_ptr<Value> constArg1 = Value::create("z");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::READ, "r", Constants::VARNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case with 'y' = print.varName, it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "p.varName", "p" });
				expectedTable->addRow({ "y", "6" });

				std::shared_ptr<Value> constArg1 = Value::create("y");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::PRINT, "p", Constants::VARNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case 'w' = print.varName, it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "p.varName", "p" });

				std::shared_ptr<Value> constArg1 = Value::create("w");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::PRINT, "p", Constants::VARNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case with 'factorial' = call.procName, it should return the right results") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "c.procName", "c" });
				expectedTable->addRow({ "factorial", "10" });

				std::shared_ptr<Value> constArg1 = Value::create("factorial");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::CALL, "c", Constants::PROCNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When WithClause resolves case 'main' = c.procName, it should return no matches") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::NO_MATCH;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "c.procName", "c" });

				std::shared_ptr<Value> constArg1 = Value::create("main");
				std::shared_ptr<Synonym> varSynArg2 = Synonym::create(Constants::CALL , "c", Constants::PROCNAME);

				std::shared_ptr<Clause> testClause = Clause::create(Constants::WITH, constArg1, varSynArg2);

				REQUIRE(testClause->resolve(pkbRet).first == expectedStatus);
				REQUIRE(testClause->resolve(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(testClause->resolve(pkbRet).second->getData() == expectedTable->getData());
			}
		}
	}
}