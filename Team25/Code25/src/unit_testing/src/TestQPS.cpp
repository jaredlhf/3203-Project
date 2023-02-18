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

		// Mock variables appearing in the SIMPLE program
		vsPointer->add("w");
		vsPointer->add("x");
		vsPointer->add("y");
		vsPointer->add("z");

		// Mock constants appearing in the SIMPLE program
		csPointer->add(123);
		csPointer->add(456);
		csPointer->add(789);

		// Mock procedures appearing in the SIMPLE program
		psPointer->add("main");
		psPointer->add("factorial");
		psPointer->add("beta");

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
		pStarsPointer->addParentStar(2, { 3,4,5,6,7,8,9 });
		pStarsPointer->addParentStar(4, { 5,6,7 });
		pStarsPointer->addParentStar(8, { 9 });

		// Mock parent relationship in SIMPLE program
		parentsPointer->addParent(2, 3);
		parentsPointer->addParent(2, 4);
		parentsPointer->addParent(2, 8);
		parentsPointer->addParent(4, 5);
		parentsPointer->addParent(4, 6);
		parentsPointer->addParent(4, 7);
		parentsPointer->addParent(8, 9);

		// Mock Modifies relationship in SIMPLE program
		msPointer->add(1, "x");
		msPointer->add(3, "w");
		msPointer->add(5, "y");
		msPointer->add(7, "x");
		msPointer->add(9, "x");

		// Mock Patterns in SIMPLE program
		pattsPointer->addAssignLhs("x", 1);
		pattsPointer->addAssignRhs(1, "y+1");
		pattsPointer->addAssignLhs("w", 3);
		pattsPointer->addAssignRhs(3, "x+1");
		pattsPointer->addAssignLhs("x", 7);
		pattsPointer->addAssignRhs(7, "x+1");
		pattsPointer->addAssignLhs("x", 9);
		pattsPointer->addAssignRhs(9, "x+1");

		PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, usesPointer);
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

			THEN("For pattern query, the right result is returned") {
				list<string> expected = { "1", "3" };
				list<string> res;

				string query = "assign a1; stmt s2; Select a1 pattern a1 (_, _\"x\"_)";

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

			THEN("For combined query with 1 overlapping synonym, the right result is returned") {
				list<string> expected = { "x" };
				list<string> res;

				string query = "assign a1; variable v1; Select v1 such that Uses(_,v1) pattern a1 (v1, _)";

				qps.query(query, res);
				REQUIRE(res == expected);
			}
		}
	}
}
