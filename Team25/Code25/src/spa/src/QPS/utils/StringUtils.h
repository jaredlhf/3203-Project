#pragma once

#include <string>
#include <vector>
#include <regex>

class StringUtils {
public:
	static bool isValidInt(const std::string& s);
	static std::string spaceifyString(const std::string& s);
	static std::vector<std::string> splitString(const std::string& s);
	static bool tokenInOp(const std::string& opStr, const std::string& token);
};
