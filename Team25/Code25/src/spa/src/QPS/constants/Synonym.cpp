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

// Synonym instance methods
Synonym::Synonym(const std::string& inputName, const std::string& attrName) {
    name = inputName;
    this->attrName = attrName;
}

bool Synonym::matchesKeyword(const std::string& inputString) {
    return inputString == keyword;
}

bool Synonym::matchesName(const std::string& inputName) {
    return inputName == name;
}

bool Synonym::matchesAttrName(const std::string& atName) {
    return this->attrName == atName;
}

void Synonym::addMatchingResult(const std::string& result) {
    matches.insert(result);
}

std::string Synonym::getName() {
    return this->name;
}

std::string Synonym::getKeyword() {
    return this->keyword;
}

bool Synonym::compare(std::shared_ptr<Synonym> other) {
    return this->name == other->name && this->keyword == other->keyword;
}

std::unordered_set<std::string> Synonym::getMatches() {
    return matches;
}

bool Synonym::isStmtRef() {
    return false;
}

bool Synonym::isVariableSyn() {
    return false;
}

bool Synonym::hasAttrName() {
    return !this->attrName.empty();
}

std::string Synonym::getAttrName() {
    return this->attrName;
}

// Factory class for Synonyms
std::shared_ptr<Synonym> Synonym::create(const std::string& type, const std::string& name) {
    return Synonym::create(type, name, "");
}

std::shared_ptr<Synonym> Synonym::create(const std::string& type, const std::string& name, const std::string& attrName) {
    if (type == Constants::STMT) return std::make_shared<StmtSynonym>(StmtSynonym(name, attrName));
    if (type == Constants::READ) return std::make_shared<ReadSynonym>(ReadSynonym(name, attrName));
    if (type == Constants::PRINT) return std::make_shared<PrintSynonym>(PrintSynonym(name, attrName));
    if (type == Constants::CALL) return std::make_shared<CallSynonym>(CallSynonym(name, attrName));
    if (type == Constants::WHILE) return std::make_shared<WhileSynonym>(WhileSynonym(name, attrName));
    if (type == Constants::IF) return std::make_shared<IfSynonym>(IfSynonym(name, attrName));
    if (type == Constants::ASSIGN) return std::make_shared<AssignSynonym>(AssignSynonym(name, attrName));
    if (type == Constants::VARIABLE) return std::make_shared<VariableSynonym>(VariableSynonym(name, attrName));
    if (type == Constants::CONSTANT) return std::make_shared<ConstantSynonym>(ConstantSynonym(name, attrName));
    if (type == Constants::PROCEDURE) return std::make_shared<ProcedureSynonym>(ProcedureSynonym(name, attrName));
    if (type == Constants::SYNTAX_ERROR) return std::make_shared<SyntaxErrorSynonym>(SyntaxErrorSynonym(name, attrName));
    if (type == Constants::SEMANTIC_ERROR) return std::make_shared<SemanticErrorSynonym>(SemanticErrorSynonym(name, attrName));

    return std::make_shared<Synonym>(Synonym(name, attrName));
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

StmtSynonym::StmtSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::STMT;
}

bool StmtSynonym::isStmtRef() {
    return true;
}

ReadSynonym::ReadSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::READ;
}

ReadSynonym::ReadSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::READ;
}

bool ReadSynonym::isStmtRef() {
    return true;
}

PrintSynonym::PrintSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::PRINT;
}

PrintSynonym::PrintSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::PRINT;
}

bool PrintSynonym::isStmtRef() {
    return true;
}

CallSynonym::CallSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::CALL;
}

CallSynonym::CallSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::CALL;
}

bool CallSynonym::isStmtRef() {
    return true;
}

WhileSynonym::WhileSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::WHILE;
}

WhileSynonym::WhileSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::WHILE;
}

bool WhileSynonym::isStmtRef() {
    return true;
}

IfSynonym::IfSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::IF;
}

IfSynonym::IfSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::IF;
}

bool IfSynonym::isStmtRef() {
    return true;
}

AssignSynonym::AssignSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::ASSIGN;
}

AssignSynonym::AssignSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::ASSIGN;
}

bool AssignSynonym::isStmtRef() {
    return true;
}

VariableSynonym::VariableSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::VARIABLE;
}

VariableSynonym::VariableSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::VARIABLE;
}

bool VariableSynonym::isStmtRef() {
    return false;
}

bool VariableSynonym::isVariableSyn() {
    return true;
}

ConstantSynonym::ConstantSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::CONSTANT;
}

ConstantSynonym::ConstantSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::CONSTANT;
}

bool ConstantSynonym::isStmtRef() {
    return false;
}

ProcedureSynonym::ProcedureSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::PROCEDURE;
}

ProcedureSynonym::ProcedureSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::PROCEDURE;
}

bool ProcedureSynonym::isStmtRef() {
    return false;
}

SyntaxErrorSynonym::SyntaxErrorSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::SYNTAX_ERROR;
}

SyntaxErrorSynonym::SyntaxErrorSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::SYNTAX_ERROR;
}

bool SyntaxErrorSynonym::isStmtRef() {
    return false;
}

SemanticErrorSynonym::SemanticErrorSynonym(const std::string& name) : Synonym(name) {
    keyword = Constants::SEMANTIC_ERROR;
}

SemanticErrorSynonym::SemanticErrorSynonym(const std::string& name, const std::string& attrName) : Synonym(name, attrName) {
    keyword = Constants::SEMANTIC_ERROR;
}

bool SemanticErrorSynonym::isStmtRef() {
    return false;
}