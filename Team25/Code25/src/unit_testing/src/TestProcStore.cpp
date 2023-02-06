#include "PKB/ProcedureStore.h"

#include "catch.hpp"
using namespace std;

ProcedureStore procStore;

TEST_CASE("Empty procedure store") {
	unordered_set<string> output({ });
    procStore.clear();
	REQUIRE(procStore.size() == 0);
	REQUIRE(procStore.getAllProc() == output);
}

TEST_CASE("Add one procedure") {
	procStore.clear();
	procStore.addProc("one");

	unordered_set<string> output({ "one" });

	REQUIRE(procStore.size() == 1);
	REQUIRE(procStore.getAllProc() == output);
	REQUIRE(procStore.has("one"));
	REQUIRE(!procStore.has("two"));
}

TEST_CASE("Add two procedures") {
	procStore.clear();
	procStore.addProc("one");
	procStore.addProc("two");

	unordered_set<string> output({ "one", "two" });

	REQUIRE(procStore.size() == 2);
	REQUIRE(procStore.getAllProc() == output);
	REQUIRE(procStore.has("one"));
	REQUIRE(procStore.has("two"));
}

TEST_CASE("Add duplicate procedure") {
	procStore.clear();
	procStore.addProc("one");
	procStore.addProc("one");

	unordered_set<string> output({ "one" });

	REQUIRE(procStore.size() == 1);
	REQUIRE(procStore.getAllProc() == output);
	REQUIRE(procStore.has("one"));
}
