#include "PKB/EntityStore.h"
#include "SP/SPConstants.h"
#include "catch.hpp"


SCENARIO("Populating statement store") {
	GIVEN("New instance of statement store") {
		StatementStore stmtStore;

		WHEN("One statement is added") {
			stmtStore.addStmt(SPConstants::ASSIGN_TYPE, 1);

			THEN("Store should have 1 assign statement") {
				REQUIRE(stmtStore.getAllStmt(SPConstants::ASSIGN_TYPE).size() == 1);
			}

			THEN("Value of assign statement should be correct") {
				REQUIRE(stmtStore.getAllStmt(SPConstants::ASSIGN_TYPE) == std::unordered_set<int>({ 1 }));
			}

		}
		WHEN("2 assign, 1 print, 1 read are added") {
			stmtStore.addStmt(SPConstants::ASSIGN_TYPE, 1);
			stmtStore.addStmt(SPConstants::ASSIGN_TYPE, 2);
			stmtStore.addStmt(SPConstants::PRINT_TYPE, 3);
			stmtStore.addStmt(SPConstants::READ_TYPE, 4);

			THEN("Store should only have assign, print, read statements") {
				REQUIRE(stmtStore.getAllStmt(SPConstants::ASSIGN_TYPE).size() > 0);
				REQUIRE(stmtStore.getAllStmt(SPConstants::PRINT_TYPE).size() > 0);
				REQUIRE(stmtStore.getAllStmt(SPConstants::READ_TYPE).size() > 0);
				REQUIRE(stmtStore.getAllStmt(SPConstants::WHILE_TYPE).size() == 0);
				REQUIRE(stmtStore.getAllStmt(SPConstants::IF_TYPE).size() == 0);
				REQUIRE(stmtStore.getAllStmt(SPConstants::CALL_TYPE).size() == 0);
			}

			THEN("Value for statements should be correct") {
				REQUIRE(stmtStore.getAllStmt(SPConstants::ASSIGN_TYPE) == std::unordered_set<int>({ 1, 2 }));
				REQUIRE(stmtStore.getAllStmt(SPConstants::PRINT_TYPE) == std::unordered_set<int>({ 3 }));
				REQUIRE(stmtStore.getAllStmt(SPConstants::READ_TYPE) == std::unordered_set<int>({ 4 }));
			}

			THEN("Calling for non-existent value should return empty set") {
				REQUIRE(stmtStore.getAllStmt(SPConstants::WHILE_TYPE) == std::unordered_set<int>({ }));
				REQUIRE(stmtStore.getAllStmt(SPConstants::IF_TYPE) == std::unordered_set<int>({ }));
				REQUIRE(stmtStore.getAllStmt(SPConstants::CALL_TYPE) == std::unordered_set<int>({ }));
			}
		}
	}
}