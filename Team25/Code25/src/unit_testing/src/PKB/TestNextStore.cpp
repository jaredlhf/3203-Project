#include "PKB/NextStore.h"

#include "catch.hpp"



SCENARIO("Populating next store") {
	GIVEN("New instance of next store") {
		NextStore nextStore;

		THEN("It should start empty") {
			REQUIRE(nextStore.getAllRight().size() == 0);
			REQUIRE(nextStore.getAllLeft().size() == 0);
		}

		WHEN("One next statement pair is added") {
			nextStore.addNext(1, 3);

			THEN("Left statement should be mapped to right statement") {
				REQUIRE(nextStore.getLeftStmt(3) == std::unordered_set<int>({ 1 }));
				REQUIRE(nextStore.getRightStmt(1) == std::unordered_set <int>({ 3 }));
			}

			WHEN("Duplicate next statement pair is added") {
				nextStore.addNext(1, 3);

				THEN("Next relation should remain the same") {
					REQUIRE(nextStore.getLeftStmt(3) == std::unordered_set<int>({ 1 }));
					REQUIRE(nextStore.getRightStmt(1) == std::unordered_set <int>({ 3 }));
				}
			}
		}
		WHEN("Two next statement pairs are added") {
			nextStore.addNext(1, 3);
			nextStore.addNext(3, 4);

			THEN("Left statement should be mapped to right statements correctly") {
				REQUIRE(nextStore.getLeftStmt(3) == std::unordered_set<int>({ 1 }));
				REQUIRE(nextStore.getRightStmt(1) == std::unordered_set <int>({ 3 }));
				REQUIRE(nextStore.getLeftStmt(4) == std::unordered_set <int>({ 3 }));
				REQUIRE(nextStore.getRightStmt(3) == std::unordered_set <int>({ 4 }));
			}

			THEN("getAllRight method should return all right statements") {
				REQUIRE(nextStore.getAllRight() == std::unordered_set<int>({ 3, 4 }));
			}

			THEN("getAllLeft method should return all left statements") {
				REQUIRE(nextStore.getAllLeft() == std::unordered_set<int>({ 1, 3 }));
			}
		}
	}
}