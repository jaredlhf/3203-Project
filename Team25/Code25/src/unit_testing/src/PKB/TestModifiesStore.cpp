#include "PKB/ModifiesStore.h"

#include "catch.hpp"

SCENARIO("Populating modifies store") {
	GIVEN("New instance of modifies store") {
		ModifiesStore modStore;

		WHEN("No modifies is added") {
			THEN("Get method should return empty") {
				REQUIRE(modStore.getVar(1) == std::unordered_set<std::string>());
			}
		}

		WHEN("One modifies is added") {
			modStore.addModifies(1, "x");

			THEN("Statement should be mapped to variable") {
				REQUIRE(modStore.getVar(1) == std::unordered_set < std::string>({ "x" }));
			}

			WHEN("Duplicate modifies is added") {
				modStore.addModifies(1, "x");

				THEN("Modifies store should remain the same") {
					REQUIRE(modStore.getVar(1) == std::unordered_set < std::string>({ "x" }));
				}
			}
		}

		WHEN("Three modifies are added") {
			modStore.addModifies(1, "x");
			modStore.addModifies(2, "x");
			modStore.addModifies(3, "y");

			THEN("Statements should be mapped to variables correctly") {
				REQUIRE(modStore.getVar(1) == std::unordered_set < std::string>({ "x" }));
				REQUIRE(modStore.getVar(2) == std::unordered_set < std::string>({ "x" }));
				REQUIRE(modStore.getVar(3) == std::unordered_set < std::string>({ "y" }));
			}
		}
	}
}

