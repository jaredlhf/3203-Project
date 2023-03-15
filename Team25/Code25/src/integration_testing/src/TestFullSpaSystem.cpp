#include "QPS/Qps.h"
#include "SP/SourceProcessor.h"
#include "catch.hpp"

SCENARIO("System testing between all components") {
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
    PrintAttribute prAtt;
    ReadAttribute readAtt;
    CallAttribute callAtt;
    NextStore next;

    std::shared_ptr<VariableStore> vsPointer =
        std::make_shared<VariableStore>(vs);
    std::shared_ptr<ConstantStore> csPointer =
        std::make_shared<ConstantStore>(cs);
    std::shared_ptr<FollowsStore> fsPointer =
        std::make_shared<FollowsStore>(fs);
    std::shared_ptr<ProcedureStore> psPointer =
        std::make_shared<ProcedureStore>(ps);
    std::shared_ptr<StatementStore> ssPointer =
        std::make_shared<StatementStore>(ss);
    std::shared_ptr<PatternStore> pattsPointer =
        std::make_shared<PatternStore>(patts);
    std::shared_ptr<FollowsStarStore> fstarsPointer =
        std::make_shared<FollowsStarStore>(fstars);
    std::shared_ptr<ModifiesProcStore> mprocsPointer =
        std::make_shared<ModifiesProcStore>(mprocs);
    std::shared_ptr<ModifiesStore> msPointer =
        std::make_shared<ModifiesStore>(ms);
    std::shared_ptr<ParentStarStore> pStarsPointer =
        std::make_shared<ParentStarStore>(pStars);
    std::shared_ptr<ParentStore> parentsPointer =
        std::make_shared<ParentStore>(parents);
    std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);
    std::shared_ptr<UsesProcStore> uprocsPointer =
        std::make_shared<UsesProcStore>(uprocs);
    std::shared_ptr<CallsStore> callsPointer =
        std::make_shared<CallsStore>(calls);
    std::shared_ptr<CallsStarStore> cstarsPointer =
        std::make_shared<CallsStarStore>(cstars);
    std::shared_ptr<PrintAttribute> printAttrStorage =
        std::make_shared<PrintAttribute>(prAtt);
    std::shared_ptr<ReadAttribute> readAttrStorage =
        std::make_shared<ReadAttribute>(readAtt);
    std::shared_ptr<CallAttribute> callAttrStorage =
        std::make_shared<CallAttribute>(callAtt);
    std::shared_ptr<NextStore> nextPointer = std::make_shared<NextStore>(next);

    // PKB classes instantiation
    PkbPopulator pkbPop(
        vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer,
        fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer,
        uprocsPointer, usesPointer, callsPointer, cstarsPointer,
        printAttrStorage, readAttrStorage, callAttrStorage, nextPointer);
    PkbRetriever pkbRet(
        vsPointer, csPointer, fsPointer, psPointer, ssPointer, pattsPointer,
        fstarsPointer, mprocsPointer, msPointer, pStarsPointer, parentsPointer,
        uprocsPointer, usesPointer, callsPointer, cstarsPointer,
        printAttrStorage, readAttrStorage, callAttrStorage, nextPointer);

    WHEN("The SP and QPS objects are instantiated and a SIMPLE program is "
         "defined") {
      // Simulating SIMPLE program in temp file
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

      // SP and QPS components initialization
      SourceProcessor sp;
      sp.processSimple(fileLocation, std::make_shared<PkbPopulator>(pkbPop));
      Qps qps(std::make_shared<PkbRetriever>(pkbRet));

      THEN("For follows* query, the right result is returned") {
        list<string> expected = {"1", "3", "9"};
        list<string> res;

        string query =
            "assign a1; stmt s2; Select a1 such that Follows*(a1, s2)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For parent* query, the right result is returned") {
        list<string> expected = {"6"};
        list<string> res;

        string query = "while w1; Select w1 such that Parent*(2, 4)";

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
        list<string> expected = {"2"};
        list<string> res;

        string query = "if ifs; Select ifs such that Parent(ifs, _)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For follows query, the right result is returned") {
        list<string> expected = {"1", "10", "2", "3", "4",
                                 "5", "6",  "7", "8", "9"};
        list<string> res;

        string query = "stmt stmt; Select stmt such that Follows(_, _)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For uses query, the right result is returned") {
        list<string> expected = {"1", "6", "7"};
        list<string> res;

        string query = "stmt s1; Select s1 such that Uses(s1, \"d\")";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For follows* query in the form (s1, _), the right result is "
           "returned") {
        list<string> expected = {"1", "2", "3", "6", "8", "9"};
        list<string> res;

        string query = "stmt s1; Select s1 such that Follows*(s1, _)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For modifies query in the form (s1, 'y'), the right result is "
           "returned") {
        list<string> expected = {"2", "3"};
        list<string> res;

        string query = "stmt stmt; Select stmt such that Modifies(stmt, \"y\")";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN(
          "For uses query in the form (1, 'y'), the right result is returned") {
        list<string> expected = {"6"};
        list<string> res;

        string query = "while Uses; Select Uses such that Uses(6, \"d\")";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For follows query in the form (1, s2), the right result is "
           "returned") {
        list<string> expected = {"2"};
        list<string> res;

        string query = "stmt s2; Select s2 such that Follows(1, s2)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For pattern query in the form (_, 'd'), the right result is "
           "returned") {
        list<string> expected = {"1", "7"};
        list<string> res;

        string query = "assign a1; stmt s2; Select a1 pattern a1 (_, _\"d\"_)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For pattern query in the form (_, _), the right result is "
           "returned") {
        list<string> expected = {"1", "10", "3", "4", "5", "7", "9"};
        list<string> res;

        string query = "assign a1; stmt s2; Select a1 pattern a1 (_, _)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For pattern query in the form (v1, _), the right result is "
           "returned") {
        list<string> expected = {"U", "W", "f1", "h", "i", "x", "y"};
        list<string> res;

        string query = "assign a1; variable v1; Select v1 pattern a1 (v1, _)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For pattern query in the form (v1, _'y'_), the right result is "
           "returned") {
        list<string> expected = {"f1"};
        list<string> res;

        string query =
            "assign a1; variable v1; Select v1 pattern a1 (v1, _\"h3\"_)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For pattern query in the form ('x', _), the right result is "
           "returned") {
        list<string> expected = {"1"};
        list<string> res;

        string query =
            "assign a1; variable v1; Select a1 pattern a1 (\"x\", _)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For pattern query in the form ('x', _'y'_), the right result is "
           "returned") {
        list<string> expected = {"9"};
        list<string> res;

        string query = "assign Select; variable v1; Select Select pattern "
                       "Select (\"h\", _\"232141\"_)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For pattern query with var syn in pattern clause, the right result "
           "is returned") {
        list<string> expected = {"1", "7"};
        list<string> res;

        string query =
            "assign a1; variable v1; Select a1 pattern a1 (v1, _\"d\"_)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For combined query, the right result is returned") {
        list<string> expected = {"U", "W", "f1", "h", "i", "x", "y"};
        list<string> res;

        string query = "assign a1; variable v1; Select v1 such that "
                       "Parent(2,3) pattern a1 (v1, _)";

        qps.query(query, res);
        REQUIRE(res == expected);
      }

      THEN("For combined query with 1 overlapping synonym, the right result is "
           "returned") {
        list<string> expected = {"7"};
        list<string> res;

        string query = "assign a1; variable v1; stmt s1; Select a1 such that "
                       "Modifies(a1, \"U\") pattern a1(_, _\"d\"_) ";

        qps.query(query, res);
        REQUIRE(res == expected);
      }
    }
  }
}