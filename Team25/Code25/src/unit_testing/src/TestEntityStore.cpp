#include "PKB/EntityStore.h"

#include "catch.hpp"

ConstantStore constStore2;
ProcedureStore procStore2;
VariableStore varStore2;


TEST_CASE("Populate stores with values") {
	constStore2.add(1);
	constStore2.add(2);
	procStore2.add("proc");
	varStore2.add("one");
	varStore2.add("two");

	std::unordered_set<int> constOutput = constStore2.getAll();
	for (const auto& item : constOutput) {
		std::cout << item << std::endl;
	}

	std::unordered_set<std::string> procOutput = procStore2.getAll();
	for (const auto& item : procOutput) {
		std::cout << item << std::endl;
	}

	std::unordered_set<std::string> varOutput = varStore2.getAll();
	for (const auto& item : varOutput) {
		std::cout << item << std::endl;
	}

	REQUIRE(constOutput.size() == 2);
	REQUIRE(procOutput.size() == 1);
	REQUIRE(varOutput.size() == 2);
}