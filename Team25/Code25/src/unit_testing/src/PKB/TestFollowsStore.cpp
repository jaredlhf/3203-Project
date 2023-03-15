#include "PKB/FollowsStore.h"

#include "catch.hpp"

SCENARIO("Populating follows store") {
  GIVEN("New instance of follows store") {
    FollowsStore followsStore;

    THEN("It should start empty") {
      REQUIRE(followsStore.getAllRight().size() == 0);
      REQUIRE(followsStore.getAllLeft().size() == 0);
    }

    WHEN("One follows is added") {
      followsStore.addFollows(1, 3);

      THEN("Followee should be mapped to follower") {
        REQUIRE(followsStore.getLeftStmt(3) == 1);
        REQUIRE(followsStore.getRightStmt(1) == 3);
      }

      WHEN("Duplicate follows is added") {
        followsStore.addFollows(1, 3);

        THEN("Follows relation should remain the same") {
          REQUIRE(followsStore.getLeftStmt(3) == 1);
          REQUIRE(followsStore.getRightStmt(1) == 3);
        }
      }
    }
    WHEN("Two follows are added") {
      followsStore.addFollows(1, 3);
      followsStore.addFollows(3, 4);

      THEN("Followees should be mapped to followers correctly") {
        REQUIRE(followsStore.getLeftStmt(3) == 1);
        REQUIRE(followsStore.getRightStmt(1) == 3);
        REQUIRE(followsStore.getLeftStmt(4) == 3);
        REQUIRE(followsStore.getRightStmt(3) == 4);
      }

      THEN("getAllRight method should return all followers") {
        REQUIRE(followsStore.getAllRight() == std::unordered_set<int>({3, 4}));
      }

      THEN("getAllLeft method should return all followees") {
        REQUIRE(followsStore.getAllLeft() == std::unordered_set<int>({1, 3}));
      }
    }
  }
}