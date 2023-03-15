#include "SP/ExpressionParser.cpp"
#include "SP/ExpressionParser.h"
#include "catch.hpp"

using namespace std;
SCENARIO("Parsing expressions") {
  GIVEN("ExpressionParser") {
    ExpressionParser e;
    WHEN("different simple valid expressions are parsed") {
      std::string var = "x";
      std::string constant = "1";
      std::string plus = "x + 1";
      std::string plus_bracket = "(x+1)";
      std::string minus = "x - 1";
      std::string minus_bracket = "(x+1)";
      std::string times = "x * 1";
      std::string times_bracket = "(x*1)";
      std::string divide = "x / 1";
      std::string divide_bracket = "(x/1)";
      std::string modulo = "x % 1";
      std::string modulo_bracket = "(x%1)";
      THEN("isExpr should return true") {
        REQUIRE(e.isExpr(var) == true);
        REQUIRE(e.isExpr(constant) == true);
        REQUIRE(e.isExpr(plus) == true);
        REQUIRE(e.isExpr(plus_bracket) == true);
        REQUIRE(e.isExpr(minus) == true);
        REQUIRE(e.isExpr(minus_bracket) == true);
        REQUIRE(e.isExpr(times) == true);
        REQUIRE(e.isExpr(times_bracket) == true);
        REQUIRE(e.isExpr(divide) == true);
        REQUIRE(e.isExpr(divide_bracket) == true);
        REQUIRE(e.isExpr(modulo) == true);
        REQUIRE(e.isExpr(modulo_bracket) == true);
      }
    }
    WHEN("different simple invalid expressions are parsed") {
      std::string var = "1x";
      std::string constant = "1_1";
      std::string plus = "x + ";
      std::string plus_bracket = "(x+1";
      std::string minus = "x - ";
      std::string minus_bracket = "(x+1";
      std::string times = "x * ";
      std::string times_bracket = "(x*1";
      std::string divide = "x / ";
      std::string divide_bracket = "(x/1";
      std::string modulo = "x % ";
      std::string modulo_bracket = "(x%1";
      THEN("isExpr should return true") {
        REQUIRE(e.isExpr(var) == false);
        REQUIRE(e.isExpr(constant) == false);
        REQUIRE(e.isExpr(plus) == false);
        REQUIRE(e.isExpr(plus_bracket) == false);
        REQUIRE(e.isExpr(minus) == false);
        REQUIRE(e.isExpr(minus_bracket) == false);
        REQUIRE(e.isExpr(times) == false);
        REQUIRE(e.isExpr(times_bracket) == false);
        REQUIRE(e.isExpr(divide) == false);
        REQUIRE(e.isExpr(divide_bracket) == false);
        REQUIRE(e.isExpr(modulo) == false);
        REQUIRE(e.isExpr(modulo_bracket) == false);
      }
    }
    WHEN("different complex valid expressions without brackets are parsed") {
      std::string test = "x + 1 / 2 * x % 3 - 2";
      std::string test2 = "3 * 4 / 2 + 1 - 2 % 2";
      std::string test3 = "x % y * u + i - p / a";
      THEN("isExpr should return true") {
        REQUIRE(e.isExpr(test) == true);
        REQUIRE(e.isExpr(test2) == true);
        REQUIRE(e.isExpr(test3) == true);
      }
    }
    WHEN("different complex valid expressions with brackets are parsed") {
      std::string test = "(x + 1) / (2 * x % 3) - 2";
      std::string test2 = "(3 * 4 / 2 + 1 - 2 % 2)";
      std::string test3 = "(x) % (y * u) + (i - p / a)";
      THEN("isExpr should return true") {
        REQUIRE(e.isExpr(test) == true);
        REQUIRE(e.isExpr(test2) == true);
        REQUIRE(e.isExpr(test3) == true);
      }
    }
    WHEN("different invalid expressions due to brackets matching are parsed") {
      std::string test = "(x + 1 / (2 * x % 3) - 2";
      std::string test2 = "(3 * 4 / 2) + 1 - 2 % 2)";
      std::string test3 = "(x) (% (y * u)) + (i - p / a)";
      THEN("isExpr should return true") {
        REQUIRE(e.isExpr(test) == false);
        REQUIRE(e.isExpr(test2) == false);
        REQUIRE(e.isExpr(test3) == false);
      }
    }
  }
}

SCENARIO("Parsing relational expressions") {
  GIVEN("ExpressionParser") {
    ExpressionParser e;
    WHEN("different simple valid relational expressions are parsed") {
      std::string more_than = "x > 1";
      std::string less_than = "x < 1";
      std::string more_than_equals = "x >= 1";
      std::string less_than_equals = "x <= 1";
      std::string equals = "x == 1";
      std::string not_equals = "x != 1";
      THEN("isRelExpr should return true") {
        REQUIRE(e.isRelExpr(more_than) == true);
        REQUIRE(e.isRelExpr(less_than) == true);
        REQUIRE(e.isRelExpr(more_than_equals) == true);
        REQUIRE(e.isRelExpr(less_than_equals) == true);
        REQUIRE(e.isRelExpr(equals) == true);
        REQUIRE(e.isRelExpr(not_equals) == true);
      }
    }
    WHEN("different simple invalid relational expressions are parsed") {
      std::string more_than = "(x > 1)";
      std::string less_than = "x >";
      std::string more_than_equals = "x >= ";
      std::string less_than_equals = "x <= ";
      std::string equals = " == 1";
      std::string not_equals = " != 1";
      THEN("isExpr should return false") {
        REQUIRE(e.isRelExpr(more_than) == false);
        REQUIRE(e.isRelExpr(less_than) == false);
        REQUIRE(e.isRelExpr(more_than_equals) == false);
        REQUIRE(e.isRelExpr(less_than_equals) == false);
        REQUIRE(e.isRelExpr(equals) == false);
        REQUIRE(e.isRelExpr(not_equals) == false);
      }
    }
    WHEN("different complex valid relational expressions without brackets are "
         "parsed") {
      std::string test = "x + 1 > 2 * x % 3 - 2";
      std::string test2 = "3 * 4 >= 2 + 1 - 2 % 2";
      std::string test3 = "x % y <= u + i - p / a";
      THEN("isRelExpr should return true") {
        REQUIRE(e.isRelExpr(test) == true);
        REQUIRE(e.isRelExpr(test2) == true);
        REQUIRE(e.isRelExpr(test3) == true);
      }
    }
    WHEN("different complex valid expressions with brackets are parsed") {
      std::string test = "(x + 1) > (2 * x % 3) - 2";
      std::string test2 = "(3 * 4) <= (2 + 1 - 2 % 2)";
      std::string test3 = "(x) == (y * u) + (i - p / a)";
      THEN("isRelExpr should return true") {
        REQUIRE(e.isRelExpr(test) == true);
        REQUIRE(e.isRelExpr(test2) == true);
        REQUIRE(e.isRelExpr(test3) == true);
      }
    }
    WHEN("different invalid expressions due to brackets matching are parsed") {
      std::string test = "(x + 1 > (2 * x % 3) - 2";
      std::string test2 = "(3 * 42) <= 1 - 2 % 2)";
      std::string test3 = "(x) (% (y * u)) == (i - p / a)";
      std::string test4 = "(x>1)";
      std::string test5 = "(x)>= x * 1)";
      THEN("isRelExpr should return false") {
        REQUIRE(e.isRelExpr(test) == false);
        REQUIRE(e.isRelExpr(test2) == false);
        REQUIRE(e.isRelExpr(test3) == false);
        REQUIRE(e.isRelExpr(test4) == false);
        REQUIRE(e.isRelExpr(test5) == false);
      }
    }
  }
}

SCENARIO("Parsing conditonal expressions") {
  GIVEN("ExpressionParser") {
    ExpressionParser e;
    WHEN("different simple valid conditional expressions are parsed") {
      std::string and_test = "(x > 1)&&(x>y)";
      std::string or_test = "(x > 1)||(x>y)";
      std::string not_test = "!(x > 1)";
      THEN("isCondExpr should return true") {
        REQUIRE(e.isCondExpr(and_test) == true);
        REQUIRE(e.isCondExpr(or_test) == true);
        REQUIRE(e.isCondExpr(not_test) == true);
      }
    }
    WHEN("different simple invalid conditional expressions are parsed") {
      std::string and_test = "(x + 1)&&(x>y)";
      std::string or_test = "(x - 1)||(x>y)";
      std::string not_test = "!(x * 1)";
      THEN("isCondExpr should return false") {
        REQUIRE(e.isCondExpr(and_test) == false);
        REQUIRE(e.isCondExpr(or_test) == false);
        REQUIRE(e.isCondExpr(not_test) == false);
      }
    }
    WHEN("different complex valid conditional expressions are parsed") {
      std::string and_test = "(var3!=(3+4+5))&&(var3==((((0)+0)+0)+0)+0)";
      std::string or_test = "((var3<3)&&(var2==0+2))||(x<=3)";
      std::string not_test = "!((var3<3)&&(var2==0+2))||(x<=3)";
      THEN("isCondExpr should return true") {
        REQUIRE(e.isCondExpr(and_test) == true);
        REQUIRE(e.isCondExpr(or_test) == true);
        REQUIRE(e.isCondExpr(not_test) == true);
      }
    }
    WHEN("different invalid conditional expressions due to brackets matching "
         "are parsed") {
      std::string and_test = "(var3!=(3+4+5)&&(var3==((((0)+0)+0)+0)+0)";
      std::string or_test = "((var3<3)&&(var2==0+2)||(x<=3)";
      std::string not_test = "!((var3<3)&&(var2==0+2))||(x<=3))";
      THEN("isCondExpr should return false") {
        REQUIRE(e.isCondExpr(and_test) == false);
        REQUIRE(e.isCondExpr(or_test) == false);
        REQUIRE(e.isCondExpr(not_test) == false);
      }
    }
  }
}