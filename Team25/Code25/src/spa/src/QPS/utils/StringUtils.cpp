#include "StringUtils.h"

bool StringUtils::isValidInt(const std::string& s) {
	if (s.size() == 0 || s == "") {
		return false;
	}

	if (s[0] == '-' && s.size() == 1) {
		return false;
	}

	if (!(s[0] == '-' || std::isdigit(s[0]))) {
		return false;
	}

	for (int i = 1; i < s.size(); i++) {
		if (!std::isdigit(s[i])) {
			return false;
		}
	}

	return true;
}

/*
	Introduce space between special characters in the string
	E.g. "x+(z*y1)+1" -> "x +  ( z * y1 )  + 1" */
std::string StringUtils::spaceifyString(const std::string& s) {
	std::string res = "";
	for (const char c : s) {
		if (!std::isalnum(c)) {
			res += ' ';
			res += c;
			res += ' ';
		}
		else {
			res += c;
		}
	}

	return res;
}

std::vector<std::string> StringUtils:: splitString(const std::string& s) {
	std::vector<std::string> res;
	
	// Split words based on whitespaces and newlines
	std::regex words_regex("[^\\s\\n]+");

	auto words_begin = std::sregex_iterator(s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::string curr = (*i).str();
		if (curr.length() < 1) {
			continue;
		}

		res.push_back(curr);
	}

	return res;
}

/*
	Returns true if the particular IDENT token is found in an operation string
*/
bool StringUtils::tokenInOp(const std::string& opStr, const std::string& token) {
	std::vector<std::string> opTokens = StringUtils::splitString(StringUtils::spaceifyString(opStr));

	return std::find(opTokens.begin(), opTokens.end(), token) != opTokens.end();
}

