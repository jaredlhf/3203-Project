#include "PKB/EntityStore.h"

#include "catch.hpp"

SCENARIO("Populating statement store") {
  GIVEN("New instance of statement store") {
    StatementStore stmtStore;

    THEN("It should start empty") { REQUIRE(stmtStore.size() == 0); }

    WHEN("One statement is addStmted") {
      stmtStore.addStmt("assign", 1);

      THEN("Store should have 1 key") {
        REQUIRE(stmtStore.size() == 1);
        REQUIRE(stmtStore.has("assign"));
      }

      THEN("Value for key should be correct") {
        REQUIRE(stmtStore.getAllStmt("assign") == std::unordered_set<int>({1}));
      }
    }
    WHEN("2 assign, 1 print, 1 read are addStmted") {
      stmtStore.addStmt("assign", 1);
      stmtStore.addStmt("assign", 2);
      stmtStore.addStmt("print", 3);
      stmtStore.addStmt("read", 4);

      THEN("Store should have 3 keys") {
        REQUIRE(stmtStore.size() == 3);
        REQUIRE(stmtStore.has("assign"));
        REQUIRE(stmtStore.has("print"));
        REQUIRE(stmtStore.has("read"));
      }

      THEN("Value for keys should be correct") {
        REQUIRE(stmtStore.getAllStmt("assign") ==
                std::unordered_set<int>({1, 2}));
        REQUIRE(stmtStore.getAllStmt("print") == std::unordered_set<int>({3}));
        REQUIRE(stmtStore.getAllStmt("read") == std::unordered_set<int>({4}));
      }
    }
  }
}