#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>

// include your other headers here
#include "AbstractWrapper.h"
#include "SP/SourceProcessor.h"
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
