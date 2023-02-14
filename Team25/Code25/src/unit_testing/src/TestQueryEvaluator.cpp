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
				std::shared_ptr vsPointer = std::make_shared<VariableStore>(vs);
				std::shared_ptr csPointer = std::make_shared<ConstantStore>(cs);
				std::shared_ptr fsPointer = std::make_shared<FollowsStore>(fs);
				std::shared_ptr psPointer = std::make_shared<ProcedureStore>(ps);
				std::shared_ptr ssPointer = std::make_shared<StatementStore>(ss);

				PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer);

				response.setDeclarations({ {"variable", "v", ",", "x"} });
				response.setSynonym("v");
				vsPointer -> add("x");
				vsPointer -> add("y");
				vsPointer -> add("z");

				list<string> res = qe.evaluate(response, &pkbRet);
				REQUIRE(res == expected);
			}
		}
	}
}
