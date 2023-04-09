#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "Tokenizer.h"
#include "Parser.h"
#include "SelectiveExtractor.h"
#include "SPUtils.h"

#include "PKB/PkbPopulator.h"

class SourceProcessor {
public:
    std::string processFile(std::string &filename);
    void processSimple(std::string &filename, std::shared_ptr<PkbPopulator> pkbPopulator);
};
