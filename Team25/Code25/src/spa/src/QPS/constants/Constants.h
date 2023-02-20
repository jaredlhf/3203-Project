#pragma once

#include <string>
#include <vector>

class Constants {
public:
	// Constant declaration for synonyms
	static const std::string STMT;
	static const std::string READ;
	static const std::string PRINT;
	static const std::string CALL;
	static const std::string WHILE;
	static const std::string IF;
	static const std::string ASSIGN;
	static const std::string VARIABLE;
	static const std::string CONSTANT;
	static const std::string PROCEDURE;
	static const std::string SYNTAX_ERROR;
	static const std::string SEMANTIC_ERROR;

	// Constant declaration for clauses
	static const std::string USES;
	static const std::string MODIFIES;
	static const std::string PARENT;
	static const std::string FOLLOWS;
	static const std::string PARENTST;
	static const std::string FOLLOWSST;
	static const std::string PATTERN;
	static const std::string WILDCARD;

	enum class ClauseResult{
		SYN_ERR = 0,
		SEM_ERR = 1,
		NO_MATCH = 2,
		OK = 3
	};

	// ClauseResult related functions
	static Constants::ClauseResult getLowerBound(Constants::ClauseResult c1, Constants::ClauseResult c2);
	static Constants::ClauseResult getLowerBound(std::vector<Constants::ClauseResult> clauseList);
};