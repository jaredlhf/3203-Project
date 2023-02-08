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
			PkbPopulator pkbPop(&vs, &cs, &fs, &ps, &ss);
			THEN("Adding one variable should increase the variable store size by 1") {
				REQUIRE(vs.size() == 0);
				pkbPop.addVar("x");
				REQUIRE(vs.size() == 1);
			}
			THEN("Adding one constant should increase the constant store size by 1") {
				REQUIRE(cs.size() == 0);
				pkbPop.addConst(10000);
				REQUIRE(cs.size() == 1);
			}
			THEN("Adding one procedure should increase the procedure store size by 1") {
				REQUIRE(ps.size() == 0);
				pkbPop.addProc("sampleProc");
				REQUIRE(ps.size() == 1);
			}
			THEN("Adding one statement should increase the statement store size by 1") {
				REQUIRE(ss.size() == 0);
				pkbPop.addStmt("assign", 2);
				REQUIRE(ss.size() == 1);
			}
		}
	}
}

