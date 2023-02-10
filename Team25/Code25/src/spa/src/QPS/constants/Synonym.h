#pragma once

#include <string>
#include <unordered_set>
#include <memory>
#include "Entity.h"


class Synonym : public Entity {
protected:
    std::unordered_set<std::string> matches;
    std::string name;
    std::string keyword;

public:
    // Constructor functions
    Synonym();
    Synonym(const std::string& inputName);

    // Synonym instance functions
    bool matchesKeyword(const std::string& inputString);
    bool matchesName(const std::string& inputName);
    void addMatchingResult(const std::string& result);
    virtual std::unordered_set<std::string> getMatches();
    virtual bool isStmtRef();

    // Static functions
    static std::shared_ptr<Synonym> create(const std::string& type, const std::string& name);

    // Overriden functions
    bool isConstant() override;
    bool isSynonym() override;
    bool isWildcard() override;
};

class StmtSynonym : public Synonym {
public:
    StmtSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class ReadSynonym : public Synonym {
public:
    ReadSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class PrintSynonym : public Synonym {
public:
    PrintSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class CallSynonym : public Synonym {
public:
    CallSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class WhileSynonym : public Synonym {
public:
    WhileSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class IfSynonym : public Synonym {
public:
    IfSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class AssignSynonym : public Synonym {
public:
    AssignSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class VariableSynonym : public Synonym {
public:
    VariableSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class ConstantSynonym : public Synonym {
public:
    ConstantSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class ProcedureSynonym : public Synonym {
public:
    ProcedureSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class SyntaxErrorSynonym : public Synonym {
public:
    SyntaxErrorSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};

class SemanticErrorSynonym : public Synonym {
public:
    SemanticErrorSynonym(const std::string& name);
    virtual bool isStmtRef() override;
};
