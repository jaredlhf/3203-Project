#include "catch.hpp"
#include "SP/SourceProcessor.h"
#include "QPS/Qps.h"

SCENARIO("System testing between all components for Parent*") {
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
        PrintAttribute printAttr;
        ReadAttribute readAttr;
        CallAttribute callAttr;
        NextStore next;

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
        std::shared_ptr<PrintAttribute> printAPointer = std::make_shared<PrintAttribute>(printAttr);
        std::shared_ptr<ReadAttribute> readAPointer = std::make_shared<ReadAttribute>(readAttr);
        std::shared_ptr<CallAttribute> callAPointer = std::make_shared<CallAttribute>(callAttr);
        std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);


        // PKB classes instantiation
        PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cstarsPointer, printAPointer, readAPointer, callAPointer, nextPointer);
        PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cstarsPointer, printAPointer, readAPointer, callAPointer, nextPointer);

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
                                                "  d = e+2;\n"
                                            "  }\n"
                                        "  }\n"
                                        "print a;\n"
                                    "  } else {\n"
                                        "  g = h+2;\n"
                                    "  }\n"
                                    "  while (i > j) {\n"
                                        "k = l;\n"
                                        "while (n > m) {\n"
                                            "o = p;\n"
                                            "while (x > y) {\n"
                                                "z = k;\n"
                                            "}\n"
                                        "}\n"
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
            Qps qps(std::make_shared<PkbRetriever>(pkbRet));
            THEN("For selecting a statement nested within a if container statement, the right result is returned") {
                list<string> expected = {  "2"  };
                list<string> res;

                string query = "stmt s;  Select s such that Parent*(s,3)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting a statement within 2 nested if container statement, the right result is returned") {
                list<string> expected = {  "2", "4"  };
                list<string> res;

                string query = "stmt s;  Select s such that Parent*(s,6)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting a statement within 3 nested if container statement, the right result is returned") {
                list<string> expected = {  "2", "4", "7"  };
                list<string> res;

                string query = "stmt s;  Select s such that Parent*(s,8)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting a statement within a while container statement, the right result is returned") {
                list<string> expected = {  "12"  };
                list<string> res;

                string query = "stmt s;  Select s such that Parent*(s,13)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting a statement within 2 nested while container statement, the right result is returned") {
                list<string> expected = {  "12", "14"  };
                list<string> res;

                string query = "stmt s;  Select s such that Parent*(s,15)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting a statement within 3 nested while container statement, the right result is returned") {
                list<string> expected = {  "12", "14", "16"  };
                list<string> res;

                string query = "stmt s;  Select s such that Parent*(s,17)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For selecting a statement that is the not in a container statement, the right result is returned") {
                list<string> expected = {};
                list<string> res;

                string query = "stmt s;  Select s such that Parent*(s,19)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
        }
    }
}
