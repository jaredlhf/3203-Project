#include "PKB/CallsStore.h"

#include "catch.hpp"

SCENARIO("Populating calls store") {
  GIVEN("New instance of calls store") {
    CallsStore callsStore;

    THEN("It should start empty") {
      REQUIRE(callsStore.getAllRight().size() == 0);
      REQUIRE(callsStore.getAllLeft().size() == 0);
    }

    WHEN("One calls is added") {
      callsStore.addCalls("proc1", "proc2");

      THEN("Left call should be mapped to right call") {
        REQUIRE(callsStore.getLeftProc("proc2") ==
                std::unordered_set<std::string>({"proc1"}));
        REQUIRE(callsStore.getRightProc("proc1") ==
                std::unordered_set<std::string>({"proc2"}));
      }

      WHEN("Duplicate calls is added") {
        callsStore.addCalls("proc1", "proc2");

        THEN("Calls relation should remain the same") {
          REQUIRE(callsStore.getLeftProc("proc2") ==
                  std::unordered_set<std::string>({"proc1"}));
          REQUIRE(callsStore.getRightProc("proc1") ==
                  std::unordered_set<std::string>({"proc2"}));
        }
      }

      WHEN("New calls is added to existing relation") {
        callsStore.addCalls("proc1", "proc3");

        THEN("Calls should have two relations") {
          REQUIRE(callsStore.getLeftProc("proc2") ==
                  std::unordered_set<std::string>({"proc1"}));
          REQUIRE(callsStore.getLeftProc("proc3") ==
                  std::unordered_set<std::string>({"proc1"}));
          REQUIRE(callsStore.getRightProc("proc1") ==
                  std::unordered_set<std::string>({"proc2", "proc3"}));
        }
      }
    }
    WHEN("Two calls are added") {
      callsStore.addCalls("proc1", "proc2");
      callsStore.addCalls("proc2", "proc3");

      THEN("Left calls should be mapped to right calls correctly") {
        REQUIRE(callsStore.getLeftProc("proc2") ==
                std::unordered_set<std::string>({"proc1"}));
        REQUIRE(callsStore.getRightProc("proc1") ==
                std::unordered_set<std::string>({"proc2"}));
        REQUIRE(callsStore.getLeftProc("proc3") ==
                std::unordered_set<std::string>({"proc2"}));
        REQUIRE(callsStore.getRightProc("proc2") ==
                std::unordered_set<std::string>({"proc3"}));
      }

      THEN("getAllRight method should return all right calls") {
        REQUIRE(callsStore.getAllRight() ==
                std::unordered_set<std::string>({"proc2", "proc3"}));
      }

      THEN("getAllLeft method should return all left calls") {
        REQUIRE(callsStore.getAllLeft() ==
                std::unordered_set<std::string>({"proc1", "proc2"}));
      }
    }
  }
}