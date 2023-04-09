#include "catch.hpp"
#include "QPS/ParserResponse.h"

std::shared_ptr<Synonym> defaultSynonym = Synonym::create(Constants::VARIABLE, "x");
std::shared_ptr<Wildcard> defaultWildcardSynonym = Wildcard::create();
std::shared_ptr<Synonym> defaultWithSynonym = Synonym::create(Constants::ASSIGN, "a1", Constants::STMTNUM);
std::vector<std::shared_ptr<Synonym>> declarations = {defaultSynonym};
std::vector<std::shared_ptr<Synonym>> selectSynonyms = {defaultSynonym};
std::vector<std::shared_ptr<Clause>> suchThatClause = {
        Clause::create(Constants::MODIFIES,
                       defaultSynonym,
                       defaultWildcardSynonym)
};
std::vector<PatternClausePair> patternClause = {
        make_pair(defaultSynonym, Clause::create(Constants::PATTERN,
                                                 defaultWildcardSynonym,
                                                 defaultWildcardSynonym))
};
std::vector<std::shared_ptr<Clause>> withClause = {
        Clause::create(Constants::WITH,
                       defaultWithSynonym,
                       defaultWithSynonym)
};

ParserResponse initialise(ParserResponse p) {
    p.setDeclarations(declarations);
    p.setSelectSynonyms(selectSynonyms);
    p.setSuchThatClauses(suchThatClause);
    p.setPatternClauses(patternClause);
    p.setWithClauses(withClause);

    return p;
}
SCENARIO("Testing compare method for parserResponse") {
    ParserResponse p;
    p = initialise(p);
    GIVEN("comparison of declarations") {
        std::vector<std::shared_ptr<Synonym>> diffSyn = {
                Synonym::create(Constants::VARIABLE, "y")
        };
        std::vector<std::shared_ptr<Synonym>> diffLength = {
                Synonym::create(Constants::VARIABLE, "y"), Synonym::create(Constants::VARIABLE, "z")
        };
        ParserResponse other;

        WHEN("given the same declarations") {
            THEN("it should return true") {
                other = initialise(other);
                bool b = p.compare(other);
                REQUIRE(b == true);
            }
        }
        WHEN("given different declarations") {
            THEN("it should return false") {
                other = initialise(other);
                other.setDeclarations(diffSyn);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("given declarations of different length") {
            THEN("it should return false") {
                other = initialise(other);
                other.setDeclarations(diffLength);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
    }
    GIVEN("comparison of select synonyms") {
        std::vector<std::shared_ptr<Synonym>> diffSyn = {
                Synonym::create(Constants::VARIABLE, "y")
        };
        std::vector<std::shared_ptr<Synonym>> diffLength = {
                Synonym::create(Constants::VARIABLE, "y"), Synonym::create(Constants::VARIABLE, "z")
        };
        ParserResponse other;
        WHEN("given the same select synonyms") {
            THEN("it should return true") {
                other = initialise(other);
                bool b = p.compare(other);
                REQUIRE(b == true);
            }
        }
        WHEN("given different select synonyms") {
            THEN("it should return false") {
                other = initialise(other);
                other.setSelectSynonyms(diffSyn);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("given select synonyms of different length") {
            THEN("it should return false") {
                other = initialise(other);
                other.setSelectSynonyms(diffLength);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("select synonyms are missing in target syn") {
            THEN("it should return false") {
                other = initialise(other);
                p.setSelectSynonyms({});
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("select synonyms are missing in other syn") {
            THEN("it should return false") {
                other = initialise(other);
                other.setSelectSynonyms({});
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
    }
    GIVEN("comparison of suchThatClause") {
        std::vector<std::shared_ptr<Clause>> diffSuchThat = {
                Clause::create(Constants::USES,
                               defaultSynonym,
                               defaultWildcardSynonym)
        };
        std::vector<std::shared_ptr<Clause>> diffLength = {
                Clause::create(Constants::MODIFIES,
                               defaultSynonym,
                               defaultWildcardSynonym),
                Clause::create(Constants::MODIFIES,
                               defaultSynonym,
                               defaultWildcardSynonym)
        };
        ParserResponse other;
        WHEN("given the same such that") {
            THEN("it should return true") {
                other = initialise(other);
                bool b = p.compare(other);
                REQUIRE(b == true);
            }
        }
        WHEN("given different such that") {
            THEN("it should return false") {
                other = initialise(other);
                other.setSuchThatClauses(diffSuchThat);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("given such that of different length") {
            THEN("it should return false") {
                other = initialise(other);
                other.setSuchThatClauses(diffLength);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("such that are missing in target") {
            THEN("it should return false") {
                other = initialise(other);
                p.setSuchThatClauses({});
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("such that are missing in other") {
            THEN("it should return false") {
                other = initialise(other);
                other.setSuchThatClauses({});
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
    }
    GIVEN("comparison of withClause") {
        std::vector<std::shared_ptr<Clause>> diffWith = {
                Clause::create(Constants::WITH,
                               Synonym::create(Constants::PRINT, "a1", Constants::STMTNUM),
                               Synonym::create(Constants::PRINT, "a1", Constants::STMTNUM))
        };
        std::vector<std::shared_ptr<Clause>> diffLength = {
                Clause::create(Constants::WITH,
                               defaultWithSynonym,
                               defaultWithSynonym),
                Clause::create(Constants::WITH,
                               defaultWithSynonym,
                               defaultWithSynonym)
        };
        ParserResponse other;
        WHEN("given the same with") {
            THEN("it should return true") {
                other = initialise(other);
                bool b = p.compare(other);
                REQUIRE(b == true);
            }
        }
        WHEN("given different with") {
            THEN("it should return false") {
                other = initialise(other);
                other.setWithClauses(diffWith);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("given with of different length") {
            THEN("it should return false") {
                other = initialise(other);
                other.setWithClauses(diffLength);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("with are missing in target") {
            THEN("it should return false") {
                other = initialise(other);
                p.setWithClauses({});
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("with are missing in other") {
            THEN("it should return false") {
                other = initialise(other);
                other.setWithClauses({});
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
    }
    GIVEN("comparison of patternClause") {
        std::vector<PatternClausePair> diffPatternSyn = {
                make_pair(defaultWithSynonym, Clause::create(Constants::PATTERN,
                               defaultWildcardSynonym,
                               defaultWildcardSynonym))
        };
        std::vector<PatternClausePair> diffPattern = {
                make_pair(defaultSynonym, Clause::create(Constants::PATTERN,
                                                             defaultSynonym,
                                                             defaultWildcardSynonym))
        };
        std::vector<PatternClausePair> diffLength = {
                make_pair(defaultSynonym, Clause::create(Constants::PATTERN,
                                                         defaultWildcardSynonym,
                                                         defaultWildcardSynonym)),
                make_pair(defaultSynonym, Clause::create(Constants::PATTERN,
                                                         defaultWildcardSynonym,
                                                         defaultWildcardSynonym))
        };
        ParserResponse other;
        WHEN("given the same pattern") {
            THEN("it should return true") {
                other = initialise(other);
                bool b = p.compare(other);
                REQUIRE(b == true);
            }
        }
        WHEN("given different pattern syns") {
            THEN("it should return false") {
                other = initialise(other);
                other.setPatternClauses(diffPatternSyn);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("given different patterns") {
            THEN("it should return false") {
                other = initialise(other);
                other.setPatternClauses(diffPattern);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("given patterns of different length") {
            THEN("it should return false") {
                other = initialise(other);
                other.setPatternClauses(diffLength);
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("patterns are missing in target") {
            THEN("it should return false") {
                other = initialise(other);
                p.setPatternClauses({});
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
        WHEN("patterns are missing in other") {
            THEN("it should return false") {
                other = initialise(other);
                other.setPatternClauses({});
                bool b = p.compare(other);
                REQUIRE(b == false);
            }
        }
    }
}