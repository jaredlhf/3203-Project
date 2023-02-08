#pragma once

#include <string>
#include <unordered_set>


class Synonym {
protected:
    std::unordered_set<std::string> matches;
    std::string name;
    std::string keyword;

public:
    Synonym();
    Synonym(const std::string& inputName);
    bool matchesKeyword(const std::string& inputString);
    bool matchesName(const std::string& inputName);
    void addMatchingResult(const std::string& result);
    std::unordered_set<std::string> getMatches();
    static Synonym create(const std::string& type, const std::string& name);
};

class StmtSynonym : public Synonym {
public:
    StmtSynonym(const std::string& name);
};

class ReadSynonym : public Synonym {
public:
    ReadSynonym(const std::string& name);
};

class PrintSynonym : public Synonym {
public:
    PrintSynonym(const std::string& name);
};

class CallSynonym : public Synonym {
public:
    CallSynonym(const std::string& name);
};

class WhileSynonym : public Synonym {
public:
    WhileSynonym(const std::string& name);
};

class IfSynonym : public Synonym {
public:
    IfSynonym(const std::string& name);
};

class AssignSynonym : public Synonym {
public:
    AssignSynonym(const std::string& name);
};

class VariableSynonym : public Synonym {
public:
    VariableSynonym(const std::string& name);
};

class ConstantSynonym : public Synonym {
public:
    ConstantSynonym(const std::string& name);
};

class ProcedureSynonym : public Synonym {
public:
    ProcedureSynonym(const std::string& name);
};

class SyntaxErrorSynonym : public Synonym {
public:
    SyntaxErrorSynonym(const std::string& name);
};

class SemanticErrorSynonym : public Synonym {
public:
    SemanticErrorSynonym(const std::string& name);
};
