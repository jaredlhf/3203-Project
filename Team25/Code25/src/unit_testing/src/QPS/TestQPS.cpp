#include "catch.hpp"
#include "QPS/Qps.h"

using namespace std;

SCENARIO("Mocking behavior of QPS") {
	GIVEN("An instance of the PKB retriever class") {
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
		UsesProcStore uprocs;
		UsesStore uses;
		CallsStore calls;
		CallsStarStore cStars;

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
		std::shared_ptr<UsesProcStore> uprocsPointer = std::make_shared<UsesProcStore>(uprocs);
		std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);
		std::shared_ptr<CallsStore> callsPointer = std::make_shared<CallsStore>(calls);
		std::shared_ptr<CallsStarStore> cStarsPointer = std::make_shared<CallsStarStore>(cStars);

		PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cStarsPointer);

		WHEN("The qps object is created") {
			Qps qps(std::make_shared<PkbRetriever>(pkbRet));

			THEN("For a given query string and population of the pkbRetriever") {
				list<string> expected = { "x", "y", "z" };
				list<string> res;

				string query = "variable x, v; Select v";

				vsPointer->addVar("x");
				vsPointer->addVar("y");
				vsPointer->addVar("z");

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For a given multi select query string and population of the pkbRetriever") {
				list<string> expected = { "1 x x", "1 x y", "1 x z", "1 y x", "1 y y", "1 y z", 
					"1 z x", "1 z y", "1 z z", "2 x x", "2 x y", "2 x z", "2 y x", "2 y y", 
					"2 y z", "2 z x", "2 z y", "2 z z", "3 x x", "3 x y", "3 x z", "3 y x", 
					"3 y y", "3 y z", "3 z x", "3 z y", "3 z z" };
				list<string> res;

				string query = "variable x, v; assign a; Select <a, x, v>";

				vsPointer->addVar("x");
				vsPointer->addVar("y");
				vsPointer->addVar("z");
				ssPointer->addStmt("assign", 1);
				ssPointer->addStmt("assign", 2);
				ssPointer->addStmt("assign", 3);

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For a given multi select query string with repeated select and population of the pkbRetriever") {
				list<string> expected = { "1 x x x", "1 y y y", "1 z z z", "2 x x x", "2 y y y", 
					"2 z z z", "3 x x x", "3 y y y", "3 z z z" };
				list<string> res;

				string query = "variable x, v; assign a; Select <a, v, v, v>";

				vsPointer->addVar("x");
				vsPointer->addVar("y");
				vsPointer->addVar("z");
				ssPointer->addStmt("assign", 1);
				ssPointer->addStmt("assign", 2);
				ssPointer->addStmt("assign", 3);

				qps.query(query, res);
				REQUIRE(res == expected);
			}
		}
	}
}

SCENARIO("Mocking behavior of QPS with such that and pattern clauses") {
	GIVEN("An instance of the PKB retriever class") {
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
		UsesProcStore uprocs;
		UsesStore uses;
		CallsStore calls;
		CallsStarStore cStars;

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
		std::shared_ptr<UsesProcStore> uprocsPointer = std::make_shared<UsesProcStore>(uprocs);
		std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);
		std::shared_ptr<CallsStore> callsPointer = std::make_shared<CallsStore>(calls);
		std::shared_ptr<CallsStarStore> cStarsPointer = std::make_shared<CallsStarStore>(cStars);

		// Mock variables appearing in the SIMPLE program
		vsPointer->addVar("w");
		vsPointer->addVar("x");
		vsPointer->addVar("y");
		vsPointer->addVar("z");

		// Mock constants appearing in the SIMPLE program
		csPointer->addConst(123);
		csPointer->addConst(456);
		csPointer->addConst(789);

		// Mock procedures appearing in the SIMPLE program
		psPointer->addProc("main");
		psPointer->addProc("factorial");
		psPointer->addProc("beta");

		// Mock statements appearing in the SIMPLE program
		ssPointer->addStmt(Constants::ASSIGN, 1);
		ssPointer->addStmt(Constants::WHILE, 2);
		ssPointer->addStmt(Constants::ASSIGN, 3);
		ssPointer->addStmt(Constants::IF, 4);
		ssPointer->addStmt(Constants::READ, 5);
		ssPointer->addStmt(Constants::PRINT, 6);
		ssPointer->addStmt(Constants::ASSIGN, 7);
		ssPointer->addStmt(Constants::WHILE, 8);
		ssPointer->addStmt(Constants::ASSIGN, 9);

		// Mock followsSt relationship in SIMPLE program
		fstarsPointer->addFollowsStar(1, { 2 });
		fstarsPointer->addFollowsStar(3, { 4, 8 });
		fstarsPointer->addFollowsStar(4, { 8 });
		fstarsPointer->addFollowsStar(5, { 6, 7 });
		fstarsPointer->addFollowsStar(6, { 7 });

		// Mock follows relationship in SIMPLE program
		fsPointer->addFollows(1, 2);
		fsPointer->addFollows(3, 4);
		fsPointer->addFollows(4, 8);
		fsPointer->addFollows(5, 6);
		fsPointer->addFollows(6, 7);

		// Mock parentSt relationship in SIMPLE program
		pStarsPointer->addParentStar(2, 3);
		pStarsPointer->addParentStar(2, 4);
		pStarsPointer->addParentStar(2, 5);
		pStarsPointer->addParentStar(2, 6);
		pStarsPointer->addParentStar(2, 7);
		pStarsPointer->addParentStar(2, 8);
		pStarsPointer->addParentStar(2, 9);
		pStarsPointer->addParentStar(4, 5);
		pStarsPointer->addParentStar(4, 6);
		pStarsPointer->addParentStar(4, 7);
		pStarsPointer->addParentStar(8, 9);

		// Mock parent relationship in SIMPLE program
		parentsPointer->addParent(2, 3);
		parentsPointer->addParent(2, 4);
		parentsPointer->addParent(2, 8);
		parentsPointer->addParent(4, 5);
		parentsPointer->addParent(4, 6);
		parentsPointer->addParent(4, 7);
		parentsPointer->addParent(8, 9);

		// Mock Modifies relationship in SIMPLE program
		msPointer->addModifies(1, "x");
		msPointer->addModifies(3, "w");
		msPointer->addModifies(5, "y");
		msPointer->addModifies(7, "x");
		msPointer->addModifies(9, "x");

		// Mock Uses relationship in SIMPLE program
		usesPointer->addUses(1, "y");
		usesPointer->addUses(3, "x");
		usesPointer->addUses(6, "x");
		usesPointer->addUses(7, "x");
		usesPointer->addUses(9, "x");

		// Mock Patterns in SIMPLE program
		pattsPointer->addAssignLhs("x", 1);
		pattsPointer->addAssignRhs(1, "y+1");
		pattsPointer->addAssignLhs("w", 3);
		pattsPointer->addAssignRhs(3, "x+1");
		pattsPointer->addAssignLhs("x", 7);
		pattsPointer->addAssignRhs(7, "x+1");
		pattsPointer->addAssignLhs("x", 9);
		pattsPointer->addAssignRhs(9, "x+1");

		// Mock Modifies Relationship for Procedures in SIMPLE program
		mprocsPointer->addModifiesProc("main", "x");
		mprocsPointer->addModifiesProc("main", "y");
		mprocsPointer->addModifiesProc("main", "z");
		mprocsPointer->addModifiesProc("factorial", "x");
		mprocsPointer->addModifiesProc("factorial", "y");
		mprocsPointer->addModifiesProc("beta", "z");

		// Mock UsesRelationship for Procedures in SIMPLE program
		uprocsPointer->addUsesProc("main", "x");
		uprocsPointer->addUsesProc("main", "y");
		uprocsPointer->addUsesProc("main", "z");
		uprocsPointer->addUsesProc("factorial", "x");
		uprocsPointer->addUsesProc("factorial", "y");
		uprocsPointer->addUsesProc("beta", "z");

		// Mock calls relationship in SIMPLE program
		callsPointer->addCalls("factorial", "main");
		callsPointer->addCalls("beta", "main");
		callsPointer->addCalls("beta", "factorial");

		// Mock callsSt relationship in SIMPLE program
		cStarsPointer->addCallsStar("main", "factorial");
		cStarsPointer->addCallsStar("main", "beta");
		cStarsPointer->addCallsStar("factorial", "beta");

		PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cStarsPointer);
		WHEN("The qps object is created") {
			Qps qps(std::make_shared<PkbRetriever>(pkbRet));

			THEN("For follows* query, the right result is returned") {
				list<string> expected = { "1", "3" };
				list<string> res;

				string query = "assign a1; stmt s2; Select a1 such that Follows*(a1, s2)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For parent* query, the right result is returned") {
				list<string> expected = { "2", "8" };
				list<string> res;

				string query = "while w1; Select w1 such that Parent*(2, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For empty parent* query, the no result is returned") {
				list<string> expected = {};
				list<string> res;

				string query = "while w1; Select w1 such that Parent*(1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For parent query, the right result is returned") {
				list<string> expected = { "4" };
				list<string> res;

				string query = "if ifs; Select ifs such that Parent(_, 9)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For follows query, the right result is returned") {
				list<string> expected = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
				list<string> res;

				string query = "stmt stmt; Select stmt such that Follows(_, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For uses query, the right result is returned") {
				list<string> expected = { "3", "6", "7", "9" };
				list<string> res;

				string query = "stmt s1; Select s1 such that Uses(s1, \"x\")";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For uses query with procedures, the right result is returned") {
				list<string> expected = { "factorial", "main" };
				list<string> res;

				string query = "procedure p1; Select p1 such that Uses(p1, \"x\")";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For procedure constant uses query, the right result is returned") {
				list<string> expected = { "x", "y" };
				list<string> res;

				string query = "variable p1; Select p1 such that Uses(\"factorial\", p1)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For follows* query in the form (s1, _), the right result is returned") {
				list<string> expected = { "1", "3", "4", "5", "6" };
				list<string> res;

				string query = "stmt s1; Select s1 such that Follows*(s1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For modifies query in the form (s1, 'y'), the right result is returned") {
				list<string> expected = { "5" };
				list<string> res;

				string query = "read rd1; Select rd1 such that Modifies(rd1, \"y\")";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For modifies query in the form (s1, 'y') with procedure, the right result is returned") {
				list<string> expected = { "beta", "main" };
				list<string> res;

				string query = "procedure p1; Select p1 such that Modifies(p1, \"z\")";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For procedure constant modifies query in the form (s1, 'y'), the right result is returned") {
				list<string> expected = { "w", "x", "y", "z" };
				list<string> res;

				string query = "variable p1; Select p1 such that Modifies(\"beta\", \"z\")";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For uses query in the form (1, 'y'), the right result is returned") {
				list<string> expected = { "6" };
				list<string> res;

				string query = "print pn; Select pn such that Uses(1, \"y\")";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For follows query in the form (1, s2), the right result is returned") {
				list<string> expected = { "2" };
				list<string> res;

				string query = "stmt s2; Select s2 such that Follows(1, s2)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For calls query in the form ('beta', s1), the right result is returned") {
				list<string> expected = { "factorial", "main" };
				list<string> res;

				string query = "procedure s2; Select s2 such that Calls(\"beta\", s2)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For calls* query in the form (_, s1), the right result is returned") {
				list<string> expected = { "beta", "factorial" };
				list<string> res;

				string query = "procedure s2; Select s2 such that Calls*(_, s2)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (_, 'x'), the right result is returned") {
				list<string> expected = { "3", "7", "9"};
				list<string> res;

				string query = "assign a1; stmt s2; Select a1 pattern a1 (_, _\"x\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (_, 'x') with tab spaces, the right result is returned") {
				list<string> expected = { "3", "7", "9" };
				list<string> res;

				string query = "assign a1; stmt s2; Select a1 pattern a1 (_, _\"x\t\t\t\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (_, _), the right result is returned") {
				list<string> expected = { "1", "3", "7", "9" };
				list<string> res;

				string query = "assign a1; stmt s2; Select a1 pattern a1 (_, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (v1, _), the right result is returned") {
				list<string> expected = { "w", "x" };
				list<string> res;

				string query = "assign a1; variable v1; Select v1 pattern a1 (v1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form (v1, _'y'_), the right result is returned") {
				list<string> expected = { "x" };
				list<string> res;

				string query = "assign a1; variable v1; Select v1 pattern a1 (v1, _\"y\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form ('x', _), the right result is returned") {
				list<string> expected = { "1", "7", "9" };
				list<string> res;

				string query = "assign a1; variable v1; Select a1 pattern a1 (\"x\", _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query in the form ('x', _'y'_), the right result is returned") {
				list<string> expected = { "1" };
				list<string> res;

				string query = "assign a1; variable v1; Select a1 pattern a1 (\"x\", _\"y\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For pattern query with var syn in pattern clause, the right result is returned") {
				list<string> expected = { "3", "7", "9" };
				list<string> res;

				string query = "assign a1; variable v1; Select a1 pattern a1 (v1, _\"x\"_)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For combined query, the right result is returned") {
				list<string> expected = { "w", "x" };
				list<string> res;

				string query = "assign a1; variable v1; Select v1 such that Parent(2,3) pattern a1 (v1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For combined query with clauses order swapped, the right result is returned") {
				list<string> expected = { "w", "x" };
				list<string> res;

				string query = "assign a1; variable v1; Select v1 pattern a1 (v1, _) such that Parent(2,3)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For combined query with 1 overlapping synonym, the right result is returned") {
				list<string> expected = { "y" };
				list<string> res;

				string query = "assign a1; variable v1; stmt s1; Select v1 such that Uses(a1,v1) pattern a1 (_,_\"y\"_) ";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For combined query with 1 overlapping synonym multiselect, the right result is returned") {
				list<string> expected = { "1 y", "2 y", "3 y", "4 y", "5 y", "6 y", "7 y", "8 y", "9 y" };
				list<string> res;

				string query = "assign a1; variable v1; stmt s1; Select <s1, v1> such that Uses(a1,v1) pattern a1 (_,_\"y\"_) ";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For combined query with such that and pattern reversed with 1 overlapping synonym, the right result is returned") {
				list<string> expected = { "y" };
				list<string> res;

				string query = "assign a1; variable v1; stmt s1; Select v1 pattern a1 (_,_\"y\"_) such that Uses(a1,v1)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}

			THEN("For combined query with such that and pattern reversed with 1 overlapping synonym multiselect, the right result is returned") {
				list<string> expected = { "y 1" };
				list<string> res;

				string query = "assign a1; variable v1; stmt s1; Select <v1, a1> pattern a1 (_,_\"y\"_) such that Uses(a1,v1)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}
		}
	}
}
