#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include <unordered_set>

class AttributeStore {
  virtual void addAttr(std::string attribute, int lineNum) = 0;
  virtual std::string getAttr(int lineNum) = 0;
  virtual std::unordered_set<int> getStmt(std::string attribute) = 0;
  virtual bool hasAttr(std::string attribute) = 0;
  virtual bool hasStmt(int lineNum) = 0;
  virtual std::unordered_set<std::string> getAllAttr() = 0;
  virtual std::unordered_set<int> getAllStmt() = 0;
};

class PrintAttribute : public AttributeStore {
private:
  std::unordered_map<int, std::string> attrStore;
  std::unordered_map<std::string, std::unordered_set<int>> stmtStore;

public:
  PrintAttribute();
  PrintAttribute(
      std::unordered_map<int, std::string> attrStore,
      std::unordered_map<std::string, std::unordered_set<int>> stmtStore);

  void addAttr(std::string attribute, int lineNum) override;
  std::string getAttr(int lineNum) override;
  std::unordered_set<int> getStmt(std::string attribute) override;
  bool hasAttr(std::string attribute) override;
  bool hasStmt(int lineNum) override;
  std::unordered_set<std::string> getAllAttr() override;
  std::unordered_set<int> getAllStmt() override;
};

class ReadAttribute : public AttributeStore {
private:
  std::unordered_map<int, std::string> attrStore;
  std::unordered_map<std::string, std::unordered_set<int>> stmtStore;

public:
  ReadAttribute();
  ReadAttribute(
      std::unordered_map<int, std::string> attrStore,
      std::unordered_map<std::string, std::unordered_set<int>> stmtStore);

  void addAttr(std::string attribute, int lineNum) override;
  std::string getAttr(int lineNum) override;
  std::unordered_set<int> getStmt(std::string attribute) override;
  bool hasAttr(std::string attribute) override;
  bool hasStmt(int lineNum) override;
  std::unordered_set<std::string> getAllAttr() override;
  std::unordered_set<int> getAllStmt() override;
};

class CallAttribute : public AttributeStore {
private:
  std::unordered_map<int, std::string> attrStore;
  std::unordered_map<std::string, std::unordered_set<int>> stmtStore;

public:
  CallAttribute();
  CallAttribute(
      std::unordered_map<int, std::string> attrStore,
      std::unordered_map<std::string, std::unordered_set<int>> stmtStore);

  void addAttr(std::string attribute, int lineNum) override;
  std::string getAttr(int lineNum) override;
  std::unordered_set<int> getStmt(std::string attribute) override;
  bool hasAttr(std::string attribute) override;
  bool hasStmt(int lineNum) override;
  std::unordered_set<std::string> getAllAttr() override;
  std::unordered_set<int> getAllStmt() override;
};
