#include "SPUtils.h"

void SPUtils::addProc(std::string procName) {
    procedures.insert(procName);
}

bool SPUtils::isExistingProc(std::string procName) {
    return procedures.find(procName) != procedures.end();
}