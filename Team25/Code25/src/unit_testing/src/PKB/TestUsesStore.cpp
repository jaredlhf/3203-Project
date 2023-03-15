#include "PKB/UsesStore.h"

#include "catch.hpp"

SCENARIO("Populating uses store") {
  GIVEN("New instance of uses store") {
    UsesStore usesStore;

    THEN("It should start empty") {
      REQUIRE(usesStore.getAllStmt().size() == 0);
      REQUIRE(usesStore.getAllVar().size() == 0);
    }

    WHEN("One uses is added") {
      usesStore.addUses(1, "x");

      THEN("Statement should be mapped to variable") {
        REQUIRE(usesStore.getStmt("x") == std::unordered_set<int>({1}));
        REQUIRE(usesStore.getVar(1) == std::unordered_set<std::string>({"x"}));
      }

      WHEN("Duplicate uses is added") {
        usesStore.addUses(1, "x");

        THEN("Uses store should remain the same") {
          REQUIRE(usesStore.getStmt("x") == std::unordered_set<int>({1}));
          REQUIRE(usesStore.getVar(1) ==
                  std::unordered_set<std::string>({"x"}));
        }
      }
    }

    WHEN("Four uses are added") {
      usesStore.addUses(2, "x");
      usesStore.addUses(2, "y");
      usesStore.addUses(3, "v");
      usesStore.addUses(3, "x");

      THEN("There should be 2 statements and 3 variables") {
        REQUIRE(usesStore.getAllStmt() == std::unordered_set<int>({2, 3}));
        REQUIRE(usesStore.getAllVar() ==
                std::unordered_set<std::string>({"x", "y", "v"}));
      }

      THEN("Statements should be mapped to variables correctly") {
        REQUIRE(usesStore.getStmt("x") == std::unordered_set<int>({2, 3}));
        REQUIRE(usesStore.getStmt("y") == std::unordered_set<int>({2}));
        REQUIRE(usesStore.getStmt("v") == std::unordered_set<int>({3}));
        REQUIRE(usesStore.getVar(2) ==
                std::unordered_set<std::string>({"x", "y"}));
        REQUIRE(usesStore.getVar(3) ==
                std::unordered_set<std::string>({"v", "x"}));
      }
    }
  }
}
