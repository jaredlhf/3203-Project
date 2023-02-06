#include "SourceProcessor.h"


SourceProcessor::SourceProcessor(PkbPopulator* populator) {
    pkbPopulator = populator
}

// converts file specified by filename into string, with \n characters removed
std::string SourceProcessor::processFile(std::string &filename) {
    ifstream inputFile;
    inputFile.open(filename);
    stringstream strStream;
    strStream << inputFile.rdbuf();
    string res = strStream.str();
    res.erase(std::remove(res.begin(), res.end(), '\n'), res.end());
    return res;
}

void SourceProcessor::processSimple(std::string &filename) {
    Tokenizer t;
    Parser p;

    std::string fileStr = processFile(filename);
    std::vector<std::string> tokens = t.tokenize(fileStr);
    p.parseProgram(tokens, pkbPopulator);
}