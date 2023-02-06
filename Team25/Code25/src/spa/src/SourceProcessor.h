#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "Tokenizer.h"
#include "Parser.h"
#include "PKB/PkbPopulator.h"

class SourceProcessor {
private:
    PkbPopulator* pkbPopulator;
public:
    SourceProcessor(PkbPopulator* pkbPopulator);
    std::string processFile(std::string &filename);
    void processSimple(std::string &filename);
};
