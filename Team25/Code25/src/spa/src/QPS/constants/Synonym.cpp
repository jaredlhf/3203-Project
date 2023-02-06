#include <string>
#include <unordered_set>
#include "Synonym.h"
#include "Constants.h"

using namespace std;

// Base Synonym class methods
Synonym::Synonym() {
    name = "";
}

Synonym::Synonym(string inputName) {
    name = inputName;
}

bool Synonym::matchesKeyword(string inputString) {
    return inputString == keyword;
}

bool Synonym::matchesName(string inputName) {
    return inputName == name;
}

void Synonym::addMatchingResult(string result) {
    matches.insert(result);
}

unordered_set<string> Synonym::getMatches() {
    return matches;
}

Synonym Synonym::create(string type, string name) {
    if (type == Constants::STMT) return StmtSynonym(name);
    if (type == Constants::READ) return ReadSynonym(name);
    if (type == Constants::PRINT) return PrintSynonym(name);
    if (type == Constants::CALL) return CallSynonym(name);
    if (type == Constants::WHILE) return WhileSynonym(name);
    if (type == Constants::IF) return IfSynonym(name);
    if (type == Constants::ASSIGN) return AssignSynonym(name);
    if (type == Constants::VARIABLE) return VariableSynonym(name);
    if (type == Constants::CONSTANT) return ConstantSynonym(name);
    if (type == Constants::PROCEDURE) return ProcedureSynonym(name);
    
    return Synonym(name);
}

// Concrete Synonym class overriden methods
StmtSynonym::StmtSynonym(string name) : Synonym(name) {
    keyword = Constants::STMT;
}

ReadSynonym::ReadSynonym(string name) : Synonym(name) {
    keyword = Constants::READ;
}

PrintSynonym::PrintSynonym(string name) : Synonym(name) {
    keyword = Constants::PRINT;
}

CallSynonym::CallSynonym(string name) : Synonym(name) {
    keyword = Constants::CALL;
}

WhileSynonym::WhileSynonym(string name) : Synonym(name) {
    keyword = Constants::WHILE;
}

IfSynonym::IfSynonym(string name) : Synonym(name) {
    keyword = Constants::IF;
}

AssignSynonym::AssignSynonym(string name) : Synonym(name) {
    keyword = Constants::ASSIGN;
}

VariableSynonym::VariableSynonym(string name) : Synonym(name) {
    keyword = Constants::VARIABLE;
}

ConstantSynonym::ConstantSynonym(string name) : Synonym(name) {
    keyword = Constants::CONSTANT;
}

ProcedureSynonym::ProcedureSynonym(string name) : Synonym(name) {
    keyword = Constants::PROCEDURE;
}