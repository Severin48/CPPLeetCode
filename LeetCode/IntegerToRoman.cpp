#include <string>
#include <unordered_map>
#include "Testing.h"

using namespace std;

void addNChars(string& s, char c, int n) {
    for (int j = 0; j < n; ++j) {
        s += c;
    }
}
string intToRoman(int num) {
    unordered_map<char, int> m = { {1,'I'}, {5,'V'}, {10,'X'},{50,'L'}, {100,'C'}, {500,'D'},{1000,'M'} };
    vector<int> nums = { 1000, 500, 100, 50, 10, 5, 1 };
    string res;
    int rem = num;
    int sz = nums.size();
    int r, nChars;
    for (int i = 0; i < sz; ++i) {
        char c = m[nums[i]];
        r = rem;
        nChars = rem / nums[i];
        while (rem >= nums[i]) {
            rem -= nums[i];
            res += c;
        }
        r = rem - nums[i];
        if (i + 2 - ((i + 2) % 2) >= sz) continue;
        int preVal = nums[i + 2 - ((i + 2) % 2)];
        if (-r <= 1 * preVal) {
            char ci = m[preVal];
            r += preVal;
            rem += preVal;
            res += ci;
            res += c;
            rem -= nums[i];
        }
    }
    return res;
}

void testIntegerToRoman() {
    vector<int> inputs = { 3, 58, 1994 };
    vector<string> solutions = { "III", "LVIII", "MCMXCIV" };

    std::function<string(int)> func = intToRoman;
    testResults(inputs, solutions, func, 2);

}