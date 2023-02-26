#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
//TODO Delete if unused

/*
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
	ConstantStore();
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
	VariableStore();
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
	ProcedureStore();
	ProcedureStore(std::unordered_set<std::string> store);
	void add(std::string value) override;
	std::unordered_set<std::string> getAll() override;
	bool has(std::string value) override;
	int size() override;
	void clear() override;
};

*/