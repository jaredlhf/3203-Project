#pragma once

#include <string>
#include <memory>
#include "Entity.h"

class Value : public Entity {
private:
	std::string val;
	Value();
	Value(const std::string& val);

public:
	// Overriden functions from parent class
	virtual bool isSynonym() override;
	virtual bool isConstant() override;
	virtual bool isWildcard() override;

	// Factory function
	static std::shared_ptr<Value> create(const std::string& val);

	// Value class functions
	const std::string& getVal() const;
	bool compare(std::shared_ptr<Value> other);
};