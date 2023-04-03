#include "PKB/ContainCallsStore.h"

#include "catch.hpp"

SCENARIO("Populating contain calls store") {
	GIVEN("New instance of contain calls store") {
		ContainCallsStore conCallsStore;

		WHEN("No calls is added") {
			THEN("Get method should return empty") {
				REQUIRE(conCallsStore.getProc(1) == std::unordered_set<std::string>());
			}
		}

		WHEN("One call is added") {
			conCallsStore.addContainCall(1, "proc1");

			THEN("Statement should be mapped to procedure call") {
				REQUIRE(conCallsStore.getProc(1) == std::unordered_set <std::string>({ "proc1" }));
			}

			WHEN("Duplicate call is added") {
				conCallsStore.addContainCall(1, "proc1");

				THEN("Store should remain the same") {
					REQUIRE(conCallsStore.getProc(1) == std::unordered_set <std::string>({ "proc1" }));
				}
			}
		}

		WHEN("Multiple calls are added") {
			conCallsStore.addContainCall(1, "proc1");
			conCallsStore.addContainCall(1, "proc2");
			conCallsStore.addContainCall(2, "proc1");
			conCallsStore.addContainCall(3, "proc2");
			conCallsStore.addContainCall(4, "proc2");

			THEN("Statements should be mapped to procedure calls correctly") {
				REQUIRE(conCallsStore.getProc(1) == std::unordered_set < std::string>({ "proc1", "proc2"}));
				REQUIRE(conCallsStore.getProc(2) == std::unordered_set < std::string>({ "proc1" }));
				REQUIRE(conCallsStore.getProc(3) == std::unordered_set < std::string>({ "proc2" }));
				REQUIRE(conCallsStore.getProc(4) == std::unordered_set < std::string>({ "proc2" }));
			}
		}
	}
}

