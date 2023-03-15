#include "PKB/CallsStarStore.h"

#include "catch.hpp"

SCENARIO("Populating calls star store") {
  GIVEN("New instance of calls star store") {
    CallsStarStore callsStar;

    THEN("It should start empty") {
      REQUIRE(callsStar.getAllLeft().size() == 0);
      REQUIRE(callsStar.getAllRight().size() == 0);
    }

    WHEN("One calls star is added") {
      callsStar.addCallsStar("proc1", "proc2");
      callsStar.addCallsStar("proc1", "proc3");
      callsStar.addCallsStar("proc1", "proc4");

      THEN("Left call should be mapped to right calls") {
        REQUIRE(callsStar.getRightStar("proc1") ==
                std::unordered_set<std::string>({"proc2", "proc3", "proc4"}));
        REQUIRE(callsStar.getLeftStar("proc2") ==
                std::unordered_set<std::string>({"proc1"}));
        REQUIRE(callsStar.getLeftStar("proc3") ==
                std::unordered_set<std::string>({"proc1"}));
        REQUIRE(callsStar.getLeftStar("proc4") ==
                std::unordered_set<std::string>({"proc1"}));
      }

      WHEN("Duplicate calls star is added") {
        callsStar.addCallsStar("proc1", "proc2");
        callsStar.addCallsStar("proc1", "proc3");
        callsStar.addCallsStar("proc1", "proc4");

        THEN("Calls star store should remain the same") {
          REQUIRE(callsStar.getRightStar("proc1") ==
                  std::unordered_set<std::string>({"proc2", "proc3", "proc4"}));
          REQUIRE(callsStar.getLeftStar("proc2") ==
                  std::unordered_set<std::string>({"proc1"}));
          REQUIRE(callsStar.getLeftStar("proc3") ==
                  std::unordered_set<std::string>({"proc1"}));
          REQUIRE(callsStar.getLeftStar("proc4") ==
                  std::unordered_set<std::string>({"proc1"}));
        }
      }
    }

    WHEN("Three calls star is added") {
      callsStar.addCallsStar("proc1", "proc2");
      callsStar.addCallsStar("proc1", "proc3");
      callsStar.addCallsStar("proc1", "proc4");
      callsStar.addCallsStar("proc2", "proc3");
      callsStar.addCallsStar("proc2", "proc4");
      callsStar.addCallsStar("proc3", "proc4");

      THEN("There should be 3 left calls and 3 right calls") {
        REQUIRE(callsStar.getAllLeft() ==
                std::unordered_set<std::string>({"proc1", "proc2", "proc3"}));
        REQUIRE(callsStar.getAllRight() ==
                std::unordered_set<std::string>({"proc2", "proc3", "proc4"}));
      }

      THEN("Left calls and right calls should be mapped correctly") {
        REQUIRE(callsStar.getRightStar("proc1") ==
                std::unordered_set<std::string>({"proc2", "proc3", "proc4"}));
        REQUIRE(callsStar.getRightStar("proc2") ==
                std::unordered_set<std::string>({"proc3", "proc4"}));
        REQUIRE(callsStar.getRightStar("proc3") ==
                std::unordered_set<std::string>({"proc4"}));

        REQUIRE(callsStar.getLeftStar("proc2") ==
                std::unordered_set<std::string>({"proc1"}));
        REQUIRE(callsStar.getLeftStar("proc3") ==
                std::unordered_set<std::string>({"proc1", "proc2"}));
        REQUIRE(callsStar.getLeftStar("proc4") ==
                std::unordered_set<std::string>({"proc1", "proc2", "proc3"}));
      }
    }
  }
}
