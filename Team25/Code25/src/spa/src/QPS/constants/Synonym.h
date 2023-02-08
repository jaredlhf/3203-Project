#pragma once

#include <string>
#include <unordered_set>

using namespace std;

class Synonym {
protected:
    unordered_set<string> matches;
    string name;
    string keyword;

public:
    Synonym();
    Synonym(string inputName);
    bool matchesKeyword(string inputString);
    bool matchesName(string inputName);
    void addMatchingResult(string result);
    unordered_set<string> getMatches();
    static Synonym create(string type, string name);
};

class StmtSynonym : public Synonym {
public:
    StmtSynonym(string name);
};

class ReadSynonym : public Synonym {
public:
    ReadSynonym(string name);
};

class PrintSynonym : public Synonym {
public:
    PrintSynonym(string name);
};

class CallSynonym : public Synonym {
public:
    CallSynonym(string name);
};

class WhileSynonym : public Synonym {
public:
    WhileSynonym(string name);
};

class IfSynonym : public Synonym {
public:
    IfSynonym(string name);
};

class AssignSynonym : public Synonym {
public:
    AssignSynonym(string name);
};

class VariableSynonym : public Synonym {
public:
    VariableSynonym(string name);
};

class ConstantSynonym : public Synonym {
public:
    ConstantSynonym(string name);
};

class ProcedureSynonym : public Synonym {
public:
    ProcedureSynonym(string name);
};
