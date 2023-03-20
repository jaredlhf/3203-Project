#include "SP/CFGNode.h"
#include "catch.hpp"


SCENARIO("Testing getAllLeafNodes()") {
    GIVEN("A few types of CFG Nodes") {
        std::vector<int> lineNo;
        lineNo.push_back(1);

        std::vector<int> lineNo2;
        lineNo2.push_back(4);
        lineNo2.push_back(5);

        std::vector<int> lineNo3;
        lineNo3.push_back(10);

        std::vector<int> lineNo4;
        lineNo3.push_back(11);

        std::vector<int> lineNo5;
        lineNo3.push_back(12);

        std::shared_ptr<CFGNode> c = std::make_shared<CFGNode>(lineNo);
        std::shared_ptr<CFGNode> c2 = std::make_shared<CFGNode>(lineNo2);
        std::shared_ptr<CFGNode> c3 = std::make_shared<CFGNode>(lineNo3);
        std::shared_ptr<CFGNode> c4 = std::make_shared<CFGNode>(lineNo4);
        std::shared_ptr<CFGNode> c5 = std::make_shared<CFGNode>(lineNo5);
        std::shared_ptr<CFGWhileNode> w = std::make_shared<CFGWhileNode>(2);
        std::shared_ptr<CFGWhileNode> w2 = std::make_shared<CFGWhileNode>(6);
        std::shared_ptr<CFGWhileNode> w3 = std::make_shared<CFGWhileNode>(13);
        std::shared_ptr<CFGIfNode> ifs = std::make_shared<CFGIfNode>(3);
        std::shared_ptr<CFGIfNode> ifs2 = std::make_shared<CFGIfNode>(7);
        std::shared_ptr<CFGIfNode> ifs3 = std::make_shared<CFGIfNode>(8);
        std::shared_ptr<CFGIfNode> ifs4 = std::make_shared<CFGIfNode>(9);


        WHEN("a single cfgNode") {
            std::unordered_set<std::shared_ptr<CFGNode>> leafNodes = c->getAllLeafNodes();
            THEN("it should contain all the leaf nodes") {
                std::unordered_set<std::shared_ptr<CFGNode>> expectedLeafNodes;
                expectedLeafNodes.insert(c);
                REQUIRE(leafNodes == expectedLeafNodes);
            }
        }

        WHEN("a single cfgWhileNode") {
            std::unordered_set<std::shared_ptr<CFGNode>> leafNodes = w->getAllLeafNodes();
            THEN("it should contain all the leaf nodes") {
                std::unordered_set<std::shared_ptr<CFGNode>> expectedLeafNodes;
                expectedLeafNodes.insert(w);
                REQUIRE(leafNodes == expectedLeafNodes);
            }
        }

        WHEN("a single cfgIfNode with no then or else") {
            THEN("it throw an error") {
                REQUIRE_THROWS_AS(ifs->getAllLeafNodes(), std::invalid_argument);
            }
        }

        WHEN("a single cfgIfNode") {
            ifs->setThenNode(c);
            ifs->setElseNode(c2);
            std::unordered_set<std::shared_ptr<CFGNode>> leafNodes = ifs->getAllLeafNodes();
            THEN("it should contain all the leaf nodes") {
                std::unordered_set<std::shared_ptr<CFGNode>> expectedLeafNodes;
                expectedLeafNodes.insert(c);
                expectedLeafNodes.insert(c2);
                REQUIRE(leafNodes == expectedLeafNodes);
            }
        }

        WHEN("a cfgIfNode followed by cfgWhileNode") {
            ifs->setThenNode(c);
            ifs->setElseNode(c2);
            ifs->setNextNodes(w);
            std::unordered_set<std::shared_ptr<CFGNode>> leafNodes = ifs->getAllLeafNodes();
            THEN("it should contain all the leaf nodes") {
                std::unordered_set<std::shared_ptr<CFGNode>> expectedLeafNodes;
                expectedLeafNodes.insert(w);
                REQUIRE(leafNodes == expectedLeafNodes);
            }
        }

        WHEN("a cfgWhileNode followed by cfgIfNode") {
            ifs->setThenNode(c);
            ifs->setElseNode(c2);
            w->setNextNodes(ifs);
            std::unordered_set<std::shared_ptr<CFGNode>> leafNodes = w->getAllLeafNodes();
            THEN("it should contain all the leaf nodes") {
                std::unordered_set<std::shared_ptr<CFGNode>> expectedLeafNodes;
                expectedLeafNodes.insert(c);
                expectedLeafNodes.insert(c2);
                REQUIRE(leafNodes == expectedLeafNodes);
            }
        }

        WHEN("a multi nested if and while cfg") {
            ifs->setThenNode(c);
            ifs->setElseNode(w);
            c->setNextNodes(ifs2);
            c3->setNextNodes(w3);

            ifs4->setThenNode(c5);
            ifs4->setElseNode(c4);
            ifs3->setThenNode(ifs4);
            ifs3->setElseNode(c3);
            ifs2->setThenNode(ifs3);
            ifs2->setElseNode(c2);

            w->setNextNodes(w2);
            std::unordered_set<std::shared_ptr<CFGNode>> leafNodes = ifs->getAllLeafNodes();
            THEN("it should contain all the leaf nodes") {
                std::unordered_set<std::shared_ptr<CFGNode>> expectedLeafNodes;
                expectedLeafNodes.insert(c2);
                expectedLeafNodes.insert(c4);
                expectedLeafNodes.insert(c5);
                expectedLeafNodes.insert(w2);
                expectedLeafNodes.insert(w3);
                REQUIRE(leafNodes == expectedLeafNodes);
            }

        }
    }
}

