#include "SP/Tokenizer.h"
#include "catch.hpp"
#include <algorithm>
#include <regex>

using namespace std;
SCENARIO("Tokenizing string") {
    GIVEN("Tokenizer") {
        WHEN("a simple string is parsed") {
            Tokenizer t;
            std::string var = "Hello";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"Hello"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple expression is parsed") {
            Tokenizer t;
            std::string var = "x + 1";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"x","+","1"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple expression without whitespace is parsed") {
            Tokenizer t;
            std::string var = "x+1";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"x","+","1"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple expression with newline is parsed") {
            Tokenizer t;
            std::string var = "x+1\n y + 2";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"x","+","1","y","+","2"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple expression with tab is parsed") {
            Tokenizer t;
            std::string var = "x+1\ty + 2";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"x","+","1","y","+","2"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple expression with semicolon is parsed") {
            Tokenizer t;
            std::string var = "x+1;\n y + 2;";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"x","+","1",";","y","+","2",";"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple expression with all arithmetic operators is parsed") {
            Tokenizer t;
            std::string var = "x+1-2*3%4/5;";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"x","+","1","-","2","*","3","%","4","/","5",";"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple relational expression is parsed") {
            Tokenizer t;
            std::string var = "x>3";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"x",">","3"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple conditional expression is parsed") {
            Tokenizer t;
            std::string var = "(x>3)&&(x<y)";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match and && should be a single token") {
                std::vector<std::string> expected({"(", "x", ">", "3", ")", "&&", "(", "x", "<", "y", ")" });
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple conditional expression is parsed") {
            Tokenizer t;
            std::string var = "(x>3)||(x<y)";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match and || should be a single token") {
                std::vector<std::string> expected({"(", "x", ">", "3", ")", "||", "(", "x", "<", "y", ")" });
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a assign statement is parsed") {
            Tokenizer t;
            std::string var = "x = y;";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"x", "=","y",";"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a print statement is parsed") {
            Tokenizer t;
            std::string var = "print y;";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"print", "y", ";"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a read statement is parsed") {
            Tokenizer t;
            std::string var = "read y;";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"read", "y", ";"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a while statement is parsed") {
            Tokenizer t;
            std::string var = "while ((x != 0) && (y != 0)) {\n"
                              "count = count + 1;\n"
                              "cenX = cenX + x;\n"
                              "cenY = cenY + y;\n"
                              "}";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"while", "(", "(", "x", "!=", "0", ")", "&&", "(", "y", "!=", "0", ")", ")", "{", "count", "=", "count", "+", "1", ";", "cenX", "=", "cenX", "+", "x", ";", "cenY", "=", "cenY", "+", "y", ";", "}"});
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a if statement is parsed") {
            Tokenizer t;
            std::string var = "if (count == 0) then {\n"
                              "flag = 1;\n"
                              "} else {\n"
                              "cenX = cenX / count;\n"
                              "cenY = cenY / count;\n"
                              "}";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"if", "(", "count", "==", "0", ")", "then", "{", "flag", "=", "1", ";", "}", "else", "{", "cenX", "=", "cenX", "/", "count", ";", "cenY", "=", "cenY", "/", "count", ";", "}" });
                REQUIRE(tokens == expected);
            }
        }
        WHEN("a simple program is parsed") {
            Tokenizer t;
            std::string var = "procedure computeCentroid {\n"
                              "count = 0;\n"
                              "cenX = 0;\n"
                              "cenY = 0;"
                              "}";
            t.tokenize(var);
            vector<string> tokens = t.getTokens();
            THEN("tokens should match") {
                std::vector<std::string> expected({"procedure", "computeCentroid", "{", "count", "=", "0", ";", "cenX", "=", "0", ";", "cenY", "=", "0", ";", "}" });
                REQUIRE(tokens == expected);
            }
        }
    }
}
