#include "catch.hpp"
#include "SP/SourceProcessor.h"
#include "QPS/Qps.h"

SCENARIO("System testing between all components for Modifies") {
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
        NextStore next;
        PrintAttribute printAttr;
        ReadAttribute readAttr;
        CallAttribute callAttr;
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
        std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);
        std::shared_ptr<PrintAttribute> printAPointer = std::make_shared<PrintAttribute>(printAttr);
        std::shared_ptr<ReadAttribute> readAPointer = std::make_shared<ReadAttribute>(readAttr);
        std::shared_ptr<CallAttribute> callAPointer = std::make_shared<CallAttribute>(callAttr);
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
                                    "    e = f;\n"
                                    "  } else {\n"
                                    "    g = h+2;\n"
                                    "  }\n"
                                    "  while (i > j) {\n"
                                    "    k = l;\n"
                                    "  }\n"
                                    "  read m;\n"
                                    "  call Beta;\n"
                                    "  o = 3;\n"
                                    "  print p;\n"
                                    "}"
                                    "procedure Beta {\n"
                                    "  ab = 1;\n"
                                    "  if (cd < 2) then {\n"
                                    "    ef = 3;\n"
                                    "  } else {\n"
                                    "    fg = 4;\n"
                                    "  }\n"
                                    "  while (hi > j) {\n"
                                    "    hi = j;\n"
                                    "    om = 3;\n"
                                    "  }\n"
                                    "  read mn;\n"
                                    "  op = 3;\n"
                                    "  print op;\n"
                                    "}";
            std::ofstream file(fileLocation);
            file << fileInput;
            file.close();

            // SP and QPS components initialization
            SourceProcessor sp;
            sp.processSimple(fileLocation, std::make_shared<PkbPopulator>(pkbPop));
            Qps qps(std::make_shared<PkbRetriever>(pkbRet));
            THEN("For select all modified variables in one procedure, the right result is returned") {
                list<string> expected = { "a", "e", "g", "k", "m", "o" };
                list<string> res;

                string query = "variable v;  Select v such that Modifies(\"Alpha\",v)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all modified variables in all procedures, the right result is returned") {
                list<string> expected = { "a", "ab", "e", "ef", "fg", "g", "hi", "k", "m", "mn", "o", "om", "op" };
                list<string> res;

                string query = "procedure p; variable v;  Select v such that Modifies(p,v)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select modified variable on a specific line, the right result is returned") {
                list<string> expected = { "a" };
                list<string> res;

                string query = " variable v;  Select v such that Modifies(1,v)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select line where variable is modified , the right result is returned") {
                list<string> expected = { "19" };
                list<string> res;

                string query = " stmt s;  Select s such that Modifies(s,\"op\")";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select modified variables by if container statement, the right result is returned") {
                list<string> expected = { "e", "g" };
                list<string> res;

                string query = " variable v;  Select v  such that Modifies(2,v)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select modified variables by while container statement, the right result is returned") {
                list<string> expected = { "hi", "om" };
                list<string> res;

                string query = " variable v;  Select v  such that Modifies(15,v)";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
        }
    }
}