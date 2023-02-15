#pragma once

#include<stdio.h>
#include <iostream>
#include <unordered_set>

template<typename T>
class EntityInterface {
public:
	virtual void add(T value) = 0;
	virtual std::unordered_set<T> getAll() = 0;
	virtual bool has(T value) = 0;
	virtual int size() = 0;
	virtual void clear() = 0;
};