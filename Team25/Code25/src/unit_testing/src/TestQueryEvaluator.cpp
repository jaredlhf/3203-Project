#include "catch.hpp"
#include "QPS/QueryEvaluator.h"
#include "QPS/ParserResponse.h"
#include "PKB/PkbRetriever.h"
#include <iostream>

using namespace std;

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
