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
				PatternStore patts;
				FollowsStarStore fstars;
				ModifiesProcStore mprocs;
				ModifiesStore ms;
				ParentStarStore pStars;
				ParentStore parents;
				UsesStore uses;
				ParserResponse response;
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
				std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);

				PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, usesPointer);

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
