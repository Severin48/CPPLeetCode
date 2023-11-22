#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include "Testing.h"

using namespace std;

int myAtoi(std::string s) {
    bool negative = false;
    bool positive = false;
    bool numChanged = false;
    long long num = 0;
    for (char c : s) {
        if ((numChanged || negative || positive) && (c < '0' || c > '9')) break;
        if (c == ' ') continue;
        else if (c == '+') positive = true;
        else if (c == '-') negative = true;
        else if (negative && positive) return 0;
        else if (c < '0' || c > '9') break;
        else {
            num = num * 10 + (c - '0');
            numChanged = true;
        }
        if (negative) {
            if (-num < INT_MIN) {
                num = -(long long)INT_MIN;
                break;
            }
        }
        else {
            if (num > INT_MAX) {
                num = INT_MAX;
                break;
            }
        }
    }

    if (negative) {
        num = -num;
    }
    return static_cast<int>(num);
}

void testStringToInteger() {
    vector<string> strings = { "42", "   -42", "4193 with words", "-91283472332", "+-12", "00000-42a1234", "  +  413" };

    vector<int> results = { 42, -42, 4193, -2147483648, 0, 0, 0 };

    std::function<int(std::string)> func = myAtoi;

    testResults(strings, results, 2, func);
}