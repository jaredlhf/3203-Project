#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>
#include <string>

#include "EntityInterface.h"

/*Generic Class for EntityStores: ConstantStore, ProcedureStore, VariableStore. 
Implements EntityInterface.*/ 
template<typename T>
class EntityStore : public EntityInterface<T> {
private:
	std::unordered_set<T> store;
public:
	EntityStore();
	void add(T value) override;
	std::unordered_set<T> getAll() override;
	bool has(T value) override;
	int size() override;
	void clear() override;
};

template<typename T>
EntityStore<T>::EntityStore() {}

template<typename T>
void EntityStore<T>::add(T value) {
	store.emplace(value);
}

template<typename T>
std::unordered_set<T> EntityStore<T>::getAll() {
	return store;
}

template<typename T>
bool EntityStore<T>::has(T value) {
	if (store.find(value) != store.end()) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
int EntityStore<T>::size() {
	return store.size();
}

template<typename T>
void EntityStore<T>::clear() {
	store.clear();
}

typedef EntityStore<int> ConstantStore;
typedef EntityStore<std::string> ProcedureStore;
typedef EntityStore<std::string> VariableStore;

