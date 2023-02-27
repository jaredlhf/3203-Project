#include "Constants.h"

// Constant declaration for synonyms
const std::string Constants::STMT = "stmt";
const std::string Constants::READ = "read";
const std::string Constants::PRINT = "print";
const std::string Constants::CALL = "call";
const std::string Constants::WHILE = "while";
const std::string Constants::IF = "if";
const std::string Constants::ASSIGN = "assign";
const std::string Constants::VARIABLE = "variable";
const std::string Constants::CONSTANT = "constant";
const std::string Constants::PROCEDURE = "procedure";
const std::string Constants::SYNTAX_ERROR = "SyntaxError";
const std::string Constants::SEMANTIC_ERROR = "SemanticError";

// Constant declaration for clauses
const std::string Constants::USES = "Uses";
const std::string Constants::MODIFIES = "Modifies";
const std::string Constants::PARENT = "Parent";
const std::string Constants::PARENTST = "Parent*";
const std::string Constants::FOLLOWS = "Follows";
const std::string Constants::FOLLOWSST = "Follows*";
const std::string Constants::PATTERN = "pattern";
const std::string Constants::WITH = "with";
const std::string Constants::WILDCARD = "_";

// Constant declaration for attribute names
const std::string Constants::PROCNAME = "procName";
const std::string Constants::VARNAME = "varName";
const std::string Constants::VALUE = "value";
const std::string Constants::STMTNUM = "stmt#";

// AttrName related functions
bool Constants::isAttrNameInt(const std::string& attrName) {
	return attrName == Constants::VALUE || attrName == Constants::STMTNUM;
}

// ClauseResult related functions
Constants::ClauseResult Constants::getLowerBound(Constants::ClauseResult c1, Constants::ClauseResult c2) {
	return std::min(c1, c2);
}

Constants::ClauseResult Constants::getLowerBound(std::vector<Constants::ClauseResult> clauseList) {
	if (clauseList.size() == 0) {
		return Constants::ClauseResult::SYN_ERR;
	}

	Constants::ClauseResult res = clauseList[0];
	for (int i = 1; i < clauseList.size(); i++) {
		res = getLowerBound(res, clauseList[i]);
	}

	return res;
}