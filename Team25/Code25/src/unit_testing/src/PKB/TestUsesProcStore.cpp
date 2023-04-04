#include "PKB/UsesProcStore.h"

#include "catch.hpp"

SCENARIO("Populating uses procedure store") {
	GIVEN("New instance of uses procedure store") {
		UsesProcStore uprocStore;

		WHEN("No usesProc is added") {
			THEN("Get method should return empty") {
				REQUIRE(uprocStore.getVar("sampleProc") == std::unordered_set<std::string>());
			}
		}

		WHEN("One usesProc is added") {
			uprocStore.addUsesProc("sampleProc", "x");

			THEN("Procedure should be mapped to variable") {
				REQUIRE(uprocStore.getVar("sampleProc") == std::unordered_set <std::string>({ "x" }));
			}

			WHEN("Duplicate usesProc is added") {
				uprocStore.addUsesProc("sampleProc", "x");

				THEN("UsesProc store should remain the same") {
					REQUIRE(uprocStore.getVar("sampleProc") == std::unordered_set <std::string>({ "x" }));
				}
			}
		}

		WHEN("Three usesProc are added") {
			uprocStore.addUsesProc("proc1", "x");
			uprocStore.addUsesProc("proc2", "x");
			uprocStore.addUsesProc("proc3", "y");

			THEN("Procedures should be mapped to variables correctly") {
				REQUIRE(uprocStore.getVar("proc1") == std::unordered_set < std::string>({ "x" }));
				REQUIRE(uprocStore.getVar("proc2") == std::unordered_set < std::string>({ "x" }));
				REQUIRE(uprocStore.getVar("proc3") == std::unordered_set < std::string>({ "y" }));
			}
		}
	}
}

