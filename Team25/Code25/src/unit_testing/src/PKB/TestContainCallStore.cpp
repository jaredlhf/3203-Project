#include "PKB/ContainCallsStore.h"

#include "catch.hpp"

SCENARIO("Populating contain calls store") {
	GIVEN("New instance of contain calls store") {
		ContainCallsStore conCallsStore;

		THEN("It should start empty") {
			REQUIRE(conCallsStore.getAllStmt().size() == 0);
			REQUIRE(conCallsStore.getAllProc().size() == 0);
		}

		WHEN("One call is added") {
			conCallsStore.addContainCall(1, "proc1");

			THEN("Statement should be mapped to procedure call") {
				REQUIRE(conCallsStore.getStmt("proc1") == std::unordered_set<int>({ 1 }));
				REQUIRE(conCallsStore.getProc(1) == std::unordered_set <std::string>({ "proc1" }));
			}

			WHEN("Duplicate call is added") {
				conCallsStore.addContainCall(1, "proc1");

				THEN("Store should remain the same") {
					REQUIRE(conCallsStore.getStmt("proc1") == std::unordered_set<int>({ 1 }));
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

			THEN("There should be 4 statements and 2 procedure calls") {
				REQUIRE(conCallsStore.getAllStmt() == std::unordered_set<int>({ 1, 2, 3, 4 }));
				REQUIRE(conCallsStore.getAllProc() == std::unordered_set<std::string>({ "proc1", "proc2" }));
			}

			THEN("Statements should be mapped to procedure calls correctly") {
				REQUIRE(conCallsStore.getStmt("proc1") == std::unordered_set<int>({ 1, 2 }));
				REQUIRE(conCallsStore.getStmt("proc2") == std::unordered_set<int>({ 1, 3, 4 }));
				REQUIRE(conCallsStore.getProc(1) == std::unordered_set < std::string>({ "proc1", "proc2"}));
				REQUIRE(conCallsStore.getProc(2) == std::unordered_set < std::string>({ "proc1" }));
				REQUIRE(conCallsStore.getProc(3) == std::unordered_set < std::string>({ "proc2" }));
				REQUIRE(conCallsStore.getProc(4) == std::unordered_set < std::string>({ "proc2" }));
			}
		}
	}
}

