#include "QPS/constants/Constants.h"
#include "catch.hpp"

// Unit Tests for ClauseResult related functions
TEST_CASE("getLowerBound with 2 arguments returns the right results") {
  // same args
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::SYN_ERR,
                                   Constants::ClauseResult::SYN_ERR) ==
          Constants::ClauseResult::SYN_ERR);
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::SEM_ERR,
                                   Constants::ClauseResult::SEM_ERR) ==
          Constants::ClauseResult::SEM_ERR);
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::NO_MATCH,
                                   Constants::ClauseResult::NO_MATCH) ==
          Constants::ClauseResult::NO_MATCH);
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::OK,
                                   Constants::ClauseResult::OK) ==
          Constants::ClauseResult::OK);

  // first arg is lower
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::SYN_ERR,
                                   Constants::ClauseResult::SEM_ERR) ==
          Constants::ClauseResult::SYN_ERR);
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::SEM_ERR,
                                   Constants::ClauseResult::NO_MATCH) ==
          Constants::ClauseResult::SEM_ERR);
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::NO_MATCH,
                                   Constants::ClauseResult::OK) ==
          Constants::ClauseResult::NO_MATCH);

  // second arg is lower
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::SEM_ERR,
                                   Constants::ClauseResult::SYN_ERR) ==
          Constants::ClauseResult::SYN_ERR);
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::NO_MATCH,
                                   Constants::ClauseResult::SEM_ERR) ==
          Constants::ClauseResult::SEM_ERR);
  REQUIRE(Constants::getLowerBound(Constants::ClauseResult::OK,
                                   Constants::ClauseResult::NO_MATCH) ==
          Constants::ClauseResult::NO_MATCH);
}

TEST_CASE(
    "getLowerBound with vector of ClauseResults returns the right results") {
  // asc order
  std::vector<Constants::ClauseResult> ascList(
      {Constants::ClauseResult::SEM_ERR, Constants::ClauseResult::NO_MATCH,
       Constants::ClauseResult::OK});
  REQUIRE(Constants::getLowerBound(ascList) ==
          Constants::ClauseResult::SEM_ERR);

  // desc order
  std::vector<Constants::ClauseResult> descList(
      {Constants::ClauseResult::OK, Constants::ClauseResult::NO_MATCH,
       Constants::ClauseResult::SEM_ERR});
  REQUIRE(Constants::getLowerBound(descList) ==
          Constants::ClauseResult::SEM_ERR);

  // lowest in middle
  std::vector<Constants::ClauseResult> middleList(
      {Constants::ClauseResult::OK, Constants::ClauseResult::NO_MATCH,
       Constants::ClauseResult::SYN_ERR, Constants::ClauseResult::SEM_ERR});
  REQUIRE(Constants::getLowerBound(middleList) ==
          Constants::ClauseResult::SYN_ERR);
}