#include "catch.hpp"
#include "SP/SourceProcessor.h"

SCENARIO("Integration testing between SP and PKB") {
	GIVEN("The initialization of the SP with the PKB") {
        SourceProcessor sp;
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
        CallsStarStore cstars;
        PrintAttribute prAtt;
        ReadAttribute readAtt;
        CallAttribute callAtt;
		NextStore next;
		CFGStore cfg;
		ContainCallsStore concall;


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
        std::shared_ptr<UsesProcStore> uprocsPointer = std::make_shared<UsesProcStore>(uprocs);
        std::shared_ptr<CallsStore> callsPointer = std::make_shared<CallsStore>(calls);
        std::shared_ptr<CallsStarStore> cstarsPointer = std::make_shared<CallsStarStore>(cstars);
        std::shared_ptr<PrintAttribute> printAPointer = std::make_shared<PrintAttribute>(prAtt);
        std::shared_ptr<ReadAttribute> readAPointer = std::make_shared<ReadAttribute>(readAtt);
        std::shared_ptr<CallAttribute> callAPointer = std::make_shared<CallAttribute>(callAtt);
		std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);
		std::shared_ptr<CFGStore> cfgPointer = std::make_shared<CFGStore>(cfg);
		std::shared_ptr<ContainCallsStore> concallPointer = std::make_shared<ContainCallsStore>(concall);


        PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cstarsPointer, printAPointer, readAPointer, callAPointer, nextPointer, cfgPointer, concallPointer);
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
				REQUIRE(vsPointer->getAllVar().size() == 18);
				REQUIRE(vsPointer->getAllVar().count("x") == 1);
				REQUIRE(vsPointer->getAllVar().count("d") == 1);
				REQUIRE(vsPointer->getAllVar().count("a") == 1);
				REQUIRE(vsPointer->getAllVar().count("b") == 1);
				REQUIRE(vsPointer->getAllVar().count("y") == 1);
				REQUIRE(vsPointer->getAllVar().count("z") == 1);
				REQUIRE(vsPointer->getAllVar().count("i") == 1);
				REQUIRE(vsPointer->getAllVar().count("j") == 1);
				REQUIRE(vsPointer->getAllVar().count("k") == 1);
				REQUIRE(vsPointer->getAllVar().count("W") == 1);
				REQUIRE(vsPointer->getAllVar().count("n") == 1);
				REQUIRE(vsPointer->getAllVar().count("c") == 1);
				REQUIRE(vsPointer->getAllVar().count("U") == 1);
				REQUIRE(vsPointer->getAllVar().count("o") == 1);
				REQUIRE(vsPointer->getAllVar().count("p") == 1);
				REQUIRE(vsPointer->getAllVar().count("z") == 1);
				REQUIRE(vsPointer->getAllVar().count("h") == 1);
				REQUIRE(vsPointer->getAllVar().count("f1") == 1);
				REQUIRE(vsPointer->getAllVar().count("h3") == 1);
			}
			THEN("PKB constants store should contain the correct constants") {
				REQUIRE(csPointer->getAllConst().size() == 2);
				REQUIRE(csPointer->getAllConst().count(2) == 1);
				REQUIRE(csPointer->getAllConst().count(232141) == 1);
			}
			THEN("PKB follows store should contain the correct follows") {
				REQUIRE(fsPointer->getAllRight().size() == 6);
				REQUIRE(fsPointer->getAllLeft().size() == 6);
			}
			THEN("PKB statment store should contain the correct statement") {
				REQUIRE(ssPointer->getAllStmt("assign").size() == 7);
				REQUIRE(ssPointer->getAllStmt("if").size() == 1);
				REQUIRE(ssPointer->getAllStmt("while").size() == 1);
				REQUIRE(ssPointer->getAllStmt("read").size() == 1);
			}
			THEN("PKB pattern store should contain the correct pattern statements") {
				REQUIRE(pattsPointer->LhsAssignStoreSize() == 7);
				REQUIRE(pattsPointer->RhsAssignStoreSize() == 7);
			}
			THEN("PKB follows star store should contain the follows star statements") {
				REQUIRE(fstarsPointer->getAllRight().size() == 6);
				REQUIRE(fstarsPointer->getAllLeft().size() == 6);
			}
			THEN("PKB modifies store should contain the modifies relationships") {
				REQUIRE(msPointer->getAllVar().size() == 8);
				REQUIRE(msPointer->getAllStmt().size() == 10);
			}
			THEN("PKB parent star store should contain the parent star relationships") {
				REQUIRE(pStarsPointer->getAllLeft().size() == 2);
				REQUIRE(pStarsPointer->getAllRight().size() == 4);
			}
			THEN("PKB parent star store should contain the parent star relationships") {
				REQUIRE(parentsPointer->getAllLeft().size() == 2);
				REQUIRE(parentsPointer->getAllRight().size() == 4);
			}
			THEN("PKB uses store should contain the uses relationships") {
				REQUIRE(usesPointer->getAllVar().size() == 11);
				REQUIRE(usesPointer->getAllStmt().size() == 8);
			}
		}

        WHEN("The SP and QPS objects are instantiated and a SIMPLE program is defined") {
            // Simulating SIMPLE program in temp file
            std::string fileLocation = "sample_source.txt";
            std::string fileInput = "procedure Alpha {\n"
                                    "  a = 1+b;\n"
                                    "  if (c < d) then {\n"
                                    "  e = f;\n"
                                    "  if (ab < cd) then {\n"
                                    "  print c;\n"
                                    "  } else {\n"
                                    "  d = e+2;\n"
                                    "  if (ab < cd) then {\n"
                                    "  print c;\n"
                                    "  } else {\n"
                                    "    d = e+2;\n"
                                    "  }\n"
                                    "  }\n"
                                    "print a;\n"
                                    "  } else {\n"
                                    "    g = h+2;\n"
                                    "  }\n"
                                    "  while (i > j) {\n"
                                    "    k = l;\n"
                                    "  while (n > m) {\n"
                                    "    o = p;\n"
                                    "  while (x > y) {\n"
                                    "    z = k;\n"
                                    "  }\n"
                                    "  }\n"
                                    "print z;\n"
                                    "  }\n"
                                    "print a;\n"
                                    "print b;\n"
                                    "}";
            std::ofstream file(fileLocation);
            file << fileInput;
            file.close();

            // SP and QPS components initialization
            SourceProcessor sp;
            sp.processSimple(fileLocation, std::make_shared<PkbPopulator>(pkbPop));
            THEN("Check that all Next relationship pairs are populated") {
                std::unordered_set<int> s1 = {2};
                std::unordered_set<int> s2 = {3, 11};
                std::unordered_set<int> s3 = {4};
                std::unordered_set<int> s4 = {5, 6};
                std::unordered_set<int> s5 = {10};
                std::unordered_set<int> s6 = {7};
                std::unordered_set<int> s7 = {8, 9};
                std::unordered_set<int> s8 = {10};
                std::unordered_set<int> s9 = {10};
                std::unordered_set<int> s10 = {12};
                std::unordered_set<int> s11 = {12};
                std::unordered_set<int> s12 = {13, 19};
                std::unordered_set<int> s13 = {14};
                std::unordered_set<int> s14 = {15, 18};
                std::unordered_set<int> s15 = {16};
                std::unordered_set<int> s16 = {14, 17};
                std::unordered_set<int> s17 = {16};
                std::unordered_set<int> s18 = {12};
                std::unordered_set<int> s19 = {20};
                std::unordered_set<int> s20 = {};

                REQUIRE(nextPointer->getRightStmt(1) == s1);
                REQUIRE(nextPointer->getRightStmt(2) == s2);
                REQUIRE(nextPointer->getRightStmt(3) == s3);
                REQUIRE(nextPointer->getRightStmt(4) == s4);
                REQUIRE(nextPointer->getRightStmt(5) == s5);
                REQUIRE(nextPointer->getRightStmt(6) == s6);
                REQUIRE(nextPointer->getRightStmt(7) == s7);
                REQUIRE(nextPointer->getRightStmt(8) == s8);
                REQUIRE(nextPointer->getRightStmt(9) == s9);
                REQUIRE(nextPointer->getRightStmt(10) == s10);
                REQUIRE(nextPointer->getRightStmt(11) == s11);
                REQUIRE(nextPointer->getRightStmt(12) == s12);
                REQUIRE(nextPointer->getRightStmt(13) == s13);
                REQUIRE(nextPointer->getRightStmt(14) == s14);
                REQUIRE(nextPointer->getRightStmt(15) == s15);
                REQUIRE(nextPointer->getRightStmt(16) == s16);
                REQUIRE(nextPointer->getRightStmt(17) == s17);
                REQUIRE(nextPointer->getRightStmt(18) == s18);
                REQUIRE(nextPointer->getRightStmt(19) == s19);
                REQUIRE(nextPointer->getRightStmt(20) == s20);

            }
        }
	}
}