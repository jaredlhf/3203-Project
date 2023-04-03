#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

class AttributeStore {
	virtual void addAttr(std::string attribute, int lineNum) = 0;
	virtual std::string getAttr(int lineNum) = 0;
};

class PrintAttribute : public AttributeStore {
private:
	std::unordered_map<int, std::string> attrStore;
public:
	PrintAttribute();
	PrintAttribute(std::unordered_map<int, std::string> attrStore);

	void addAttr(std::string attribute, int lineNum) override;
	std::string getAttr(int lineNum) override;
};

class ReadAttribute : public AttributeStore {
private:
	std::unordered_map<int, std::string> attrStore;
public:
	ReadAttribute();
	ReadAttribute(std::unordered_map<int, std::string> attrStore);

	void addAttr(std::string attribute, int lineNum) override;
	std::string getAttr(int lineNum) override;
};

class CallAttribute : public AttributeStore {
private:
	std::unordered_map<int, std::string> attrStore;
public:
	CallAttribute();
	CallAttribute(std::unordered_map<int, std::string> attrStore);

	void addAttr(std::string attribute, int lineNum) override;
	std::string getAttr(int lineNum) override;
};
