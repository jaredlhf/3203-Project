#include "QPS/constants/Wildcard.h"
#include "catch.hpp"

// TEST CASES FOR VALUE FACTORY FUNCTION
TEST_CASE("Wildcard factory method returns the right output") {
  std::shared_ptr<Entity> ent = Wildcard::create("x");
  std::shared_ptr<Entity> ent2 = Wildcard::create();

  REQUIRE(ent != nullptr);
  REQUIRE(ent2 != nullptr);
}

// TEST CASES FOR OVERRIDEN ENTITY FUNCTIONS
TEST_CASE("Wildcard overriden functions return the right output") {
  std::shared_ptr<Entity> ent = Wildcard::create("x");

  REQUIRE(ent->isConstant() == false);
  REQUIRE(ent->isSynonym() == false);
  REQUIRE(ent->isWildcard() == true);
}

// TEST CASES FOR VALUE INSTANCE FUNCTIONS
TEST_CASE("Wildcard getVal function returns the right output") {
  const std::string expected1 = "test";
  std::shared_ptr<Wildcard> ent1 = Wildcard::create(expected1);

  REQUIRE(ent1->getVal() == expected1);

  const std::string expected2 = "";
  std::shared_ptr<Wildcard> ent2 = Wildcard::create();

  REQUIRE(ent2->getVal() == expected2);
}

TEST_CASE("Wildcard isGenericWildcard function returns the right output") {
  const std::string test1 = "test";
  std::shared_ptr<Wildcard> ent1 = Wildcard::create(test1);

  REQUIRE(ent1->isGenericWildcard() == false);

  std::shared_ptr<Wildcard> ent2 = Wildcard::create();

  REQUIRE(ent2->isGenericWildcard() == true);
}

TEST_CASE("Wildcard compare function returns true for pattern wildcard") {
  const std::string test1 = "test";
  std::shared_ptr<Wildcard> ent1 = Wildcard::create(test1);
  std::shared_ptr<Wildcard> ent2 = Wildcard::create(test1);

  REQUIRE(ent1->compare(ent2) == true);
}

TEST_CASE("Wildcard compare function returns true for generic wildcard") {
  const std::string test1 = "";
  std::shared_ptr<Wildcard> ent1 = Wildcard::create(test1);
  std::shared_ptr<Wildcard> ent2 = Wildcard::create(test1);

  REQUIRE(ent1->compare(ent2) == true);
}

TEST_CASE("Wildcard compare function returns false for different wildcards") {
  const std::string test1 = "xx";
  const std::string test2 = "xyz";
  std::shared_ptr<Wildcard> ent1 = Wildcard::create(test1);
  std::shared_ptr<Wildcard> ent2 = Wildcard::create(test2);

  REQUIRE(ent1->compare(ent2) == false);
}