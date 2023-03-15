#pragma once

#include "QpsTable.h"

class ResultFormatter {
private:
  std::vector<std::string> resNames;
  std::shared_ptr<QpsTable> resTable;

public:
  ResultFormatter(std::vector<std::string> resNames,
                  std::shared_ptr<QpsTable> resTable);
  std::set<std::string> getResults();
};