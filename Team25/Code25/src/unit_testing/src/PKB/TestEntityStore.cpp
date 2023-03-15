#include "PKB/EntityStore.h"

#include "catch.hpp"

SCENARIO("Populating stores for constants, procedures, and variables") {
  GIVEN("New instances of constant store, procedure store, variable store") {

    ConstantStore constStore;
    ProcedureStore procStore;
    VariableStore varStore;

    THEN("They should start empty") {
      REQUIRE(constStore.getAllConst().size() == 0);
      REQUIRE(procStore.getAllProc().size() == 0);
      REQUIRE(varStore.getAllVar().size() == 0);
    }

    WHEN("One value is added to them") {
      constStore.addConst(1);
      procStore.addProc("proc");
      varStore.addVar("one");

      THEN("Their size should increase by 1") {
        REQUIRE(constStore.getAllConst().size() == 1);
        REQUIRE(procStore.getAllProc().size() == 1);
        REQUIRE(varStore.getAllVar().size() == 1);
      }

      THEN("Constant store should contain 1") {
        REQUIRE(constStore.getAllConst() == std::unordered_set<int>({1}));
      }

      THEN("Procedure store should contain 'proc'") {
        REQUIRE(procStore.getAllProc() ==
                std::unordered_set<std::string>({"proc"}));
      }

      THEN("Variable store should contain 'one'") {
        REQUIRE(varStore.getAllVar() ==
                std::unordered_set<std::string>({"one"}));
      }
    }

    WHEN("Duplicate value is added to them") {
      constStore.addConst(1);
      procStore.addProc("proc");
      varStore.addVar("one");
      constStore.addConst(1);
      procStore.addProc("proc");
      varStore.addVar("one");

      THEN("Their size should still be 1") {
        REQUIRE(constStore.getAllConst().size() == 1);
        REQUIRE(procStore.getAllProc().size() == 1);
        REQUIRE(varStore.getAllVar().size() == 1);
      }

      THEN("Constant store should still contain 1") {
        REQUIRE(constStore.getAllConst() == std::unordered_set<int>({1}));
      }

      THEN("Procedure store should still contain 'proc'") {
        REQUIRE(procStore.getAllProc() ==
                std::unordered_set<std::string>({"proc"}));
      }

      THEN("Variable store should still contain 'one'") {
        REQUIRE(varStore.getAllVar() ==
                std::unordered_set<std::string>({"one"}));
      }
    }
  }
}
