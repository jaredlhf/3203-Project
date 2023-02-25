#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>

template<typename T>
class EntityStore {
public:
	virtual void add(T value) = 0;
	virtual std::unordered_set<T> getAll() = 0;
	virtual bool has(T value) = 0;
	virtual int size() = 0;
	virtual void clear() = 0;
};

class ConstantStore : public EntityStore<int> {
private:
	std::unordered_set<int> store;
public:
	ConstantStore(std::unordered_set<int> store);
	void add(int value) override;
	std::unordered_set<int> getAll() override;
	bool has(int value) override;
	int size() override;
	void clear() override;
};

class VariableStore : public EntityStore<std::string> {
private:
	std::unordered_set<std::string> store;
public:
	VariableStore(std::unordered_set<std::string> store);
	void add(std::string value) override;
	std::unordered_set<std::string> getAll() override;
	bool has(std::string value) override;
	int size() override;
	void clear() override;
};

class ProcedureStore : public EntityStore<std::string> {
private:
	std::unordered_set<std::string> store;
public:
	ProcedureStore(std::unordered_set<std::string> store);
	void add(std::string value) override;
	std::unordered_set<std::string> getAll() override;
	bool has(std::string value) override;
	int size() override;
	void clear() override;
};

class StatementStore : public EntityStore<std::string> {
private:
	std::unordered_map<std::string, std::unordered_set<int>> store;
public:
	StatementStore(std::unordered_map<std::string, std::unordered_set<int>> store);
	
	// overridden but unused
	void add(std::string value) override;
	std::unordered_set<std::string> getAll() override;

	void add(std::string stmtType, int lineNum);
	std::unordered_set<int> getAll(std::string stmtType);
	bool has(std::string stmtType) override;
	int size() override;
	void clear() override;
};