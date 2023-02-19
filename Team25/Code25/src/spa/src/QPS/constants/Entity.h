#pragma once

#include <string>

class Entity {
public:
	virtual bool isConstant() = 0;
	virtual bool isSynonym() = 0;
	virtual bool isWildcard() = 0;
};