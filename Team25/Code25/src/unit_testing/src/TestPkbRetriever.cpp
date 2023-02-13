#include "PKB/PkbRetriever.h"
#include <iostream>
#include "catch.hpp"

using namespace std;

SCENARIO("Working version of PkbRetriever") {
	GIVEN("Valid instance of empty stores") {
		VariableStore vs;
		ConstantStore cs;
		FollowsStore fs;
		ProcedureStore ps;
		StatementStore ss;

		WHEN("The PkbRetriever references empty stores") {
			PkbRetriever pkbRet(&vs, &cs, &fs, &ps, &ss);
			THEN("Getting all variables should return an empty list") {
				REQUIRE(pkbRet.getAllVar().size() == 0);
			}
			THEN("Getting all constants should return an empty list") {
				REQUIRE(pkbRet.getAllConst().size() == 0);
			}
			THEN("Getting all follows should return an empty list") {
				REQUIRE(pkbRet.getAllFollowees().size() == 0);
				REQUIRE(pkbRet.getAllFollowers().size() == 0);
			}
			THEN("Getting all constants should return an empty list") {
				REQUIRE(pkbRet.getAllConst().size() == 0);
			}
			THEN("Getting all procedures should return an empty list") {
				REQUIRE(pkbRet.getAllProc().size() == 0);
			}
			THEN("Getting all statements should return an empty list") {
				REQUIRE(pkbRet.getAllStmt("assign").size() == 0);
				REQUIRE(pkbRet.getAllStmt("read").size() == 0);
				REQUIRE(pkbRet.getAllStmt("print").size() == 0);
				REQUIRE(pkbRet.getAllStmt("call").size() == 0);
				REQUIRE(pkbRet.getAllStmt("while").size() == 0);
				REQUIRE(pkbRet.getAllStmt("if").size() == 0);
			}
		}
		WHEN("The PkbRetriever references non-empty stores") {
			PkbRetriever pkbRet(&vs, &cs, &fs, &ps, &ss);
			vs.addVar("x");
			cs.addConst(1);
			fs.addFollows(1, 2);
			ps.addProc("testProc");
			ss.addStmt("assign", 1);
			THEN("Getting all variables hsould return a non empty list") {
				REQUIRE(pkbRet.getAllVar().size() == 1);
				REQUIRE(pkbRet.getAllVar().count("x") == 1);
			}
			THEN("Getting all constants should return a non empty list") {
				REQUIRE(pkbRet.getAllConst().size() == 1);
				REQUIRE(pkbRet.getAllConst().count(1) == 1);
			}
			THEN("Getting all follows should return a non empty list") {
				REQUIRE(pkbRet.getAllFollowees().size() == 1);
				REQUIRE(pkbRet.getAllFollowees().count(2) == 1);
				REQUIRE(pkbRet.getAllFollowers().size() == 1);
				REQUIRE(pkbRet.getAllFollowers().count(1) == 1);
			}
			THEN("Getting all procedures should return a non empty list") {
				REQUIRE(pkbRet.getAllProc().size() == 1);
				REQUIRE(pkbRet.getAllProc().count("testProc") == 1);
			}
			THEN("Getting all statements should return a non empty list") {
				REQUIRE(pkbRet.getAllStmt("assign").size() == 1);
				REQUIRE(pkbRet.getAllStmt("assign").count(1) == 1);
				REQUIRE(pkbRet.getAllStmt("read").size() == 0);
				REQUIRE(pkbRet.getAllStmt("print").size() == 0);
				REQUIRE(pkbRet.getAllStmt("call").size() == 0);
				REQUIRE(pkbRet.getAllStmt("while").size() == 0);
				REQUIRE(pkbRet.getAllStmt("if").size() == 0);
			}
		}
	}
}