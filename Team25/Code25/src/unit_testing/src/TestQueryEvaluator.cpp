#include "catch.hpp"
#include "PKB/PkbRetriever.h"
#include "QPS/QueryEvaluator.h"
#include "QPS/ParserResponse.h"
#include <iostream>

using namespace std;

// Scenario with pkb stubs for main evaluate function
SCENARIO("Mocking behavior of ParserResponse and PkbRetriever for QpsEvaluator test") {
	GIVEN("An instance of a QpsEvaluator class") {
		QueryEvaluator qe;

		WHEN("ParserResponse and PkbRetriever are populated with query for variables") {
			VariableStore vs;
			ConstantStore cs;
			FollowsStore fs;
			ProcedureStore ps;
			StatementStore ss;
			PatternStore patts;

			ParserResponse response;
			std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
			std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
			std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
			std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
			std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
			std::shared_ptr<PatternStore> pattsPointer = std::make_shared<PatternStore>(patts);

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer);

			// Mock variables appearing in the SIMPLE program
			vsPointer->add("x");
			vsPointer->add("y");
			vsPointer->add("z");

			// Mock constants appearing in the SIMPLE program
			csPointer->add(123);
			csPointer->add(456);
			csPointer->add(789);

			// Mock procedures appearing in the SIMPLE program
			psPointer->add("main");
			psPointer->add("factorial");
			psPointer->add("beta");

			// Mock statements appearing in the SIMPLE program
			ssPointer->addStmt(Constants::ASSIGN, 1);
			ssPointer->addStmt(Constants::ASSIGN, 2);
			ssPointer->addStmt(Constants::CALL, 3);
			ssPointer->addStmt(Constants::CALL, 4);
			ssPointer->addStmt(Constants::WHILE, 5);
			ssPointer->addStmt(Constants::WHILE, 6);
			ssPointer->addStmt(Constants::IF, 7);
			ssPointer->addStmt(Constants::IF, 8);
			ssPointer->addStmt(Constants::PRINT, 9);
			ssPointer->addStmt(Constants::PRINT, 10);
			ssPointer->addStmt(Constants::READ, 11);
			ssPointer->addStmt(Constants::READ, 12);

			THEN("When QpsEvaluator evaluates a singular select of SyntaxError, it should return SYN_ERR") {
				list<string> expected = {Constants::SYNTAX_ERROR};
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::SYNTAX_ERROR, "v"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of SemanticError, it should return SEM_ERR") {
				list<string> expected = { Constants::SEMANTIC_ERROR };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::SEMANTIC_ERROR, "v"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of VariableSynonym, it should return the right results") {
				list<string> expected = { "x", "y", "z" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::VARIABLE, "x"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of ProcedureSynonym, it should return the right results") {
				list<string> expected = { "beta", "factorial", "main" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::PROCEDURE, "pr"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of ConstantSynonym, it should return the right results") {
				list<string> expected = { "123", "456", "789" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::CONSTANT, "cs"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of StmtSynonym, it should return the right results") {
				list<string> expected = { "1", "10", "11", "12", "2", "3", "4", "5", "6", "7", "8", "9" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::STMT, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::STMT, "cs"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of AssignSynonym, it should return the right results") {
				list<string> expected = { "1","2" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::ASSIGN, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::ASSIGN, "a"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of CallSynonym, it should return the right results") {
				list<string> expected = { "3","4" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::CALL, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::CALL, "cl"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of WhileSynonym, it should return the right results") {
				list<string> expected = { "5","6" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::WHILE, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::WHILE, "wl"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of IfSynonym, it should return the right results") {
				list<string> expected = { "7","8" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::IF, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::IF, "ifs"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of PrintSynonym, it should return the right results") {
				list<string> expected = { "10", "9"};
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::PRINT, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::PRINT, "ifs"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}

			THEN("When QpsEvaluator evaluates a singular select of ReadSynonym, it should return the right results") {
				list<string> expected = { "11", "12" };
				ParserResponse response;

				response.setDeclarations({ Synonym::create(Constants::READ, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::READ, "rd"));

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRet));
				REQUIRE(res == expected);
			}
		}
	}
}

// Scenario to test the resolveSelectSynonym function
SCENARIO("Mocking behavior of the resolveSelectSynonym function") {
	GIVEN("An instance of a QpsEvaluator class") {
		QueryEvaluator qe;

		WHEN("PkbRetriever is populated with information of different type of synonyms") {
			VariableStore vs;
			ConstantStore cs;
			FollowsStore fs;
			ProcedureStore ps;
			StatementStore ss;
			PatternStore patts;

			ParserResponse response;
			std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
			std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
			std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
			std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
			std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
			std::shared_ptr pattsPointer = std::make_shared<PatternStore>(patts);

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer);

			// Mock variables appearing in the SIMPLE program
			vsPointer->add("x");
			vsPointer->add("y");
			vsPointer->add("z");

			// Mock constants appearing in the SIMPLE program
			csPointer->add(123);
			csPointer->add(456);
			csPointer->add(789);

			// Mock procedures appearing in the SIMPLE program
			psPointer->add("main");
			psPointer->add("factorial");
			psPointer->add("beta");

			// Mock statements appearing in the SIMPLE program
			ssPointer->addStmt(Constants::ASSIGN, 1);
			ssPointer->addStmt(Constants::ASSIGN, 2);
			ssPointer->addStmt(Constants::CALL, 3);
			ssPointer->addStmt(Constants::CALL, 4);
			ssPointer->addStmt(Constants::WHILE, 5);
			ssPointer->addStmt(Constants::WHILE, 6);
			ssPointer->addStmt(Constants::IF, 7);
			ssPointer->addStmt(Constants::IF, 8);
			ssPointer->addStmt(Constants::PRINT, 9);
			ssPointer->addStmt(Constants::PRINT, 10);
			ssPointer->addStmt(Constants::READ, 11);
			ssPointer->addStmt(Constants::READ, 12);


			THEN("QpsEvaluator calling resolveSelectSynonym on SyntaxErrorSynonym returns SYN_ERR") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::SYNTAX_ERROR, "x");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res = 
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({});
				std::set<std::vector<std::string>> expectedData({});

				REQUIRE(res.first == Constants::ClauseResult::SYN_ERR);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on SemanticErrorSynonym returns SEM_ERR") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::SEMANTIC_ERROR, "x");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({});
				std::set<std::vector<std::string>> expectedData({});

				REQUIRE(res.first == Constants::ClauseResult::SEM_ERR);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on VariableSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::VARIABLE, "v");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "v" });
				std::set<std::vector<std::string>> expectedData({ {"x"}, {"y"}, {"z"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on ProcedureSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::PROCEDURE, "p");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "p" });
				std::set<std::vector<std::string>> expectedData({ {"main"}, {"factorial"}, {"beta"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on ConstantSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::CONSTANT, "cs");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "cs" });
				std::set<std::vector<std::string>> expectedData({ {"123"}, {"456"}, {"789"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on StmtSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::STMT, "s");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "s" });
				std::set<std::vector<std::string>> expectedData({ {"1"}, {"2"}, {"3"}, 
					{"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"10"}, {"11"}, {"12"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on AssignSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::ASSIGN, "a");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "a" });
				std::set<std::vector<std::string>> expectedData({ {"1"}, {"2"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on CallSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::CALL, "cl");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "cl" });
				std::set<std::vector<std::string>> expectedData({ {"3"}, {"4"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on WhileSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::WHILE, "wl");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "wl" });
				std::set<std::vector<std::string>> expectedData({ {"5"}, {"6"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on IfSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::IF, "ifs");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "ifs" });
				std::set<std::vector<std::string>> expectedData({ {"7"}, {"8"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on PrintSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::PRINT, "pr");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "pr" });
				std::set<std::vector<std::string>> expectedData({ {"9"}, {"10"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on ReadSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::READ, "rd");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "rd" });
				std::set<std::vector<std::string>> expectedData({ {"11"}, {"12"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}
		}

		WHEN("PkbRetriever is populated with values without any matches") {
			VariableStore vs;
			ConstantStore cs;
			FollowsStore fs;
			ProcedureStore ps;
			StatementStore ss;
			PatternStore patts;

			ParserResponse response;
			std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
			std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
			std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
			std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
			std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
			std::shared_ptr<PatternStore> pattsPointer = std::make_shared<PatternStore>(patts);

			PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer);

			// Mock constants appearing in the SIMPLE program
			csPointer->add(123);
			csPointer->add(456);
			csPointer->add(789);

			// Mock procedures appearing in the SIMPLE program
			psPointer->add("main");
			psPointer->add("factorial");
			psPointer->add("beta");

			// Mock statements appearing in the SIMPLE program
			ssPointer->addStmt(Constants::CALL, 3);
			ssPointer->addStmt(Constants::CALL, 4);
			ssPointer->addStmt(Constants::WHILE, 5);
			ssPointer->addStmt(Constants::WHILE, 6);
			ssPointer->addStmt(Constants::IF, 7);
			ssPointer->addStmt(Constants::IF, 8);
			ssPointer->addStmt(Constants::PRINT, 9);
			ssPointer->addStmt(Constants::PRINT, 10);
			ssPointer->addStmt(Constants::READ, 11);
			ssPointer->addStmt(Constants::READ, 12);

			THEN("QpsEvaluator calling resolveSelectSynonym on ReadSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::READ, "rd");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "rd" });
				std::set<std::vector<std::string>> expectedData({ {"11"}, {"12"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on AssignSynonym returns no match") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::ASSIGN, "a");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "a" });
				std::set<std::vector<std::string>> expectedData({});

				REQUIRE(res.first == Constants::ClauseResult::NO_MATCH);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on ProcedureSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::PROCEDURE, "p");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "p" });
				std::set<std::vector<std::string>> expectedData({ {"main"}, {"factorial"}, {"beta"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on ConstantSynonym returns the right results") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::CONSTANT, "cs");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "cs" });
				std::set<std::vector<std::string>> expectedData({ {"123"}, {"456"}, {"789"} });

				REQUIRE(res.first == Constants::ClauseResult::OK);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}

			THEN("QpsEvaluator calling resolveSelectSynonym on VariableSynonym returns no match") {
				std::shared_ptr<Synonym> s = Synonym::create(Constants::VARIABLE, "v");
				std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res =
					qe.resolveSelectSynonym(s, std::make_shared<PkbRetriever>(pkbRet));

				std::vector<std::string> expectedHeaders({ "v" });
				std::set<std::vector<std::string>> expectedData({});

				REQUIRE(res.first == Constants::ClauseResult::NO_MATCH);
				REQUIRE(res.second->getHeaders() == expectedHeaders);
				REQUIRE(res.second->getData() == expectedData);
			}
		}
	}
}

// Test cases for the resolveClauses function
TEST_CASE("resolveClauses function returns the right result for a clause with SYN_ERR") {
	QueryEvaluator qe;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause1;
	std::vector<std::string> t1row1({ "1" });
	std::vector<std::string> t1row2({ "2" });
	std::vector<std::string> t1row3({ "3" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3 });

	std::vector<std::string> header1({ "a" });

	std::shared_ptr<QpsTable> clause1Table = QpsTable::create(header1, t1Data);
	clause1.first = Constants::ClauseResult::SYN_ERR;
	clause1.second = clause1Table;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause2;
	std::vector<std::string> t2row1({ "2", "x" });
	std::vector<std::string> t2row2({ "3", "y" });
	std::vector<std::string> t2row3({ "4", "z" });
	std::vector<std::string> t2row4({ "5", "w" });
	std::set<std::vector<std::string>> t2Data({ t2row1, t2row2, t2row3, t2row4 });

	std::vector<std::string> header2({ "s", "v" });

	std::shared_ptr<QpsTable> clause2Table = QpsTable::create(header2, t2Data);
	clause2.first = Constants::ClauseResult::OK;
	clause2.second = clause2Table;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause3;
	std::vector<std::string> t3row1({ "1", "x" });
	std::vector<std::string> t3row2({ "3", "y" });
	std::vector<std::string> t3row3({ "4", "z" });
	std::vector<std::string> t3row4({ "5", "w" });
	std::set<std::vector<std::string>> t3Data({ t3row1, t3row2, t3row3, t3row4 });

	std::vector<std::string> header3({ "a", "v" });

	std::shared_ptr<QpsTable> clause3Table = QpsTable::create(header3, t3Data);
	clause3.first = Constants::ClauseResult::SEM_ERR;
	clause3.second = clause3Table;

	std::vector<std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>> clauses({clause1, clause2, clause3});
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res = qe.resolveClauses(clauses);
	
	REQUIRE(res.first == Constants::ClauseResult::SYN_ERR);
	REQUIRE(res.second->getHeaders().size() == 0);
	REQUIRE(res.second->getData().size() == 0);
}

TEST_CASE("resolveClauses function returns the right result for a clause with SEM_ERR") {
	QueryEvaluator qe;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause1;
	std::vector<std::string> t1row1({ "1" });
	std::vector<std::string> t1row2({ "2" });
	std::vector<std::string> t1row3({ "3" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3 });

	std::vector<std::string> header1({ "a" });

	std::shared_ptr<QpsTable> clause1Table = QpsTable::create(header1, t1Data);
	clause1.first = Constants::ClauseResult::OK;
	clause1.second = clause1Table;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause2;
	std::vector<std::string> t2row1({ "2", "x" });
	std::vector<std::string> t2row2({ "3", "y" });
	std::vector<std::string> t2row3({ "4", "z" });
	std::vector<std::string> t2row4({ "5", "w" });
	std::set<std::vector<std::string>> t2Data({ t2row1, t2row2, t2row3, t2row4 });

	std::vector<std::string> header2({ "s", "v" });

	std::shared_ptr<QpsTable> clause2Table = QpsTable::create(header2, t2Data);
	clause2.first = Constants::ClauseResult::OK;
	clause2.second = clause2Table;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause3;
	std::vector<std::string> t3row1({ "1", "x" });
	std::vector<std::string> t3row2({ "3", "y" });
	std::vector<std::string> t3row3({ "4", "z" });
	std::vector<std::string> t3row4({ "5", "w" });
	std::set<std::vector<std::string>> t3Data({ t3row1, t3row2, t3row3, t3row4 });

	std::vector<std::string> header3({ "a", "v" });

	std::shared_ptr<QpsTable> clause3Table = QpsTable::create(header3, t3Data);
	clause3.first = Constants::ClauseResult::SEM_ERR;
	clause3.second = clause3Table;

	std::vector<std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>> clauses({ clause1, clause2, clause3 });
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res = qe.resolveClauses(clauses);

	REQUIRE(res.first == Constants::ClauseResult::SEM_ERR);
	REQUIRE(res.second->getHeaders().size() == 0);
	REQUIRE(res.second->getData().size() == 0);
}

TEST_CASE("resolveClauses function returns the right result for a clause with NO_MATCH") {
	QueryEvaluator qe;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause1;
	std::vector<std::string> t1row1({ "1" });
	std::vector<std::string> t1row2({ "2" });
	std::vector<std::string> t1row3({ "3" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3 });

	std::vector<std::string> header1({ "a" });

	std::shared_ptr<QpsTable> clause1Table = QpsTable::create(header1, t1Data);
	clause1.first = Constants::ClauseResult::OK;
	clause1.second = clause1Table;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause2;
	std::vector<std::string> t2row1({ "2", "x" });
	std::vector<std::string> t2row2({ "3", "y" });
	std::vector<std::string> t2row3({ "4", "z" });
	std::vector<std::string> t2row4({ "5", "w" });
	std::set<std::vector<std::string>> t2Data({ t2row1, t2row2, t2row3, t2row4 });

	std::vector<std::string> header2({ "s", "v" });

	std::shared_ptr<QpsTable> clause2Table = QpsTable::create(header2, t2Data);
	clause2.first = Constants::ClauseResult::NO_MATCH;
	clause2.second = clause2Table;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause3;
	std::vector<std::string> t3row1({ "1", "x" });
	std::vector<std::string> t3row2({ "3", "y" });
	std::vector<std::string> t3row3({ "4", "z" });
	std::vector<std::string> t3row4({ "5", "w" });
	std::set<std::vector<std::string>> t3Data({ t3row1, t3row2, t3row3, t3row4 });

	std::vector<std::string> header3({ "a", "v" });

	std::shared_ptr<QpsTable> clause3Table = QpsTable::create(header3, t3Data);
	clause3.first = Constants::ClauseResult::OK;
	clause3.second = clause3Table;

	std::vector<std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>> clauses({ clause1, clause2, clause3 });
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res = qe.resolveClauses(clauses);

	REQUIRE(res.first == Constants::ClauseResult::NO_MATCH);
	REQUIRE(res.second->getHeaders().size() == 0);
	REQUIRE(res.second->getData().size() == 0);
}

TEST_CASE("resolveClauses function returns the right result for a clause for a valid set of clause tables with 3 related rows") {
	QueryEvaluator qe;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause1;
	std::vector<std::string> t1row1({ "1" });
	std::vector<std::string> t1row2({ "2" });
	std::vector<std::string> t1row3({ "3" });
	std::set<std::vector<std::string>> t1Data({ t1row1, t1row2, t1row3 });

	std::vector<std::string> header1({ "a" });

	std::shared_ptr<QpsTable> clause1Table = QpsTable::create(header1, t1Data);
	clause1.first = Constants::ClauseResult::OK;
	clause1.second = clause1Table;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause2;
	std::vector<std::string> t2row1({ "2", "x" });
	std::vector<std::string> t2row2({ "3", "y" });
	std::vector<std::string> t2row3({ "4", "z" });
	std::vector<std::string> t2row4({ "5", "w" });
	std::set<std::vector<std::string>> t2Data({ t2row1, t2row2, t2row3, t2row4 });

	std::vector<std::string> header2({ "s", "v" });

	std::shared_ptr<QpsTable> clause2Table = QpsTable::create(header2, t2Data);
	clause2.first = Constants::ClauseResult::OK;
	clause2.second = clause2Table;

	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> clause3;
	std::vector<std::string> t3row1({ "1", "x" });
	std::vector<std::string> t3row2({ "3", "y" });
	std::vector<std::string> t3row3({ "4", "z" });
	std::vector<std::string> t3row4({ "5", "w" });
	std::set<std::vector<std::string>> t3Data({ t3row1, t3row2, t3row3, t3row4 });

	std::vector<std::string> header3({ "a", "v" });

	std::shared_ptr<QpsTable> clause3Table = QpsTable::create(header3, t3Data);
	clause3.first = Constants::ClauseResult::OK;
	clause3.second = clause3Table;

	std::vector<std::string> expectedRow1({ "1", "2", "x" });
	std::vector<std::string> expectedRow2({ "3", "3", "y"});
	std::set<std::vector<std::string>> expectedData({ expectedRow1, expectedRow2 });

	std::vector<std::string> expectedHeader({ "a", "s", "v" });

	std::shared_ptr<QpsTable> expectedTable = QpsTable::create(expectedHeader, expectedData);
	std::set<std::string> expectedFirstCol({ "1", "3" });

	std::vector<std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>> clauses({ clause1, clause2, clause3 });
	std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> res = qe.resolveClauses(clauses);

	REQUIRE(res.first == Constants::ClauseResult::OK);
	REQUIRE(res.second->getHeaders() == expectedTable->getHeaders());
	REQUIRE(res.second->getData() == expectedTable->getData());
	REQUIRE(res.second->getData() == expectedTable->getData());
	REQUIRE(res.second->getColResults("a") == expectedFirstCol);
}
