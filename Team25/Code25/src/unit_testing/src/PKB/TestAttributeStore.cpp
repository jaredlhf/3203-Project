#include "PKB/AttributeStore.h"

#include "catch.hpp"

SCENARIO("Populating attribute stores") {
  GIVEN("New instances of print, read, call attributes") {

    PrintAttribute printA;
    ReadAttribute readA;
    CallAttribute callA;

    THEN("They should start empty") {
      REQUIRE(printA.getAllAttr().size() == 0);
      REQUIRE(readA.getAllAttr().size() == 0);
      REQUIRE(callA.getAllAttr().size() == 0);
      REQUIRE(printA.getAllStmt().size() == 0);
      REQUIRE(readA.getAllStmt().size() == 0);
      REQUIRE(callA.getAllStmt().size() == 0);
    }

    WHEN("One value is added to them") {
      printA.addAttr("x", 1);
      readA.addAttr("y", 2);
      callA.addAttr("sampleProc", 3);

      THEN("print attribute store should return correct values") {
        REQUIRE(printA.getAttr(1) == "x");
        REQUIRE(printA.getStmt("x") == std::unordered_set<int>({1}));
      }

      THEN("read attribute store should return correct values") {
        REQUIRE(readA.getAttr(2) == "y");
        REQUIRE(readA.getStmt("y") == std::unordered_set<int>({2}));
      }

      THEN("call attribute store should return correct values") {
        REQUIRE(callA.getAttr(3) == "sampleProc");
        REQUIRE(callA.getStmt("sampleProc") == std::unordered_set<int>({3}));
      }
    }

    WHEN("Two values are added to them") {
      printA.addAttr("x", 1);
      printA.addAttr("x", 4);
      readA.addAttr("y", 2);
      readA.addAttr("y", 5);
      callA.addAttr("sampleProc", 3);
      callA.addAttr("sampleProc", 6);

      THEN("print attribute store should return correct values") {
        REQUIRE(printA.getAttr(1) == "x");
        REQUIRE(printA.getStmt("x") == std::unordered_set<int>({1, 4}));
      }

      THEN("read attribute store should return correct values") {
        REQUIRE(readA.getAttr(2) == "y");
        REQUIRE(readA.getStmt("y") == std::unordered_set<int>({2, 5}));
      }

      THEN("call attribute store should return correct values") {
        REQUIRE(callA.getAttr(3) == "sampleProc");
        REQUIRE(callA.getStmt("sampleProc") == std::unordered_set<int>({3, 6}));
      }

      WHEN("Non-existent value is retrieved") {
        THEN("print get methods should return empty") {
          REQUIRE(printA.getAttr(2) == std::string());
          REQUIRE(printA.getStmt("z") == std::unordered_set<int>());
        }

        THEN("read get methods should return empty") {
          REQUIRE(readA.getAttr(3) == std::string());
          REQUIRE(readA.getStmt("z") == std::unordered_set<int>());
        }

        THEN("call get methods should return empty") {
          REQUIRE(callA.getAttr(4) == std::string());
          REQUIRE(callA.getStmt("z") == std::unordered_set<int>());
        }
      }
    }
  }
}
