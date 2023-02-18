#include "PKB/EntityStore.h"

#include "catch.hpp"



SCENARIO("Populating stores for constants, procedures, and variables") {
	GIVEN("Instances of constant store, procedure store, variable store") {
		ConstantStore constStore;
		ProcedureStore procStore;
		VariableStore varStore;

		THEN("They should start empty") {
			REQUIRE(constStore.getAll().size() == 0);
			REQUIRE(procStore.getAll().size() == 0);
			REQUIRE(varStore.getAll().size() == 0);
		}

		WHEN("One value is added to them") {
			constStore.add(1);
			procStore.add("proc");
			varStore.add("one");

			THEN("Their size should increase by 1") {
				REQUIRE(constStore.getAll().size() == 1);
				REQUIRE(procStore.getAll().size() == 1);
				REQUIRE(varStore.getAll().size() == 1);
			}

			THEN("Constant store should contain 1") {
				REQUIRE(constStore.getAll() == std::unordered_set<int>({1}));
			}

			THEN("Procedure store should contain 'proc'") {
				REQUIRE(procStore.getAll() == std::unordered_set<std::string>({ "proc" }));
			}

			THEN("Variable store should contain 'one'") {
				REQUIRE(varStore.getAll() == std::unordered_set<std::string>({ "one" }));
			}
		}
	}
}
