#include "QPS/ResultFormatter.h"
#include "catch.hpp"

TEST_CASE("Formatting results for 1 result returns the right results") {
  std::vector<std::string> resNames = {"s1"};
  std::vector<std::string> headers = {"s3", "s1244", "s1", "s1919"};
  std::set<std::vector<std::string>> data = {
      {"1", "2", "3", "4"},
      {"w1", "w2", "w3", "w4"},
      {"w", "x", "y", "z"},
      {"w3w", "x3x", "y3y", "z3z"},
  };

  std::shared_ptr<QpsTable> resTable = QpsTable::create(headers, data);

  std::set<std::string> expected = {"3", "y", "w3", "y3y"};
  std::set<std::string> res = ResultFormatter(resNames, resTable).getResults();

  REQUIRE(res == expected);
}

TEST_CASE("Formatting results for multiple results not same order as header "
          "returns the right results") {
  std::vector<std::string> resNames = {"s1", "s3", "s1919"};
  std::vector<std::string> headers = {"s3", "s1244", "s1", "s1919"};
  std::set<std::vector<std::string>> data = {
      {"1", "2", "3", "4"},
      {"w1", "w2", "w3", "w4"},
      {"w", "x", "y", "z"},
      {"w3w", "x3x", "y3y", "z3z"},
  };

  std::shared_ptr<QpsTable> resTable = QpsTable::create(headers, data);

  std::set<std::string> expected = {"3 1 4", "y w z", "w3 w1 w4",
                                    "y3y w3w z3z"};
  std::set<std::string> res = ResultFormatter(resNames, resTable).getResults();

  REQUIRE(res == expected);
}