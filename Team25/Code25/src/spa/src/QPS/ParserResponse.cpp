#include "ParserResponse.h";

using namespace std;

void ParserResponse::setDeclarations(vector<vector<string>> declarations) {
    ParserResponse::declarations = declarations;
    return;
}

vector<vector<string>> ParserResponse::getDeclarations() {
    return ParserResponse::declarations;
}

void ParserResponse::setSynonym(string synonym) {
    ParserResponse::synonym = synonym;
    return;
}

string ParserResponse::getSynonym() {
    return ParserResponse::synonym;
}

bool ParserResponse::compare(ParserResponse a, ParserResponse b) {
    return a.getSynonym() == b.getSynonym() && a.getDeclarations() == b.getDeclarations();
}