#pragma once

#include <string>
#include <vector>
#include <regex>
#include <stack>
#include <algorithm>

class StringUtils {
public:
	static bool isValidInt(const std::string& s);
	static std::string spaceifyString(const std::string& s);
	static std::vector<std::string> splitString(const std::string& s);
	static bool tokenInOp(const std::string& opStr, const std::string& token);
	static bool postFixInFullpostFix(const std::string& postFix, const std::string& fullPostFix);
	static std::string createPostFixNotation(const std::string& prefixNotation);
	static int opPrecedence(char op);
};
