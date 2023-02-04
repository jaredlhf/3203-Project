#include "SourceProcessor.h"

string SourceProcessor::processFile(string &filename) {
    ifstream inputFile;
    inputFile.open(filename);
    stringstream strStream;
    strStream << inputFile.rdbuf();
    string res = strStream.str();
    return res;
}

void SourceProcessor::processSimple(string &filename) {
    Tokenizer t;
    Parser p;

    string fileStr = processFile(filename);
    vector<string> tokens = t.tokenize(fileStr);


    // TODO: parse tokens into AST
}