#include "PKB/UsesProcStore.h"

#include "catch.hpp"

SCENARIO("Populating uses procedure store") {
  GIVEN("New instance of uses procedure store") {
    UsesProcStore uprocStore;

    THEN("It should start empty") {
      REQUIRE(uprocStore.getAllProc().size() == 0);
      REQUIRE(uprocStore.getAllVar().size() == 0);
    }

    WHEN("One usesProc is added") {
      uprocStore.addUsesProc("sampleProc", "x");

      THEN("Procedure should be mapped to variable") {
        REQUIRE(uprocStore.getProc("x") ==
                std::unordered_set<std::string>({"sampleProc"}));
        REQUIRE(uprocStore.getVar("sampleProc") ==
                std::unordered_set<std::string>({"x"}));
      }

      WHEN("Duplicate usesProc is added") {
        uprocStore.addUsesProc("sampleProc", "x");

        THEN("UsesProc store should remain the same") {
          REQUIRE(uprocStore.getProc("x") ==
                  std::unordered_set<std::string>({"sampleProc"}));
          REQUIRE(uprocStore.getVar("sampleProc") ==
                  std::unordered_set<std::string>({"x"}));
        }
      }
    }

    WHEN("Three usesProc are added") {
      uprocStore.addUsesProc("proc1", "x");
      uprocStore.addUsesProc("proc2", "x");
      uprocStore.addUsesProc("proc3", "y");

      THEN("There should be 3 procedures and 2 variables") {
        REQUIRE(uprocStore.getAllProc() ==
                std::unordered_set<std::string>({"proc1", "proc2", "proc3"}));
        REQUIRE(uprocStore.getAllVar() ==
                std::unordered_set<std::string>({"x", "y"}));
      }

      THEN("Procedures should be mapped to variables correctly") {
        REQUIRE(uprocStore.getProc("x") ==
                std::unordered_set<std::string>({"proc1", "proc2"}));
        REQUIRE(uprocStore.getProc("y") ==
                std::unordered_set<std::string>({"proc3"}));
        REQUIRE(uprocStore.getVar("proc1") ==
                std::unordered_set<std::string>({"x"}));
        REQUIRE(uprocStore.getVar("proc2") ==
                std::unordered_set<std::string>({"x"}));
        REQUIRE(uprocStore.getVar("proc3") ==
                std::unordered_set<std::string>({"y"}));
      }
    }
  }
}
