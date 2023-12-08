#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include "Testing.h"

using namespace std;

vector<string> merge_vecs(vector<string>& v1, vector<string>& v2) {
    int ts = v1.size() * v2.size();
    vector<string> ret;
    ret.reserve(ts);
    for (int i = 0; i < v1.size(); ++i) {
        for (int j = 0; j < v2.size(); ++j) {
            ret.push_back(v1[i] + v2[j]);
        }
    }
    return ret;
}

vector<string> letterCombinations(string digits) {
    if (digits == "") return {};
    unordered_map<string, vector<string>> m = { {"2", {"a", "b", "c"}},{"3", {"d", "e", "f"}},{"4", {"g", "h", "i"}},
    {"5", {"j", "k", "l"}},{"6", {"m", "n", "o"}},{"7", {"p", "q", "r", "s"}},{"8", {"t", "u", "v"}},
    {"9", {"w", "x", "y", "z"}} };

    if (digits.size() == 1) {
        return m[digits];
    }
    vector<string> ret = m[string() + digits[digits.size() - 1]];
    unordered_map<string, vector<string>> dp;
    while (digits.size() > 1) {
        digits.pop_back();
        ret = merge_vecs(m[string() + digits[digits.size() - 1]], ret);
    }
    return ret;
}

void testLetterCombinationsOfAPhoneNumber() {
    vector<string> inputs = { "23", "", "2" };
    vector<vector<string>> outputs = { {"ad","ae","af","bd","be","bf","cd","ce","cf"}, {}, {"a", "b", "c"} };

    function<vector<string>(string)> func = letterCombinations;
    testResults(inputs, outputs, func, 2);
}