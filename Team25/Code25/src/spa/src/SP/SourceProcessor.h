#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "Parser.h"
#include "SelectiveExtractor.h"
#include "Tokenizer.h"

#include "PKB/PkbPopulator.h"

class SourceProcessor {
public:
  std::string processFile(std::string &filename);
  void processSimple(std::string &filename,
                     std::shared_ptr<PkbPopulator> pkbPopulator);
};
