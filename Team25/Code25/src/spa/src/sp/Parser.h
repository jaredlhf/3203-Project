#pragma once
#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Parser {
    void parseStatement(vector<string> str);
    void parseAssign(vector<string> str);
    bool isValidVariableName(string str);
    bool isNumber(string str);
};;


