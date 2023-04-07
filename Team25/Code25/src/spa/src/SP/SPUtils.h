#ifndef SPA_SPUTILS_H
#define SPA_SPUTILS_H

#include <stdio.h>
#include <iostream>
#include <unordered_set>

class SPUtils {
private:
    std::unordered_set<std::string> procedures;

public:
    void addProc(std::string procName);
    bool isExistingProc(std::string procName);
};

#endif //SPA_SPUTILS_H
