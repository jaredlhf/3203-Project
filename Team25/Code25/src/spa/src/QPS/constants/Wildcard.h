#pragma once

#include "Entity.h"
#include <memory>
#include <string>

class Wildcard : public Entity {
private:
  std::string val = "";
  Wildcard();
  Wildcard(const std::string &val);

public:
  // Overriden functions from parent class
  virtual bool isSynonym() override;
  virtual bool isConstant() override;
  virtual bool isWildcard() override;

  // Factory function
  static std::shared_ptr<Wildcard> create(const std::string &val);
  static std::shared_ptr<Wildcard> create();

  // Value class functions
  const std::string &getVal() const;
  bool isGenericWildcard();
  bool compare(std::shared_ptr<Wildcard> other);
};