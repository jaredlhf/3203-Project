#include "PKB/ModifiesProcStore.h"

#include "catch.hpp"

SCENARIO("Populating modifies procedure store") {
	GIVEN("New instance of modifies procedure store") {
		ModifiesProcStore mprocStore;

		WHEN("No modifiesProc is added") {
			THEN("Get method should return empty") {
				REQUIRE(mprocStore.getVar("sampleProc") == std::unordered_set<std::string>());
			}
		}

		WHEN("One modifiesProc is added") {
			mprocStore.addModifiesProc("sampleProc", "x");

			THEN("Procedure should be mapped to variable") {
				REQUIRE(mprocStore.getVar("sampleProc") == std::unordered_set <std::string>({"x"}));
			}

			WHEN("Duplicate modifiesProc is added") {
				mprocStore.addModifiesProc("sampleProc", "x");

				THEN("ModifiesProc store should remain the same") {
					REQUIRE(mprocStore.getVar("sampleProc") == std::unordered_set <std::string>({"x"}));
				}
			}
		}

		WHEN("Three modifiesProc are added") {
			mprocStore.addModifiesProc("proc1", "x");
			mprocStore.addModifiesProc("proc2", "x");
			mprocStore.addModifiesProc("proc3", "y");

			THEN("Procedures should be mapped to variables correctly") {
				REQUIRE(mprocStore.getVar("proc1") == std::unordered_set < std::string>({ "x" }));
				REQUIRE(mprocStore.getVar("proc2") == std::unordered_set < std::string>({ "x" }));
				REQUIRE(mprocStore.getVar("proc3") == std::unordered_set < std::string>({ "y" }));
			}
		}
	}
}

