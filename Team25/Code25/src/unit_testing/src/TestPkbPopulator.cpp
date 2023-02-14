#include "PKB/PkbPopulator.h"
#include <iostream>
#include "catch.hpp"

using namespace std;

SCENARIO("Working version of PkbPopulator") {
	GIVEN("Valid instances of empty stores") {
		VariableStore vs;
		ConstantStore cs;
		FollowsStore fs;
		ProcedureStore ps;
		StatementStore ss;
	

		WHEN("The PkbPopulator references empty stores") {
			std::shared_ptr vsPointer = std::make_shared<VariableStore>(vs);
			std::shared_ptr csPointer = std::make_shared<ConstantStore>(cs);
			std::shared_ptr fsPointer = std::make_shared<FollowsStore>(fs);
			std::shared_ptr psPointer = std::make_shared<ProcedureStore>(ps);
			std::shared_ptr ssPointer = std::make_shared<StatementStore>(ss);

			PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer);
			THEN("Adding one variable should increase the variable store size by 1") {
				REQUIRE(vsPointer -> size() == 0);
				pkbPop.addVar("x");
				REQUIRE(vsPointer -> size() == 1);
			}
			THEN("Adding one constant should increase the constant store size by 1") {
				REQUIRE(csPointer -> size() == 0);
				pkbPop.addConst(10000);
				REQUIRE(csPointer -> size() == 1);
			}
			THEN("Adding one procedure should increase the procedure store size by 1") {
				REQUIRE(psPointer -> size() == 0);
				pkbPop.addProc("sampleProc");
				REQUIRE(psPointer -> size() == 1);
			}
			THEN("Adding one statement should increase the statement store size by 1") {
				REQUIRE(ssPointer -> size() == 0);
				pkbPop.addStmt("assign", 2);
				REQUIRE(ssPointer -> size() == 1);
			}
			THEN("Adding one follows relationship should increase the follows store size by 1") {
				REQUIRE(fsPointer -> getAllFollowers().size() == 0);
				REQUIRE(fsPointer -> getAllFollowees().size() == 0);
				pkbPop.addFollows(1, 2);
				REQUIRE(fsPointer -> getAllFollowers().size() == 1);
				REQUIRE(fsPointer -> getAllFollowees().size() == 1);
			}
		}
	}
}

