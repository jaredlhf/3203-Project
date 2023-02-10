#include "Value.h"

// Private constructor functions
Value::Value() {

}

Value::Value(const std::string& val) {
	this->val = val;
}

// Overriden functions from Entity class
bool Value::isSynonym() {
	return false;
}

bool Value::isConstant() {
	return true;
}

bool Value::isWildcard() {
	return false;
}

// Factory function
std::shared_ptr<Value> Value::create(const std::string& val) {
	return std::make_shared<Value>(Value(val));
}

// Value class functions
const std::string& Value::getVal() const {
	return this->val;
}

bool Value::compare(std::shared_ptr<Value> other) {
	return this->val == other->val;
}
