#include "ResultFormatter.h"

ResultFormatter::ResultFormatter(std::vector<std::string> resNames,
                                 std::shared_ptr<QpsTable> resTable) {
  this->resNames = resNames;
  this->resTable = resTable;
}

std::set<std::string> ResultFormatter::getResults() {
  std::vector<int> matchingIndices;
  std::vector<std::string> headers = this->resTable->getHeaders();

  // Add the index of the resName in the header
  for (const std::string &resName : resNames) {
    for (int i = 0; i < headers.size(); i++) {
      const std::string &header = headers[i];

      if (header == resName) {
        matchingIndices.push_back(i);
        break;
      }
    }
  }

  std::set<std::vector<std::string>> data = resTable->getData();
  std::set<std::string> result;
  for (std::vector<std::string> row : data) {
    std::string rowRes = "";
    for (int i : matchingIndices) {
      rowRes += row[i];
      rowRes += " ";
    }
    rowRes.pop_back(); // Remove last whitespace
    result.insert(rowRes);
  }

  return result;
}