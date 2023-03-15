#include "Tokenizer.h"
#include "SPConstants.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void Tokenizer::setTokens(vector<string> tok) { tokens = tok; };

vector<string> Tokenizer::getTokens() { return this->tokens; }

string Tokenizer::peek() {
  if (this->tokens.empty()) {
    throw std::out_of_range("Error: Insufficient tokens.");
  }
  return this->tokens.front();
}

string Tokenizer::peekTwice() {
  if (this->tokens.size() >= 2) {
    return this->tokens[1];
  }
  throw std::out_of_range("Error: Insufficient tokens.");
}

string Tokenizer::getNextToken() {
  if (tokens.empty()) {
    throw std::out_of_range("Error: Insufficient tokens.");
  }
  string next = this->tokens.front();
  tokens.erase(tokens.begin());
  return next;
}

vector<string> Tokenizer::tokenize(const string &str) {
  // next token
  string next;
  // result vector
  vector<string> result;
  // token delimiters
  const char delimiters_Args[] = {SPConstants::TAB, SPConstants::NEWLINE,
                                  SPConstants::SPACE};
  std::vector<char> delimiters(delimiters_Args, std::end(delimiters_Args));
  // single operator and identifier tokens
  const char identifiers_args[] = {
      SPConstants::RIGHT_BRACE,   SPConstants::LEFT_BRACE,
      SPConstants::RIGHT_BRACKET, SPConstants::LEFT_BRACKET,
      SPConstants::SEMICOLON,     SPConstants::PLUS,
      SPConstants::MINUS,         SPConstants::TIMES,
      SPConstants::DIVIDE,        SPConstants::MODULO,
  };
  std::vector<char> identifiers(identifiers_args, std::end(identifiers_args));
  // special tokens that could be the first token of a double char operator
  const char double_identifiers_args[] = {
      SPConstants::EQUALS, SPConstants::MORE_THAN,  SPConstants::LESS_THAN,
      SPConstants::NOT,    SPConstants::SINGLE_AND, SPConstants::SINGLE_OR};
  std::vector<char> double_identifiers(double_identifiers_args,
                                       std::end(double_identifiers_args));
  // second token of a double char operator token
  const char second_operator_args[] = {
      SPConstants::SINGLE_OR, SPConstants::SINGLE_AND, SPConstants::EQUALS};
  std::vector<char> second_operator(second_operator_args,
                                    std::end(second_operator_args));
  // iterate through the characters of the input string
  for (string::const_iterator it = str.begin(); it != str.end(); it++) {
    char curr = *it;
    // check for delimiters
    if (std::count(delimiters.begin(), delimiters.end(), curr)) {
      if (!next.empty()) {
        result.push_back(next);
        next.clear();
      }
      // check for identifiers
    } else if (std::count(identifiers.begin(), identifiers.end(), curr)) {
      std::string id = std::string(1, curr);
      if (!next.empty()) {
        result.push_back(next);
        result.push_back(id);
        next.clear();
      } else {
        result.push_back(id);
      }
      // check for possible double char operators
    } else if (std::count(double_identifiers.begin(), double_identifiers.end(),
                          curr)) {
      std::string id = std::string(1, curr);
      if (!next.empty() && (std::count(second_operator.begin(),
                                       second_operator.end(), *(it + 1)))) {
        result.push_back(next);
        next.clear();
        result.push_back((id + *(it + 1)));
        it++;
      } else if (!(next.empty()) &&
                 !(std::count(second_operator.begin(), second_operator.end(),
                              *(it + 1)))) {
        result.push_back(next);
        result.push_back(id);
        next.clear();
      } else if (!std::count(second_operator.begin(), second_operator.end(),
                             *(it + 1))) {
        result.push_back(id);
      } else {
        result.push_back(id + *(it + 1));
        it++;
      }
    } else {
      next += *it;
    }
  }
  if (!next.empty())
    result.push_back(next);
  // set tokens of tokenizer
  setTokens(result);
  return result;
}
