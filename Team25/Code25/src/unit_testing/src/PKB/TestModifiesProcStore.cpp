#include "PKB/ModifiesProcStore.h"

#include "catch.hpp"

SCENARIO("Populating modifies procedure store") {
	GIVEN("New instance of modifies procedure store") {
		ModifiesProcStore mprocStore;

		THEN("It should start empty") {
			REQUIRE(mprocStore.getAllProc().size() == 0);
			REQUIRE(mprocStore.getAllVar().size() == 0);
		}

		WHEN("One modifiesProc is added") {
			mprocStore.addModifiesProc("sampleProc", "x");

			THEN("Procedure should be mapped to variable") {
				REQUIRE(mprocStore.getProc("x") == std::unordered_set<std::string>({ "sampleProc"}));
				REQUIRE(mprocStore.getVar("sampleProc") == std::unordered_set <std::string>({"x"}));
			}

			WHEN("Duplicate modifiesProc is added") {
				mprocStore.addModifiesProc("sampleProc", "x");

				THEN("ModifiesProc store should remain the same") {
					REQUIRE(mprocStore.getProc("x") == std::unordered_set<std::string>({ "sampleProc" }));
					REQUIRE(mprocStore.getVar("sampleProc") == std::unordered_set <std::string>({"x"}));
				}
			}
		}

		WHEN("Three modifiesProc are added") {
			mprocStore.addModifiesProc("proc1", "x");
			mprocStore.addModifiesProc("proc2", "x");
			mprocStore.addModifiesProc("proc3", "y");

			THEN("There should be 3 procedures and 2 variables") {
				REQUIRE(mprocStore.getAllProc() == std::unordered_set<std::string>({ "proc1", "proc2", "proc3" }));
				REQUIRE(mprocStore.getAllVar() == std::unordered_set<std::string>({ "x", "y" }));
			}

			THEN("Procedures should be mapped to variables correctly") {
				REQUIRE(mprocStore.getProc("x") == std::unordered_set<std::string>({ "proc1", "proc2" }));
				REQUIRE(mprocStore.getProc("y") == std::unordered_set<std::string>({ "proc3" }));
				REQUIRE(mprocStore.getVar("proc1") == std::unordered_set < std::string>({ "x" }));
				REQUIRE(mprocStore.getVar("proc2") == std::unordered_set < std::string>({ "x" }));
				REQUIRE(mprocStore.getVar("proc3") == std::unordered_set < std::string>({ "y" }));
			}
		}
	}
}

