#include "catch.hpp"
#include "SP/SourceProcessor.h"
#include "QPS/Qps.h"

SCENARIO("System testing between all components for Follows") {
    GIVEN("The initialization and population of the PKB related classes") {
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
        PrintAttribute printA;
        ReadAttribute readA;
        CallAttribute callA;
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
        std::shared_ptr<PrintAttribute> printAPointer = std::make_shared<PrintAttribute>(printA);
        std::shared_ptr<ReadAttribute> readAPointer = std::make_shared<ReadAttribute>(readA);
        std::shared_ptr<CallAttribute> callAPointer = std::make_shared<CallAttribute>(callA);
        std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);
        std::shared_ptr<CFGStore> cfgPointer = std::make_shared<CFGStore>(cfg);
        std::shared_ptr<ContainCallsStore> concallPointer = std::make_shared<ContainCallsStore>(concall);


        // PKB classes instantiation
        PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cstarsPointer, printAPointer, readAPointer, callAPointer, nextPointer, cfgPointer, concallPointer);
        PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cstarsPointer, printAPointer, readAPointer, callAPointer, nextPointer, cfgPointer, concallPointer);


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
            Qps qps(std::make_shared<PkbRetriever>(pkbRet));
            THEN("For selecting statement that follows a statement, the right result is returned") {
                list<string> expected = { "18" };
                list<string> res;

                string query = "stmt s;  Select s such that Follows(17,s)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting statement that follows a if statement, the right result is returned") {
                list<string> expected = { "11" };
                list<string> res;

                string query = "stmt s;  Select s such that Follows(2,s)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting statement that is within an if statement, the right result is returned") {
                list<string> expected = { "7" };
                list<string> res;

                string query = "stmt s;  Select s such that Follows(6,s)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting the last statement within an if statement, the right result is returned") {
                list<string> expected = {};
                list<string> res;

                string query = "stmt s;  Select s such that Follows(5,s)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting statement that follows a while statement, the right result is returned") {
                list<string> expected = { "17" };
                list<string> res;

                string query = "stmt s;  Select s such that Follows(11,s)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
        }
    }
}