#include "PKB/EntityStore.h"

#include "catch.hpp"

ConstantStore constStore;
ProcedureStore procStore;
VariableStore varStore;


TEST_CASE("Populate stores with values") {
	constStore.add(1);
	constStore.add(2);
	procStore.add("proc");
	varStore.add("one");
	varStore.add("two");

	std::unordered_set<int> constOutput = constStore.getAll();
	for (const auto& item : constOutput) {
		std::cout << item << std::endl;
	}

	std::unordered_set<std::string> procOutput = procStore.getAll();
	for (const auto& item : procOutput) {
		std::cout << item << std::endl;
	}

	std::unordered_set<std::string> varOutput = varStore.getAll();
	for (const auto& item : varOutput) {
		std::cout << item << std::endl;
	}

	REQUIRE(constOutput.size() == 2);
	REQUIRE(procOutput.size() == 1);
	REQUIRE(varOutput.size() == 2);
}