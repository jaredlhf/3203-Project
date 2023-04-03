#include "PKB/UsesStore.h"

#include "catch.hpp"

SCENARIO("Populating uses store") {
	GIVEN("New instance of uses store") {
		UsesStore usesStore;

		WHEN("No uses is added") {
			THEN("Get method should return empty") {
				REQUIRE(usesStore.getVar(1) == std::unordered_set<std::string>());
			}
		}

		WHEN("One uses is added") {
			usesStore.addUses(1, "x");

			WHEN("Duplicate uses is added") {
				usesStore.addUses(1, "x");

				THEN("Uses store should remain the same") {
					REQUIRE(usesStore.getVar(1) == std::unordered_set<std::string>({ "x" }));
				}
			}
		}

		WHEN("Four uses are added") {
			usesStore.addUses(2, "x");
			usesStore.addUses(2, "y");
			usesStore.addUses(3, "v");
			usesStore.addUses(3, "x");

			THEN("Statements should be mapped to variables correctly") {
				REQUIRE(usesStore.getVar(2) == std::unordered_set<std::string>({ "x", "y" }));
				REQUIRE(usesStore.getVar(3) == std::unordered_set<std::string>({ "v", "x" }));
			}
		}
	}
}

