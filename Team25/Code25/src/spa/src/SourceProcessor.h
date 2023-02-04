#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "Tokenizer.h"
#include "Parser.h"

class SourceProcessor {
public:
    string processFile(string &filename);
    void processSimple(string &filename);
};
