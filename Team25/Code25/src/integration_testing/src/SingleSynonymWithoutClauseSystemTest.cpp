#include "catch.hpp"
#include "SP/SourceProcessor.h"
#include "QPS/Qps.h"

SCENARIO("System testing between all components for single synonym select") {
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
        std::shared_ptr<PrintAttribute> printAPointer = std::make_shared<PrintAttribute>(printAttr);
        std::shared_ptr<ReadAttribute> readAPointer = std::make_shared<ReadAttribute>(readAttr);
        std::shared_ptr<CallAttribute> callAPointer = std::make_shared<CallAttribute>(callAttr);
        std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);
        std::shared_ptr<CFGStore> cfgPointer = std::make_shared<CFGStore>(cfg);
        std::shared_ptr<ContainCallsStore> concallPointer = std::make_shared<ContainCallsStore>(concall);

        // PKB classes instantiation
        PkbPopulator pkbPop(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cstarsPointer, printAPointer, readAPointer, callAPointer, nextPointer, cfgPointer, concallPointer);
        PkbRetriever pkbRet(vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer, fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer, uprocsPointer, usesPointer, callsPointer, cstarsPointer, printAPointer, readAPointer, callAPointer, nextPointer, cfgPointer, concallPointer);

        WHEN("The SP and QPS objects are instantiated and a SIMPLE program is defined") {
            // Simulating SIMPLE program in temp file
            std::string fileLocation = "sample_source.txt";
            std::string fileInput = "procedure Example {\n"
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
                                    "  call n;\n"
                                    "  o = 3;\n"
                                    "  print p;\n"
                                    "}";
            std::ofstream file(fileLocation);
            file << fileInput;
            file.close();

            // SP and QPS components initialization
            SourceProcessor sp;
            sp.processSimple(fileLocation, std::make_shared<PkbPopulator>(pkbPop));
            Qps qps(std::make_shared<PkbRetriever>(pkbRet));
            THEN("For select all procedure, the right result is returned") {
                list<string> expected = { "Example"};
                list<string> res;

                string query = "procedure p;  Select p";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all variable, the right result is returned") {
                list<string> expected = { "a","b","c","d","e","f","g","h","i","j","k","l","m","o","p"};
                list<string> res;

                string query = "variable v;  Select v";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all constant query, the right result is returned") {
                list<string> expected = { "1","2","3" };
                list<string> res;

                string query = "constant c;  Select c";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all statement query, the right result is returned") {
                list<string> expected = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
                list<string> res;

                string query = "stmt s;  Select s";

                qps.query(query, res);
                res.sort();
                expected.sort();
                REQUIRE(res == expected);
            }
            THEN("For select all assign query, the right result is returned") {
                list<string> expected = { "1", "3", "4", "6", "9" };
                list<string> res;

                string query = "assign a;  Select a";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all call query, the right result is returned") {
                list<string> expected = { "8" };
                list<string> res;

                string query = "call c;  Select c";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all read query, the right result is returned") {
                list<string> expected = { "7" };
                list<string> res;

                string query = "read r;  Select r";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all print query, the right result is returned") {
                list<string> expected = { "10" };
                list<string> res;

                string query = "print p;  Select p";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all if query, the right result is returned") {
                list<string> expected = { "2" };
                list<string> res;

                string query = "if ifs;  Select ifs";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
            THEN("For select all if query, the right result is returned") {
                list<string> expected = { "5" };
                list<string> res;

                string query = "while wh;  Select wh";

                qps.query(query, res);
                REQUIRE(res == expected);
            }
        }
    }
}