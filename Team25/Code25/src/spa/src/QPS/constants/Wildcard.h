#pragma once

#include <string>
#include <memory>
#include "Entity.h"

class Wildcard : public Entity {
private:
	std::string val = "";
	Wildcard();
	Wildcard(const std::string& val);

public:
	// Overriden functions from parent class
	virtual bool isSynonym() override;
	virtual bool isConstant() override;
	virtual bool isWildcard() override;

	// Factory function
	static std::shared_ptr<Wildcard> create(const std::string& val);
	static std::shared_ptr<Wildcard> create();

	// Value class functions
	const std::string& getVal() const;
	bool isGenericWildcard();
};