#pragma once

#include "QPS/constants/Synonym.h"

class AttrUtils {
public:
	static bool hasValidAttr(const std::string& synKeyword, const std::string& attrName);
	static bool hasValidAttr(std::shared_ptr<Synonym> syn, const std::string& attrName);
};