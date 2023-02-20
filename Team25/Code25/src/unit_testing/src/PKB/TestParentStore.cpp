#include "PKB/ParentStore.h"

#include "catch.hpp"


SCENARIO("Populating parent store") {
	GIVEN("New instance of parent store") {
		ParentStore parentStore;

		THEN("It should start empty") {
			REQUIRE(parentStore.getAllParents().size() == 0);
			REQUIRE(parentStore.getAllChildren().size() == 0);
		}

		WHEN("One parent is added") {
			parentStore.addParent(1, 3);

			THEN("Parent should be mapped to child") {
				REQUIRE(parentStore.getParent(3) == 1);
				REQUIRE(parentStore.getChildren(1) == std::unordered_set<int>({ 3 }));
			}

			WHEN("Duplicate parent is added") {
				parentStore.addParent(1, 3);

				THEN("Parent relation should remain the same") {
					REQUIRE(parentStore.getParent(3) == 1);
					REQUIRE(parentStore.getChildren(1) == std::unordered_set<int>({ 3 }));
				}
			}

			WHEN("New child is added to existing parent") {
				parentStore.addParent(1, 4);

				THEN("Parent should have two children") {
					REQUIRE(parentStore.getParent(3) == 1);
					REQUIRE(parentStore.getParent(4) == 1);
					REQUIRE(parentStore.getChildren(1) == std::unordered_set<int>({ 3, 4 }));
				}
			}
		}

		WHEN("Two Parents are added") {
			parentStore.addParent(1, 3);
			parentStore.addParent(3, 4);

			THEN("Parents should be mapped to children correctly") {
				REQUIRE(parentStore.getParent(3) == 1);
				REQUIRE(parentStore.getChildren(1) == std::unordered_set<int>({ 3 }));
				REQUIRE(parentStore.getParent(4) == 3);
				REQUIRE(parentStore.getChildren(3) == std::unordered_set<int>({ 4 }));
			}

			THEN("getAllChildren method should return all children") {
				REQUIRE(parentStore.getAllChildren() == std::unordered_set<int>({ 3, 4 }));
			}

			THEN("getAllParents method should return all parents") {
				REQUIRE(parentStore.getAllParents() == std::unordered_set<int>({ 1, 3 }));
			}
		}
	}
}
