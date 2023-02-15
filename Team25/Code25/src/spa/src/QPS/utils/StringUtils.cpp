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

