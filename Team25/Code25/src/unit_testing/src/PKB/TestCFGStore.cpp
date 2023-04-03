#include "PKB/CFGStore.h"

#include "catch.hpp"
#include <algorithm>


SCENARIO("Populating CFG store") {
	GIVEN("New instance of CFG store with an initialized CFG") {
		CFGStore cfgStore;

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

		WHEN("One CFG is added to the store") {
			c->setNextNodes(c2);
			
			cfgStore.addCFGNode("TestCFG", c);

			THEN("The root node should be correct") {
				REQUIRE(cfgStore.getCFGNode("TestCFG") == c);
			}

			THEN("The node after root should be correct") {
				std::vector<std::shared_ptr<CFGNode>> expectedNodes;
				expectedNodes.push_back(c2);
				std::vector<std::shared_ptr<CFGNode>> actualNodes = cfgStore.getNextNodes(c);
				REQUIRE(actualNodes == expectedNodes);
			}
		}

		WHEN("More than one CFG is added to the store") {
			c->setNextNodes(c2);
			ifs->setThenNode(c3);
			ifs->setElseNode(w);
			w->setNextNodes(w2);

			cfgStore.addCFGNode("TestCFG1", c);
			cfgStore.addCFGNode("TestCFG2", ifs);

			THEN("The root nodes for both CFG should be correct") {
				REQUIRE(cfgStore.getCFGNode("TestCFG1") == c);
				REQUIRE(cfgStore.getCFGNode("TestCFG2") == ifs);
			}

			THEN("The If Node should be correct") {
				std::vector<std::shared_ptr<CFGNode>> expectedNodes;
				expectedNodes.push_back(c3);
				expectedNodes.push_back(w);
				std::vector<std::shared_ptr<CFGNode>> actualNodes = cfgStore.getNextNodes(ifs);
				REQUIRE(actualNodes == expectedNodes);
			}

			THEN("The While Node should be correct") {
				std::vector<std::shared_ptr<CFGNode>> expectedNodes;
				expectedNodes.push_back(w2);
				expectedNodes.push_back({});
				std::vector<std::shared_ptr<CFGNode>> actualNodes = cfgStore.getNextNodes(w);
				REQUIRE(actualNodes == expectedNodes);
			}
		}
	}
}