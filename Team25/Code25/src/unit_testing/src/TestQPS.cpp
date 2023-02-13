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
		ParserResponse response;
		PkbRetriever pkbRetriever(&vs, &cs, &fs, &ps, &ss);

		WHEN("The qps object is created") {
			Qps qps(std::make_shared<PkbRetriever>(pkbRetriever));
			THEN("For a given query string and population of the pkbRetriever") {
				list<string> expected = { "x", "y", "z" };
				list<string> res;
				
				string query = "variable x, v; Select v";

				vs.addVar("x");
				vs.addVar("y");
				vs.addVar("z");

				qps.query(query, res);
				REQUIRE(res == expected);
			}
		}
	}
}
