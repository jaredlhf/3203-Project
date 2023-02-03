#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Tokenizer {
public:
    vector<string> tokenize(const string& str);
    string expect(const string& spa,const string& str);
};