#include "Synonym.h"
#include "Constants.h"


// Base Synonym class methods
Synonym::Synonym() {
    name = "";
}

// Synonym instance methods
Synonym::Synonym(const std::string& inputName) {
    name = inputName;
}

bool Synonym::matchesKeyword(const std::string& inputString) {
    return inputString == keyword;
}

bool Synonym::matchesName(const std::string& inputName) {
    return inputName == name;
}

void Synonym::addMatchingResult(const std::string& result) {
    matches.insert(result);
}

std::unordered_set<std::string> Synonym::getMatches() {
    return matches;
}

// Factory class for Synonyms
std::shared_ptr<Synonym> Synonym::create(const std::string& type, const std::string& name) {
    if (type == Constants::STMT) return std::make_shared<StmtSynonym>(StmtSynonym(name));
    if (type == Constants::READ) return std::make_shared<ReadSynonym>(ReadSynonym(name));
    if (type == Constants::PRINT) return std::make_shared<PrintSynonym>(PrintSynonym(name));
    if (type == Constants::CALL) return std::make_shared<CallSynonym>(CallSynonym(name));
    if (type == Constants::WHILE) return std::make_shared<WhileSynonym>(WhileSynonym(name));
    if (type == Constants::IF) return std::make_shared<IfSynonym>(IfSynonym(name));
    if (type == Constants::ASSIGN) return std::make_shared<AssignSynonym>(AssignSynonym(name));
    if (type == Constants::VARIABLE) return std::make_shared<VariableSynonym>(VariableSynonym(name));
    if (type == Constants::CONSTANT) return std::make_shared<ConstantSynonym>(ConstantSynonym(name));
    if (type == Constants::PROCEDURE) return std::make_shared<ProcedureSynonym>(ProcedureSynonym(name));
    
    return std::make_shared<Synonym>(Synonym(name));
}

// Overriden methods from Entity parent class
bool Synonym::isConstant() {
    return false;
}

bool Synonym::isSynonym() {
    return true;
}

bool Synonym::isWildcard() {
    return false;
}

// Concrete Synonym class overriden methods
StmtSynonym::StmtSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::STMT;
}

ReadSynonym::ReadSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::READ;
}

PrintSynonym::PrintSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::PRINT;
}

CallSynonym::CallSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::CALL;
}

WhileSynonym::WhileSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::WHILE;
}

IfSynonym::IfSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::IF;
}

AssignSynonym::AssignSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::ASSIGN;
}

VariableSynonym::VariableSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::VARIABLE;
}

ConstantSynonym::ConstantSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::CONSTANT;
}

ProcedureSynonym::ProcedureSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::PROCEDURE;
}

SyntaxErrorSynonym::SyntaxErrorSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::SYNTAX_ERROR;
}

SemanticErrorSynonym::SemanticErrorSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::SEMANTIC_ERROR;
}