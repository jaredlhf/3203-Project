#include "catch.hpp"
#include "QPS/QueryEvaluator.h"
#include "QPS/ParserResponse.h"
#include "PKB/PkbRetriever.h"
#include <iostream>

using namespace std;

// Scenario with pkb stubs for main evaluate function
SCENARIO("Mocking behavior of ParserResponse and PkbRetriever for QpsEvaluator test") {
	GIVEN("An instance of a QpsEvaluator class") {
		QueryEvaluator qe;

		WHEN("ParserResponse and PkbRetriever are populated with query for variables") {

			THEN("When QpsEvaluator evaluates with the given stub, it should return x, y and z") {
				list<string> expected = { "x", "y", "z" };
				VariableStore vs;
				ConstantStore cs;
				FollowsStore fs;
				ProcedureStore ps;
				StatementStore ss;
				ParserResponse response;
				PkbRetriever pkbRetriever(&vs, &cs, &fs, &ps, &ss);

				response.setDeclarations({Synonym::create(Constants::VARIABLE, "x"), Synonym::create(Constants::VARIABLE, "v") });
				response.setSynonym(Synonym::create(Constants::VARIABLE, "v"));
				vs.addVar("x");
				vs.addVar("y");
				vs.addVar("z");

				list<string> res = qe.evaluate(response, std::make_shared<PkbRetriever>(pkbRetriever));
				REQUIRE(res == expected);
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
