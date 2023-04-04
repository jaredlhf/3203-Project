#include "PKB/AttributeStore.h"

#include "catch.hpp"

SCENARIO("Populating attribute stores") {
	GIVEN("New instances of print, read, call attributes") {

		PrintAttribute printA;
		ReadAttribute readA;
		CallAttribute callA;

		WHEN("No attributes are added") {
			THEN("Get methods should return empty") {
				REQUIRE(printA.getAttr(1) == std::string());
				REQUIRE(readA.getAttr(2) == std::string());
				REQUIRE(callA.getAttr(3) == std::string());
			}
		}

		WHEN("One value is added to them") {
			printA.addAttr("x", 1);
			readA.addAttr("y", 2);
			callA.addAttr("sampleProc", 3);

			THEN("print attribute store should return correct values") {
				REQUIRE(printA.getAttr(1) == "x");
			}

			THEN("read attribute store should return correct values") {
				REQUIRE(readA.getAttr(2) == "y");
			}

			THEN("call attribute store should return correct values") {
				REQUIRE(callA.getAttr(3) == "sampleProc");
			}
		}

		WHEN("Two values are added to them") {
			printA.addAttr("x", 1);
			printA.addAttr("x", 4);
			readA.addAttr("y", 2);
			readA.addAttr("y", 5);
			callA.addAttr("sampleProc", 3);
			callA.addAttr("sampleProc", 6);

			THEN("print attribute store should return correct values") {
				REQUIRE(printA.getAttr(1) == "x");
			}

			THEN("read attribute store should return correct values") {
				REQUIRE(readA.getAttr(2) == "y");
			}

			THEN("call attribute store should return correct values") {
				REQUIRE(callA.getAttr(3) == "sampleProc");
			}

			WHEN("Non-existent value is retrieved") {
				THEN("print get methods should return empty") {
					REQUIRE(printA.getAttr(2) == std::string());
				}

				THEN("read get methods should return empty") {
					REQUIRE(readA.getAttr(3) == std::string());
				}

				THEN("call get methods should return empty") {
					REQUIRE(callA.getAttr(4) == std::string());
				}
			}
		}
	}
}

