#include "catch.hpp"
#include "SP/SourceProcessor.h"
#include "QPS/Qps.h"

bool compareString(const string& a, const string& b) {
    return stoi(a) < stoi(b);
}

SCENARIO("System testing between all components for Next") {
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
            Qps qps(std::make_shared<PkbRetriever>(pkbRet));
            THEN("Check that all pairs are populated") {
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

                REQUIRE(pkbRet.getRightNext(1) == s1);
                REQUIRE(pkbRet.getRightNext(2) == s2);
                REQUIRE(pkbRet.getRightNext(3) == s3);
                REQUIRE(pkbRet.getRightNext(4) == s4);
                REQUIRE(pkbRet.getRightNext(5) == s5);
                REQUIRE(pkbRet.getRightNext(6) == s6);
                REQUIRE(pkbRet.getRightNext(7) == s7);
                REQUIRE(pkbRet.getRightNext(8) == s8);
                REQUIRE(pkbRet.getRightNext(9) == s9);
                REQUIRE(pkbRet.getRightNext(10) == s10);
                REQUIRE(pkbRet.getRightNext(11) == s11);
                REQUIRE(pkbRet.getRightNext(12) == s12);
                REQUIRE(pkbRet.getRightNext(13) == s13);
                REQUIRE(pkbRet.getRightNext(14) == s14);
                REQUIRE(pkbRet.getRightNext(15) == s15);
                REQUIRE(pkbRet.getRightNext(16) == s16);
                REQUIRE(pkbRet.getRightNext(17) == s17);
                REQUIRE(pkbRet.getRightNext(18) == s18);
                REQUIRE(pkbRet.getRightNext(19) == s19);
                REQUIRE(pkbRet.getRightNext(20) == s20);

            }

            THEN("When selecting all statements that have a next statement, the right result is returned") {
                list<string> expected = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19"};
                list<string> res;

                string query = "stmt s; stmt s2; Select s such that Next(s,s2)";

                qps.query(query, res);
                res.sort(compareString);
                REQUIRE(res == expected);
            }

            THEN("When selecting all statements that have are a next statement, the right result is returned") {
                list<string> expected = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
                list<string> res;

                string query = "stmt s; stmt s2; Select s2 such that Next(s,s2)";

                qps.query(query, res);
                res.sort(compareString);
                REQUIRE(res == expected);
            }

        }
    }
}