#include "catch.hpp"
#include "QPS/utils/ParserUtils.h"

// TODO: add tests for new methods
TEST_CASE("valid integer string") {
    std::string s = "123";
    REQUIRE(ParserUtils::isValidIntegerString(s) == true);
}

TEST_CASE("empty integer string") {
    std::string s = "";
    REQUIRE(ParserUtils::isValidIntegerString(s) == false);
}

TEST_CASE("integer string starts with zero") {
    std::string s = "0233";
    REQUIRE(ParserUtils::isValidIntegerString(s) == false);
}

TEST_CASE("integer string with non-numerical characters") {
    std::string s = "223sdas33";
    REQUIRE(ParserUtils::isValidIntegerString(s) == false);
}

TEST_CASE("valid name") {
    std::string s = "counter";
    REQUIRE(ParserUtils::isValidNaming(s) == true);
}

TEST_CASE("valid name with numbers") {
    std::string s = "counter22";
    REQUIRE(ParserUtils::isValidNaming(s) == true);
}

TEST_CASE("empty name string") {
    std::string s = "";
    REQUIRE(ParserUtils::isValidNaming(s) == false);
}

TEST_CASE("invalid character in name") {
    std::string s = "\'ounter";
    REQUIRE(ParserUtils::isValidNaming(s) == false);
}

TEST_CASE("invalid name that starts with non-letter") {
    std::string s = "2ounter";
    REQUIRE(ParserUtils::isValidNaming(s) == false);
}

SCENARIO("Testing method for checking validity of an entity reference") {
    GIVEN("some valid declarations") {
        std::vector<std::shared_ptr<Synonym>> declarations = {
            Synonym::create(Constants::VARIABLE, "x")
        };

        WHEN("given a valid wildcard string") {
            std::shared_ptr<Wildcard> w = Wildcard::create();
            THEN("it should return a wildcard entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidEntRef("_", declarations);
                REQUIRE(e->isWildcard() == true);
            }
        }

        WHEN("given a valid SIMPLE program variable string") {
            std::string s = "\"count\"";
            std::shared_ptr<Value> v = Value::create("count");
            THEN("it should return the correct value entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidEntRef(s, declarations);
                REQUIRE(e->isConstant() == true);
                REQUIRE(std::static_pointer_cast<Value>(e)->compare(v) == true);
            }
        }

        WHEN("given a valid variable synonym string") {
            std::string s = "x";
            std::shared_ptr<Synonym> correctSyn = Synonym::create(Constants::VARIABLE, s);
            THEN("it should return the correct variable synonym entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidEntRef(s, declarations);
                REQUIRE(e->isSynonym() == true);
                std::shared_ptr<Synonym> syn = std::static_pointer_cast<Synonym>(e);
                REQUIRE(syn->compare(correctSyn) == true);
            }
        }

        WHEN("given an undeclared variable synonym string") {
            std::string s = "y";
            std::shared_ptr<Synonym> errorSyn = Synonym::create(Constants::SEMANTIC_ERROR, "");
            THEN("it should return a semantic error synonym entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidEntRef(s, declarations);
                REQUIRE(e->isSynonym() == true);
                std::shared_ptr<Synonym> syn = std::static_pointer_cast<Synonym>(e);
                REQUIRE(syn->compare(errorSyn) == true);
            }
        }

        WHEN("given an invalid entity reference string") {
            std::string s = "123";
            std::shared_ptr<Synonym> errorSyn = Synonym::create(Constants::SYNTAX_ERROR, "");
            THEN("it should return a syntax error synonym entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidEntRef(s, declarations);
                REQUIRE(e->isSynonym() == true);
                std::shared_ptr<Synonym> syn = std::static_pointer_cast<Synonym>(e);
                REQUIRE(syn->compare(errorSyn) == true);
            }
        }
    }
}

SCENARIO("Testing method for checking validity of a statement reference") {
    GIVEN("some valid declarations") {
        std::vector<std::shared_ptr<Synonym>> declarations = {
                Synonym::create(Constants::VARIABLE, "a")
        };

        WHEN("given a valid wildcard string") {
            std::shared_ptr<Wildcard> w = Wildcard::create();
            THEN("it should return a wildcard entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidStmtRef("_", declarations);
                REQUIRE(e->isWildcard() == true);
            }
        }

        WHEN("given a valid statement reference string") {
            std::string s = "23";
            std::shared_ptr<Value> v = Value::create(s);
            THEN("it should return the correct value entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidStmtRef(s, declarations);
                REQUIRE(e->isConstant() == true);
                REQUIRE(std::static_pointer_cast<Value>(e)->compare(v) == true);
            }
        }

        WHEN("given a valid variable synonym string") {
            std::string s = "a";
            std::shared_ptr<Synonym> correctSyn = Synonym::create(Constants::VARIABLE, s);
            THEN("it should return the correct variable synonym entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidStmtRef(s, declarations);
                REQUIRE(e->isSynonym() == true);
                std::shared_ptr<Synonym> syn = std::static_pointer_cast<Synonym>(e);
                REQUIRE(syn->compare(correctSyn) == true);
            }
        }

        WHEN("given an undeclared variable synonym string") {
            std::string s = "y";
            std::shared_ptr<Synonym> errorSyn = Synonym::create(Constants::SEMANTIC_ERROR, "");
            THEN("it should return a semantic error synonym entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidStmtRef(s, declarations);
                REQUIRE(e->isSynonym() == true);
                std::shared_ptr<Synonym> syn = std::static_pointer_cast<Synonym>(e);
                REQUIRE(syn->compare(errorSyn) == true);
            }
        }

        WHEN("given an invalid entity reference string") {
            std::string s = "\"counts\"";
            std::shared_ptr<Synonym> errorSyn = Synonym::create(Constants::SYNTAX_ERROR, "");
            THEN("it should return a syntax error synonym entity") {
                std::shared_ptr<Entity> e = ParserUtils::getValidStmtRef(s, declarations);
                REQUIRE(e->isSynonym() == true);
                std::shared_ptr<Synonym> syn = std::static_pointer_cast<Synonym>(e);
                REQUIRE(syn->compare(errorSyn) == true);
            }
        }
    }
}

TEST_CASE("valid var_name factor pattern expression for milestone 1") {
    std::string s = "_\"s\"_";
    REQUIRE(ParserUtils::isValidExpression(s) == true);
}

TEST_CASE("valid wildcard pattern expression for milestone 1") {
    std::string s = "_";
    REQUIRE(ParserUtils::isValidExpression(s) == true);
}

TEST_CASE("valid const_value factor pattern expression for milestone 1") {
    std::string s = "_\"233\"_";
    REQUIRE(ParserUtils::isValidExpression(s) == true);
}

TEST_CASE("missing quotes for factor pattern expression for milestone 1") {
    std::string s = "_233_";
    REQUIRE(ParserUtils::isValidExpression(s) == false);
}

TEST_CASE("missing wildcard for factor pattern expression for milestone 1") {
    std::string s = "\"233\"_";
    REQUIRE(ParserUtils::isValidExpression(s) == false);
}

TEST_CASE("valid design entity") {
    std::string s = "variable";
    REQUIRE(ParserUtils::isDesignEntityToken(s) == true);
}

TEST_CASE("invalid design entity") {
    std::string s = "Variable";
    REQUIRE(ParserUtils::isDesignEntityToken(s) == false);
}

TEST_CASE("valid relation reference") {
    std::string s = "Follows*";
    REQUIRE(ParserUtils::isRelRefToken(s) == true);
}

TEST_CASE("invalid relation reference") {
    std::string s = "follow";
    REQUIRE(ParserUtils::isRelRefToken(s) == false);
}

TEST_CASE("remove quotes from string") {
    std::string s = "\"some text\"";
    std::string clean = "some text";
    REQUIRE(ParserUtils::removeQuotations(s) == clean);
}
