#include "catch.hpp"
#include "SP/SourceProcessor.h"

SCENARIO("Integration testing between SP and PKB") {
	GIVEN("The initialization of the SP with the PKB") {
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
		SourceProcessor sp;

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

		PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, usesPointer);
		WHEN("Given a SIMPLE program") {
			std::string fileLocation = "sample_source.txt";

			std::string fileInput = "procedure Example {\n"
				"  x = 2+d;\n"
				"  if (a < b) then {\n"
				"    y = z;\n"
				"    i = j + k;\n"
				"  } else {\n"
				"    W = n;\n"
				"  }\n"
				"  while (c > d) {\n"
				"    U = o + p + d;\n"
				"  }\n"
				"  read z;\n"
				"  h = 232141;\n"
				"  f1 = h3;\n"
				"}";
			std::ofstream file(fileLocation);
			file << fileInput;
			file.close();
			sp.processSimple(fileLocation, std::make_shared<PkbPopulator>(pkbPop));
			THEN("PKB variable store should contain the correct variables") {
				REQUIRE(vsPointer->size() == 18);
				REQUIRE(vsPointer->getAll().count("x") == 1);
				REQUIRE(vsPointer->getAll().count("d") == 1);
				REQUIRE(vsPointer->getAll().count("a") == 1);
				REQUIRE(vsPointer->getAll().count("b") == 1);
				REQUIRE(vsPointer->getAll().count("y") == 1);
				REQUIRE(vsPointer->getAll().count("z") == 1);
				REQUIRE(vsPointer->getAll().count("i") == 1);
				REQUIRE(vsPointer->getAll().count("j") == 1);
				REQUIRE(vsPointer->getAll().count("k") == 1);
				REQUIRE(vsPointer->getAll().count("W") == 1);
				REQUIRE(vsPointer->getAll().count("n") == 1);
				REQUIRE(vsPointer->getAll().count("c") == 1);
				REQUIRE(vsPointer->getAll().count("U") == 1);
				REQUIRE(vsPointer->getAll().count("o") == 1);
				REQUIRE(vsPointer->getAll().count("p") == 1);
				REQUIRE(vsPointer->getAll().count("z") == 1);
				REQUIRE(vsPointer->getAll().count("h") == 1);
				REQUIRE(vsPointer->getAll().count("f1") == 1);
				REQUIRE(vsPointer->getAll().count("h3") == 1);
			}
			THEN("PKB constants store should contain the correct constants") {
				REQUIRE(csPointer->size() == 2);
				REQUIRE(csPointer->getAll().count(2) == 1);
				REQUIRE(csPointer->getAll().count(232141) == 1);
			}
			THEN("PKB follows store should contain the correct follows") {
				REQUIRE(fsPointer->getAllFollowers().size() == 6);
				REQUIRE(fsPointer->getAllFollowees().size() == 6);
			}
			THEN("PKB statment store should contain the correct statement") {
				REQUIRE(ssPointer->getAllStmt("assign").size() == 7);
				REQUIRE(ssPointer->getAllStmt("if").size() == 1);
				REQUIRE(ssPointer->getAllStmt("while").size() == 1);
				REQUIRE(ssPointer->getAllStmt("read").size() == 1);
			}
			THEN("PKB pattern store should contain the correct pattern statements") {
				REQUIRE(pattsPointer->LhsAssignStoreSize() == 7);
				REQUIRE(pattsPointer->RhsAssignStoreSize() == 9);
			}
			THEN("PKB follows star store should contain the follows star statements") {
				REQUIRE(fstarsPointer->getAllFollowers().size() == 6);
				REQUIRE(fstarsPointer->getAllFollowees().size() == 6);
			}
			THEN("PKB modifies store should contain the modifies relationships") {
				REQUIRE(msPointer->getAllVar().size() == 8);
				REQUIRE(msPointer->getAllStmt().size() == 10);
			}
			THEN("PKB parent star store should contain the parent star relationships") {
				REQUIRE(pStarsPointer->getAllParents().size() == 2);
				REQUIRE(pStarsPointer->getAllChildren().size() == 4);
			}
			THEN("PKB parent star store should contain the parent star relationships") {
				REQUIRE(parentsPointer->getAllParents().size() == 2);
				REQUIRE(parentsPointer->getAllChildren().size() == 4);
			}
			THEN("PKB uses store should contain the uses relationships") {
				REQUIRE(usesPointer->getAllVar().size() == 11);
				REQUIRE(usesPointer->getAllStmt().size() == 8);
			}
		}
	}
}