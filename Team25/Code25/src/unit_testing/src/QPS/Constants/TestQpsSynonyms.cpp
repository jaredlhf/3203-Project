#include <string>
#include <unordered_set>
#include "QPS/Constants/Synonym.h"
#include "QPS/Constants/Constants.h"
#include "catch.hpp"

using namespace std;

// TESTS FOR ENTITY OVERRIDEN FUNCTIONS
TEST_CASE("Synonym classes return the right values for Entity parent class virtual functions") {
	CallSynonym cl("cll");
	ProcedureSynonym pr("cll");
	StmtSynonym st("cll");
	REQUIRE(cl.isSynonym() == true);
	REQUIRE(pr.isConstant() == false);
	REQUIRE(st.isWildcard() == false);
	REQUIRE(Synonym::create(Constants::ASSIGN, "a")->isSynonym() == true);
	REQUIRE(Synonym::create(Constants::ASSIGN, "a")->isConstant() == false);
	REQUIRE(Synonym::create(Constants::ASSIGN, "a")->isWildcard() == false);
}

// TESTS FOR BASE SYNONYM CLASS FUNCTIONS
TEST_CASE("Synonym name matches given name works correctly") {
	CallSynonym cl("cll");
	REQUIRE(cl.matchesName("cll") == true);
}

TEST_CASE("Synonym name does not match different name") {
	ProcedureSynonym cl("cll");
	REQUIRE(cl.matchesName("clo") == false);
}

TEST_CASE("Adding non-duplicate results returns the correct set") {
	ProcedureSynonym cl("cll");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v1");

	REQUIRE(cl.getMatches() == unordered_set<string>({"v", "v1"}));
}

TEST_CASE("Adding duplicate results returns the correct set") {
	ProcedureSynonym cl("cll");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v1");
	cl.addMatchingResult("v");

	REQUIRE(cl.getMatches() == unordered_set<string>({ "v", "v1" }));
}

TEST_CASE("Adding results to set will NOT match with different set") {
	ProcedureSynonym cl("cll");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v");
	cl.addMatchingResult("v1");
	cl.addMatchingResult("v");

	REQUIRE(cl.getMatches() != unordered_set<string>({ "c", "v1" }));
}

TEST_CASE("Compare function returns the right results for Synonyms of the same type and name") {
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->compare(Synonym::create(Constants::ASSIGN, "x")) == true);
	REQUIRE(Synonym::create(Constants::CALL, "x")->compare(Synonym::create(Constants::CALL, "x")) == true);
}

TEST_CASE("Compare function returns false for Synonyms of different type") {
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->compare(Synonym::create(Constants::ASSIGN, "x")) == false);
	REQUIRE(Synonym::create(Constants::CALL, "x")->compare(Synonym::create(Constants::PROCEDURE, "x")) == false);
}

TEST_CASE("Compare function returns false for Synonyms of different name") {
	REQUIRE(Synonym::create(Constants::ASSIGN, "y")->compare(Synonym::create(Constants::ASSIGN, "x")) == false);
	REQUIRE(Synonym::create(Constants::CALL, "x")->compare(Synonym::create(Constants::CALL, "y")) == false);
}



// TESTS FOR STATIC SYNONYM CLASS FUNCTIONS
TEST_CASE("create function creates the right classes based on the keywords passed in") {
	REQUIRE(Synonym::create(Constants::STMT, "x")->matchesKeyword(Constants::STMT));
	REQUIRE(Synonym::create(Constants::READ, "x")->matchesKeyword(Constants::READ));
	REQUIRE(Synonym::create(Constants::PRINT, "x")->matchesKeyword(Constants::PRINT));
	REQUIRE(Synonym::create(Constants::CALL, "x")->matchesKeyword(Constants::CALL));
	REQUIRE(Synonym::create(Constants::WHILE, "x")->matchesKeyword(Constants::WHILE));
	REQUIRE(Synonym::create(Constants::IF, "x")->matchesKeyword(Constants::IF));
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->matchesKeyword(Constants::ASSIGN));
	REQUIRE(Synonym::create(Constants::VARIABLE, "x")->matchesKeyword(Constants::VARIABLE));
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->matchesKeyword(Constants::CONSTANT));
	REQUIRE(Synonym::create(Constants::PROCEDURE, "x")->matchesKeyword(Constants::PROCEDURE));
	REQUIRE(Synonym::create(Constants::BOOLEAN, "x")->matchesKeyword(Constants::BOOLEAN));
	REQUIRE(Synonym::create(Constants::SYNTAX_ERROR, "x")->matchesKeyword(Constants::SYNTAX_ERROR));
	REQUIRE(Synonym::create(Constants::SEMANTIC_ERROR, "x")->matchesKeyword(Constants::SEMANTIC_ERROR));
}

TEST_CASE("create function with attrName creates the right classes based on the keywords passed in") {
	const std::string& attr1 = Constants::PROCNAME;
	const std::string& attr2 = Constants::VARNAME;
	const std::string& attr3 = Constants::VALUE;
	const std::string& attr4 = Constants::STMTNUM;
	REQUIRE(Synonym::create(Constants::STMT, "x", attr1)->matchesKeyword(Constants::STMT));
	REQUIRE(Synonym::create(Constants::STMT, "x", attr1)->matchesAttrName(attr1));

	REQUIRE(Synonym::create(Constants::READ, "x", attr2)->matchesKeyword(Constants::READ));
	REQUIRE(Synonym::create(Constants::READ, "x", attr2)->matchesAttrName(attr2));

	REQUIRE(Synonym::create(Constants::PRINT, "x", attr3)->matchesKeyword(Constants::PRINT));
	REQUIRE(Synonym::create(Constants::PRINT, "x", attr3)->matchesAttrName(attr3));

	REQUIRE(Synonym::create(Constants::CALL, "x", attr4)->matchesKeyword(Constants::CALL));
	REQUIRE(Synonym::create(Constants::CALL, "x", attr4)->matchesAttrName(attr4));

	REQUIRE(Synonym::create(Constants::WHILE, "x", attr1)->matchesKeyword(Constants::WHILE));
	REQUIRE(Synonym::create(Constants::WHILE, "x", attr1)->matchesAttrName(attr1));

	REQUIRE(Synonym::create(Constants::IF, "x", attr2)->matchesKeyword(Constants::IF));
	REQUIRE(Synonym::create(Constants::IF, "x", attr2)->matchesAttrName(attr2));

	REQUIRE(Synonym::create(Constants::ASSIGN, "x", attr3)->matchesKeyword(Constants::ASSIGN));
	REQUIRE(Synonym::create(Constants::ASSIGN, "x", attr3)->matchesAttrName(attr3));

	REQUIRE(Synonym::create(Constants::VARIABLE, "x", attr4)->matchesKeyword(Constants::VARIABLE));
	REQUIRE(Synonym::create(Constants::VARIABLE, "x", attr4)->matchesAttrName(attr4));

	REQUIRE(Synonym::create(Constants::CONSTANT, "x", attr1)->matchesKeyword(Constants::CONSTANT));
	REQUIRE(Synonym::create(Constants::CONSTANT, "x", attr1)->matchesAttrName(attr1));

	REQUIRE(Synonym::create(Constants::PROCEDURE, "x", attr2)->matchesKeyword(Constants::PROCEDURE));
	REQUIRE(Synonym::create(Constants::PROCEDURE, "x", attr2)->matchesAttrName(attr2));
}


// TESTS FOR POLYMORPHIC FUNCTIONS IN CONCRETE SYNONYM CLASSES
TEST_CASE("All concrete synonym classes match the correct keywords") {
	StmtSynonym st("cll");
	ReadSynonym re("cll");
	PrintSynonym pr("cll");
	CallSynonym cl("cll");
	WhileSynonym wh("cll");
	IfSynonym i("cll");
	AssignSynonym asg("cll");
	VariableSynonym var("cll");
	ConstantSynonym cnst("cll");
	ProcedureSynonym proc("cll");

	REQUIRE(st.matchesKeyword(Constants::STMT) == true);
	REQUIRE(re.matchesKeyword(Constants::READ) == true);
	REQUIRE(pr.matchesKeyword(Constants::PRINT) == true);
	REQUIRE(cl.matchesKeyword(Constants::CALL) == true);
	REQUIRE(wh.matchesKeyword(Constants::WHILE) == true);
	REQUIRE(i.matchesKeyword(Constants::IF) == true);
	REQUIRE(asg.matchesKeyword(Constants::ASSIGN) == true);
	REQUIRE(var.matchesKeyword(Constants::VARIABLE) == true);
	REQUIRE(cnst.matchesKeyword(Constants::CONSTANT) == true);
	REQUIRE(proc.matchesKeyword(Constants::PROCEDURE) == true);
}

TEST_CASE("All concrete synonym classes returns false for the wrong keywords") {
	StmtSynonym st("cll");
	ReadSynonym re("cll");
	PrintSynonym pr("cll");
	CallSynonym cl("cll");
	WhileSynonym wh("cll");
	IfSynonym i("cll");
	AssignSynonym asg("cll");
	VariableSynonym var("cll");
	ConstantSynonym cnst("cll");
	ProcedureSynonym proc("cll");

	REQUIRE(st.matchesKeyword(Constants::READ) == false);
	REQUIRE(re.matchesKeyword(Constants::PRINT) == false);
	REQUIRE(pr.matchesKeyword(Constants::CALL) == false);
	REQUIRE(cl.matchesKeyword(Constants::WHILE) == false);
	REQUIRE(wh.matchesKeyword(Constants::IF) == false);
	REQUIRE(i.matchesKeyword(Constants::ASSIGN) == false);
	REQUIRE(asg.matchesKeyword(Constants::VARIABLE) == false);
	REQUIRE(var.matchesKeyword(Constants::CONSTANT) == false);
	REQUIRE(cnst.matchesKeyword(Constants::PROCEDURE) == false);
	REQUIRE(proc.matchesKeyword(Constants::STMT) == false);
}

TEST_CASE("All concrete synonym classes returns the right results for isStmtRef function") {
	StmtSynonym st("cll");
	ReadSynonym re("cll");
	PrintSynonym pr("cll");
	CallSynonym cl("cll");
	WhileSynonym wh("cll");
	IfSynonym i("cll");
	AssignSynonym asg("cll");
	VariableSynonym var("cll");
	ConstantSynonym cnst("cll");
	ProcedureSynonym proc("cll");

	REQUIRE(Synonym::create(Constants::STMT, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::READ, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::PRINT, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::CALL, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::WHILE, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::IF, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->isStmtRef() == true);
	REQUIRE(Synonym::create(Constants::VARIABLE, "x")->isStmtRef() == false);
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->isStmtRef() == false);
	REQUIRE(Synonym::create(Constants::PROCEDURE, "x")->isStmtRef() == false);
}

TEST_CASE("All concrete synonym classes returns the right results for isVariableSyn function") {
	StmtSynonym st("cll");
	ReadSynonym re("cll");
	PrintSynonym pr("cll");
	CallSynonym cl("cll");
	WhileSynonym wh("cll");
	IfSynonym i("cll");
	AssignSynonym asg("cll");
	VariableSynonym var("cll");
	ConstantSynonym cnst("cll");
	ProcedureSynonym proc("cll");

	REQUIRE(Synonym::create(Constants::STMT, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::READ, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::PRINT, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::CALL, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::WHILE, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::IF, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::VARIABLE, "x")->isVariableSyn() == true);
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->isVariableSyn() == false);
	REQUIRE(Synonym::create(Constants::PROCEDURE, "x")->isVariableSyn() == false);
}

TEST_CASE("isBooleanSyn function returns the right result for the type of Synonym") {
	REQUIRE(Synonym::create(Constants::STMT, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::READ, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::PRINT, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::CALL, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::WHILE, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::IF, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::ASSIGN, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::VARIABLE, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::CONSTANT, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::PROCEDURE, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::BOOLEAN, "x")->isBooleanSyn() == true);
	REQUIRE(Synonym::create(Constants::SYNTAX_ERROR, "x")->isBooleanSyn() == false);
	REQUIRE(Synonym::create(Constants::SEMANTIC_ERROR, "x")->isBooleanSyn() == false);
}


// Test case for resolveAttrResult
SCENARIO("Mocking behavior of QPS for resolveAttrResult") {
	GIVEN("An instance of the PKB retriever class") {
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

		PkbRetriever pkbRetriever(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer,
			fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cStarsPointer,
                                  printAttrStorage, readAttrStorage, callAttrStorage, nextPointer);
		std::shared_ptr<PkbRetriever> pkbRet = std::make_shared<PkbRetriever>(pkbRetriever);

		WHEN("Populated with the attrname information") {
			// Mock variables appearing in the SIMPLE program
			vsPointer->addVar("w");
			vsPointer->addVar("x");
			vsPointer->addVar("y");
			vsPointer->addVar("z");

			// Mock constants appearing in the SIMPLE program
			csPointer->addConst(123);
			csPointer->addConst(456);
			csPointer->addConst(789);

			// Mock procedures appearing in the SIMPLE program
			psPointer->addProc("main");
			psPointer->addProc("factorial");
			psPointer->addProc("beta");

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

			THEN("When evaluating stmt.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "1", "1" });
				expectedTable->addRow({ "2", "2" });
				expectedTable->addRow({ "3", "3" });
				expectedTable->addRow({ "4", "4" });
				expectedTable->addRow({ "5", "5" });
				expectedTable->addRow({ "6", "6" });
				expectedTable->addRow({ "7", "7" });
				expectedTable->addRow({ "8", "8" });
				expectedTable->addRow({ "9", "9" });
				expectedTable->addRow({ "10", "10" });
				expectedTable->addRow({ "11", "11" });
				expectedTable->addRow({ "12", "12" });
				expectedTable->addRow({ "13", "13" });
				expectedTable->addRow({ "14", "14" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::STMT, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating asg.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#"} );
				expectedTable->addRow({ "1", "1" });
				expectedTable->addRow({ "3", "3" });
				expectedTable->addRow({ "7", "7" });
				expectedTable->addRow({ "9", "9" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::ASSIGN, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating if.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "11", "11" });
				expectedTable->addRow({ "4", "4" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::IF, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating while.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "2", "2" });
				expectedTable->addRow({ "8", "8" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::WHILE, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating read.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "12", "12" });
				expectedTable->addRow({ "5", "5" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::READ, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating print.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "13", "13" });
				expectedTable->addRow({ "6", "6" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::PRINT, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating call.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "14", "14" });
				expectedTable->addRow({ "10", "10" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::CALL, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating proc.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "main", "main" });
				expectedTable->addRow({ "factorial", "factorial" });
				expectedTable->addRow({ "beta", "beta" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::PROCEDURE, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating var.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "w", "w" });
				expectedTable->addRow({ "x", "x" });
				expectedTable->addRow({ "y", "y" });
				expectedTable->addRow({ "z", "z" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::VARIABLE, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}

			THEN("When evaluating const.stmt#") {
				Constants::ClauseResult expectedStatus = Constants::ClauseResult::OK;
				std::shared_ptr<QpsTable> expectedTable = QpsTable::create({ "s1", "s1.stmt#" });
				expectedTable->addRow({ "123", "123" });
				expectedTable->addRow({ "456", "456" });
				expectedTable->addRow({ "789", "789" });

				std::shared_ptr<Synonym> syn = Synonym::create(Constants::CONSTANT, "s1", Constants::STMTNUM);

				REQUIRE(syn->resolveAttrResult(pkbRet).first == expectedStatus);
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getHeaders() == expectedTable->getHeaders());
				REQUIRE(syn->resolveAttrResult(pkbRet).second->getData() == expectedTable->getData());
			}
		}
	}
}