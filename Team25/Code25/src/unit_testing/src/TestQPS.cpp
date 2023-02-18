#include "catch.hpp"
#include "QPS/Qps.h"
#include <iostream>

using namespace std;

SCENARIO("Mocking behavior of QPS") {
	GIVEN("An instance of the PKB retriever class") {
		VariableStore vs;
		ConstantStore cs;
		FollowsStore fs;
		ProcedureStore ps;
		StatementStore ss;
		PatternStore patts;
		ParserResponse response;
		std::shared_ptr vsPointer = std::make_shared<VariableStore>(vs);
		std::shared_ptr csPointer = std::make_shared<ConstantStore>(cs);
		std::shared_ptr fsPointer = std::make_shared<FollowsStore>(fs);
		std::shared_ptr psPointer = std::make_shared<ProcedureStore>(ps);
		std::shared_ptr ssPointer = std::make_shared<StatementStore>(ss);
		std::shared_ptr pattsPointer = std::make_shared<PatternStore>(patts);

		PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer);

		WHEN("The qps object is created") {
			Qps qps(std::make_shared<PkbRetriever>(pkbRet));

			THEN("For a given query string and population of the pkbRetriever") {
				list<string> expected = { "x", "y", "z" };
				list<string> res;
				
				string query = "variable x, v; Select v";

				vsPointer -> add("x");
				vsPointer -> add("y");
				vsPointer -> add("z");

				qps.query(query, res);
				REQUIRE(res == expected);
			}
		}
	}
}
