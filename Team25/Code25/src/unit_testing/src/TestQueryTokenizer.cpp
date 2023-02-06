#include <vector>
#include <string>
#include "QPS/QueryTokenizer.h"
#include "catch.hpp"

using namespace std;

QueryTokenizer qt;

TEST_CASE("Tokenize basic query without parantheses and newlines") {
	string testStr = "variable v; Select v";
	vector<string> expected{"variable", "v", ";", "Select", "v"};
	vector<string> res = qt.tokenize(testStr);

	REQUIRE(res == expected);
}

TEST_CASE("Tokenize basic query with extra whitespaces") {
	string testStr = "variable    v; Select v";
	vector<string> expected{ "variable", "v", ";", "Select", "v" };
	vector<string> res = qt.tokenize(testStr);

	REQUIRE(res == expected);
}

TEST_CASE("Tokenize basic query newline but without parantheses") {
	string testStr = "variable v;\nSelect v";
	vector<string> expected{ "variable", "v", ";", "Select", "v" };
	vector<string> res = qt.tokenize(testStr);

	REQUIRE(res == expected);
}

TEST_CASE("Tokenize basic query with parantheses and newline") {
	string testStr = "variable v;\nSelect v such that Follows* (6, v)";
	vector<string> expected{ "variable", "v", ";", "Select", "v", 
		"such", "that", "Follows*", "(", "6", ",", "v", ")"};
	vector<string> res = qt.tokenize(testStr);

	REQUIRE(res == expected);
}

TEST_CASE("Tokenize complex query") {
	string testStr = "assign a; while w;\nSelect a such that Parent* (w, a) pattern a (\"count\", \\_)";
	vector<string> expected{ "assign", "a", ";", "while", "w", ";", "Select", "a",
		"such", "that", "Parent*", "(", "w", ",", "a", ")", "pattern", "a", 
		"(", "\"count\"", ",", "\\_", ")" };
	vector<string> res = qt.tokenize(testStr);

	REQUIRE(res == expected);
}
