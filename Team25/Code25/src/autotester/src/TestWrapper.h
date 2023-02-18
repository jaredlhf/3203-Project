#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>

// include your other headers here
#include "AbstractWrapper.h"
#include "SourceProcessor.h"
#include "PKB/PkbRetriever.h"
#include "PKB/PkbPopulator.h"
#include "QPS/Qps.h"


class TestWrapper : public AbstractWrapper {
 private:
    SourceProcessor sp;
    Qps qps;
	VariableStore vs;
	ConstantStore cs;
	FollowsStore fs;
	ProcedureStore ps;
	StatementStore ss;
	PatternStore patts;
	FollowsStarStore fstars;
	ModifiesProcStore mprocs;
	ModifiesStore ms;
	ParentStarStore pStars;
	ParentStore parents;
	UsesStore uses;

    std::shared_ptr<VariableStore> vsPointer = std::make_shared<VariableStore>(vs);
    std::shared_ptr<ConstantStore> csPointer = std::make_shared<ConstantStore>(cs);
    std::shared_ptr<FollowsStore> fsPointer = std::make_shared<FollowsStore>(fs);
    std::shared_ptr<ProcedureStore> psPointer = std::make_shared<ProcedureStore>(ps);
    std::shared_ptr<StatementStore> ssPointer = std::make_shared<StatementStore>(ss);
    std::shared_ptr<PatternStore> pattsPointer = std::make_shared<PatternStore>(patts);
	std::shared_ptr<FollowsStarStore> fstarsPointer = std::make_shared<FollowsStarStore>(fstars);
	std::shared_ptr<ModifiesProcStore> mprocsPointer = std::make_shared<ModifiesProcStore>(mprocs);
	std::shared_ptr<ModifiesStore> msPointer = std::make_shared<ModifiesStore>(ms);
	std::shared_ptr<ParentStarStore> pStarsPointer = std::make_shared<ParentStarStore>(pStars);
	std::shared_ptr<ParentStore> parentsPointer = std::make_shared<ParentStore>(parents);
	std::shared_ptr<UsesStore> usesPointer = std::make_shared<UsesStore>(uses);

    PkbRetriever pkbRetriever;
    PkbPopulator pkbPopulator;
 public:
  // default constructor
  TestWrapper();
  
  // destructor
  ~TestWrapper();
  
  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);
  
  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif
