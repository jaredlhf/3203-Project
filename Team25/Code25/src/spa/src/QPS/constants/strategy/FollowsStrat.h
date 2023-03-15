#pragma once

#include "ClauseStrat.h"

class ClauseStrat;

class FollowsStrat : public ClauseStrat {
private:
  // Strategy functions used
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>
  wildcardWildcard();
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> wildcardConst();
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> wildcardSyn();
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> constWildcard();
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> constConst();
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> constSyn();
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> synWildcard();
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> synConst();
  std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> synSyn();

public:
  // Constructor function for Strat
  FollowsStrat(std::string clauseKeyword, std::shared_ptr<Entity> arg1,
               std::shared_ptr<Entity> arg2,
               std::shared_ptr<PkbRetriever> pkbRet);

  // Overriden functions for ClauseStrat
  virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>
  resolve() override;

  // Factory function for strategy used
  virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>>
  createReturnStrategy() override;
};