#include "QPS/constants/Value.h"
#include "catch.hpp"

// TEST CASES FOR VALUE FACTORY FUNCTION
TEST_CASE("Value factory method returns the right output") {
  std::shared_ptr<Entity> ent = Value::create("x");

  REQUIRE(ent != nullptr);
}

// TEST CASES FOR OVERRIDEN ENTITY FUNCTIONS
TEST_CASE("Value overriden functions return the right output") {
  std::shared_ptr<Entity> ent = Value::create("x");

  REQUIRE(ent->isConstant() == true);
  REQUIRE(ent->isSynonym() == false);
  REQUIRE(ent->isWildcard() == false);
}

// TEST CASES FOR VALUE INSTANCE FUNCTIONS
TEST_CASE("Value getVal function returns the right output") {
  const std::string expected = "test";
  std::shared_ptr<Value> ent = Value::create(expected);

  REQUIRE(ent->getVal() == expected);
}

TEST_CASE("Value isInt function returns the right output for int string") {
  const std::string testInput = "123";
  std::shared_ptr<Value> ent = Value::create(testInput);

  REQUIRE(ent->isInt() == true);
}

TEST_CASE(
    "Value isInt function returns the right output for negative int string") {
  const std::string testInput = "-123";
  std::shared_ptr<Value> ent = Value::create(testInput);

  REQUIRE(ent->isInt() == true);
}

TEST_CASE("Value isInt function returns the right output for non int string") {
  const std::string testInput = "count";
  std::shared_ptr<Value> ent = Value::create(testInput);

  REQUIRE(ent->isInt() == false);
}

TEST_CASE("Value isInt function returns the right output for semi int string") {
  const std::string testInput = "12count";
  std::shared_ptr<Value> ent = Value::create(testInput);

  REQUIRE(ent->isInt() == false);
}

TEST_CASE("Value class compare function returns true for the same value") {
  const std::string val = "test";
  std::shared_ptr<Value> ent = Value::create(val);
  std::shared_ptr<Value> expected = Value::create(val);

  REQUIRE(ent->compare(expected) == true);
}

TEST_CASE("Value class compare function returns false for different values") {
  const std::string val = "test";
  std::shared_ptr<Value> ent = Value::create(val);
  std::shared_ptr<Value> expected = Value::create(val);

  REQUIRE(ent->compare(expected) == true);
}
