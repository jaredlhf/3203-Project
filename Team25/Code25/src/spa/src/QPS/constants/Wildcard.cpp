#include "Wildcard.h"

// Private constructor functions
Wildcard::Wildcard() {

}

Wildcard::Wildcard(const std::string& val) {
	this->val = val;
}

// Overriden functions from Entity class
bool Wildcard::isSynonym() {
	return false;
}

bool Wildcard::isConstant() {
	return false;
}

bool Wildcard::isWildcard() {
	return true;
}

// Factory function
std::shared_ptr<Wildcard> Wildcard::create(const std::string& val) {
	return std::make_shared<Wildcard>(Wildcard(val));
}

// Factory function for generic wildcard
std::shared_ptr<Wildcard> Wildcard::create() {
	return std::make_shared<Wildcard>(Wildcard());
}

const std::string& Wildcard::getVal() const {
	return this->val;
}

bool Wildcard::isGenericWildcard() {
	return this->val == "";
}
