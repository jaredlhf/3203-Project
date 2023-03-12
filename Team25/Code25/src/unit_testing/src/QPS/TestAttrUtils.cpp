#include "QPS/utils/AttrUtils.h"
#include "catch.hpp"

TEST_CASE("hasValidAttr returns the right result for procedure keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::PROCEDURE, Constants::PROCNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(Constants::PROCEDURE, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::PROCEDURE, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::PROCEDURE, Constants::STMTNUM) == false);
}

TEST_CASE("hasValidAttr returns the right result for variable keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::VARIABLE, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::VARIABLE, Constants::VARNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(Constants::VARIABLE, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::VARIABLE, Constants::STMTNUM) == false);
}

TEST_CASE("hasValidAttr returns the right result for constant keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::CONSTANT, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::CONSTANT, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::CONSTANT, Constants::VALUE) == true);
	REQUIRE(AttrUtils::hasValidAttr(Constants::CONSTANT, Constants::STMTNUM) == false);
}

TEST_CASE("hasValidAttr returns the right result for stmt keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::STMT, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::STMT, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::STMT, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::STMT, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for read keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::READ, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::READ, Constants::VARNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(Constants::READ, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::READ, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for print keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::PRINT, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::PRINT, Constants::VARNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(Constants::PRINT, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::PRINT, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for call keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::CALL, Constants::PROCNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(Constants::CALL, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::CALL, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::CALL, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for while keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::WHILE, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::WHILE, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::WHILE, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::WHILE, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for if keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::IF, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::IF, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::IF, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::IF, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for assign keyword") {
	REQUIRE(AttrUtils::hasValidAttr(Constants::ASSIGN, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::ASSIGN, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::ASSIGN, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(Constants::ASSIGN, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for procedure synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::PROCEDURE, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == false);
}

TEST_CASE("hasValidAttr returns the right result for variable synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::VARIABLE, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == false);
}

TEST_CASE("hasValidAttr returns the right result for constant synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::CONSTANT, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == true);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == false);
}

TEST_CASE("hasValidAttr returns the right result for stmt synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::STMT, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for read synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::READ, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for print synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::PRINT, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for call synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::CALL, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == true);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for while synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::WHILE, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for if synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::IF, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == true);
}

TEST_CASE("hasValidAttr returns the right result for assign synonym") {
	std::shared_ptr<Synonym> syn = Synonym::create(Constants::ASSIGN, "");
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::PROCNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VARNAME) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::VALUE) == false);
	REQUIRE(AttrUtils::hasValidAttr(syn, Constants::STMTNUM) == true);
}
