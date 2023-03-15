#pragma once

#include <string>
#include <unordered_set>
#include <memory>
#include "Entity.h"
#include "QPS/QpsTable.h"
#include "PKB/PkbRetriever.h"


class Synonym : public Entity {
protected:
    std::unordered_set<std::string> matches;
    std::string name;
    std::string keyword;
    std::string attrName;

public:
    // Constructor functions
    Synonym();
    Synonym(const std::string& inputName);
    Synonym(const std::string& inputName, const std::string& attrName);

    // Synonym instance functions
    bool matchesKeyword(const std::string& inputString);
    bool matchesName(const std::string& inputName);
    bool matchesAttrName(const std::string& inputAttrName);
    void addMatchingResult(const std::string& result);
    std::string getName();
    std::string getNameWithAttr();
    std::string getKeyword();
    bool compare(std::shared_ptr<Synonym> other);
    virtual std::unordered_set<std::string> getMatches();
    virtual bool isStmtRef();
    virtual bool isVariableSyn();
    virtual bool hasAttrName();
    std::string getAttrName();
    virtual bool isBooleanSyn();
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveSelectResult(
        std::shared_ptr<PkbRetriever> pkbRet);
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveAttrResult(
        std::shared_ptr<PkbRetriever> pkbRet);

    // Static functions
    static std::shared_ptr<Synonym> create(const std::string& type, const std::string& name);
    static std::shared_ptr<Synonym> create(const std::string& type, const std::string& name, const std::string& attrName);

    // Overriden functions
    bool isConstant() override;
    bool isSynonym() override;
    bool isWildcard() override;
};

class StmtSynonym : public Synonym {
public:
    StmtSynonym(const std::string& name);
    StmtSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveSelectResult(
        std::shared_ptr<PkbRetriever> pkbRet) override;
};

class ReadSynonym : public Synonym {
public:
    ReadSynonym(const std::string& name);
    ReadSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
};

class PrintSynonym : public Synonym {
public:
    PrintSynonym(const std::string& name);
    PrintSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
};

class CallSynonym : public Synonym {
public:
    CallSynonym(const std::string& name);
    CallSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
};

class WhileSynonym : public Synonym {
public:
    WhileSynonym(const std::string& name);
    WhileSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
};

class IfSynonym : public Synonym {
public:
    IfSynonym(const std::string& name);
    IfSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
};

class AssignSynonym : public Synonym {
public:
    AssignSynonym(const std::string& name);
    AssignSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
};

class VariableSynonym : public Synonym {
public:
    VariableSynonym(const std::string& name);
    VariableSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
    virtual bool isVariableSyn() override;
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveSelectResult(
        std::shared_ptr<PkbRetriever> pkbRet) override;
};

class ConstantSynonym : public Synonym {
public:
    ConstantSynonym(const std::string& name);
    ConstantSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveSelectResult(
        std::shared_ptr<PkbRetriever> pkbRet) override;
};

class ProcedureSynonym : public Synonym {
public:
    ProcedureSynonym(const std::string& name);
    ProcedureSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveSelectResult(
        std::shared_ptr<PkbRetriever> pkbRet) override;
};

class BooleanSynonym : public Synonym {
public:
    BooleanSynonym(const std::string& name);
    virtual bool isBooleanSyn() override;
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveSelectResult(
        std::shared_ptr<PkbRetriever> pkbRet) override;
};

class SyntaxErrorSynonym : public Synonym {
public:
    SyntaxErrorSynonym(const std::string& name);
    SyntaxErrorSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveSelectResult(
        std::shared_ptr<PkbRetriever> pkbRet) override;
};

class SemanticErrorSynonym : public Synonym {
public:
    SemanticErrorSynonym(const std::string& name);
    SemanticErrorSynonym(const std::string& name, const std::string& attrName);
    virtual bool isStmtRef() override;
    virtual std::pair<Constants::ClauseResult, std::shared_ptr<QpsTable>> resolveSelectResult(
        std::shared_ptr<PkbRetriever> pkbRet) override;
};
