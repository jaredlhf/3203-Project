#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

class AttributeStore {
	virtual void addAttr(std::string attribute, int lineNum) = 0;
	virtual std::string getAttr(int lineNum) = 0;
	virtual std::unordered_set<int> getStmt(std::string attribute) = 0;
	virtual bool hasAttr(std::string attribute) = 0;
	virtual bool hasStmt(int lineNum) = 0;
};

class PrintAttribute : AttributeStore {
private:
	std::unordered_map<int, std::string> attrStore;
	std::unordered_map<std::string, std::unordered_set<int>> stmtStore;
public:
	PrintAttribute();
	PrintAttribute(std::unordered_map<int, std::string> attrStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore);

	void addAttr(std::string attribute, int lineNum) override;
	std::string getAttr(int lineNum) override;
	std::unordered_set<int> getStmt(std::string attribute) override;
	bool hasAttr(std::string attribute) override;
	bool hasStmt(int lineNum) override;
};

class ReadAttribute : AttributeStore {
private:
	std::unordered_map<int, std::string> attrStore;
	std::unordered_map<std::string, std::unordered_set<int>> stmtStore;
public:
	ReadAttribute();
	ReadAttribute(std::unordered_map<int, std::string> attrStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore);

	void addAttr(std::string attribute, int lineNum) override;
	std::string getAttr(int lineNum) override;
	std::unordered_set<int> getStmt(std::string attribute) override;
	bool hasAttr(std::string attribute) override;
	bool hasStmt(int lineNum) override;
};

class CallAttribute : AttributeStore {
private:
	std::unordered_map<int, std::string> attrStore;
	std::unordered_map<std::string, std::unordered_set<int>> stmtStore;
public:
	CallAttribute();
	CallAttribute(std::unordered_map<int, std::string> attrStore, std::unordered_map<std::string, std::unordered_set<int>> stmtStore);

	void addAttr(std::string attribute, int lineNum) override;
	std::string getAttr(int lineNum) override;
	std::unordered_set<int> getStmt(std::string attribute) override;
	bool hasAttr(std::string attribute) override;
	bool hasStmt(int lineNum) override;
};
