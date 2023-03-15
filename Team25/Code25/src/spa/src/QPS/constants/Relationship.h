#pragma once

#include "../constants/Constants.h"
#include "../constants/Entity.h"
#include "../constants/Synonym.h"
#include "../constants/Value.h"
#include "../constants/Wildcard.h"
#include "../utils/ParserUtils.h"
#include <string>

class Relationship {
protected:
  std::string keyword;
  std::string arg1;
  std::string arg2;

public:
  // Constructor
  Relationship(const std::string &arg1, const std::string &arg2);

  // instance functions
  std::string getKeyword();
  bool compare(std::shared_ptr<Relationship> other);

  // static class functions
  static std::shared_ptr<Relationship> create(const std::string &keyword,
                                              const std::string &arg1,
                                              const std::string &arg2);

  // functions to override
  virtual std::vector<std::shared_ptr<Entity>>
  verifyRelationship(std::vector<std::shared_ptr<Synonym>> declarations);
};

class FollowsRelationship : public Relationship {
public:
  FollowsRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class FollowsSTRelationship : public Relationship {
public:
  FollowsSTRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class ParentRelationship : public Relationship {
public:
  ParentRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class ParentSTRelationship : public Relationship {
public:
  ParentSTRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class UsesRelationship : public Relationship {
public:
  UsesRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class ModifiesRelationship : public Relationship {
public:
  ModifiesRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class CallsRelationship : public Relationship {
public:
  CallsRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class CallsSTRelationship : public Relationship {
public:
  CallsSTRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class NextRelationship : public Relationship {
public:
  NextRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};

class NextSTRelationship : public Relationship {
public:
  NextSTRelationship(const std::string &arg1, const std::string &arg2);
  virtual std::vector<std::shared_ptr<Entity>> verifyRelationship(
      std::vector<std::shared_ptr<Synonym>> declarations) override;
};