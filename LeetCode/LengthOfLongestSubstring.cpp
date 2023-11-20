#include <unordered_map>
#include <iostream>
#include <string>
#include "LengthOfLongestSubstring.h"

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> uMap;
        int max, len, counter, curr_start;
        len = s.length();
        counter = 0;
        max = 0;
        curr_start = 0;
        for (int i = 0; i < len; i++) {
            char c = s[i];
            int diff;
            if (uMap.find(c) == uMap.end() || uMap[c] == i) {
                counter++;
                uMap[c] = i;
            }
            else {
                int prevIdx = uMap[c];
                counter = 1;
                for (int j = curr_start; j <= prevIdx; j++) {
                    uMap.erase(s[j]);
                }
                uMap[c] = i;
                i = prevIdx + 1;
                curr_start = prevIdx + 1;
            }
            if (counter > max) max = counter;

        }
        return max;
    }
};

Solution s;

void test(string s1, int le) {
    cout << s1 << " ----------- " << (s.lengthOfLongestSubstring(s1) == le) << "\t(" << s.lengthOfLongestSubstring(s1) << ") -- " << le << endl;
}

void testLengthOfLongestSubstring() {
    test("bbbbb", 1);
    test("abcabcbb", 3);
    test("aab", 2);
    test("tmmzuxt", 5);
    test("dvdf", 3);
    test("pwwkew", 3);

    // abcabcbb
    // aab
    // tmmzuxt
    // dvdf
    // pwwkew
    // bbbbb
}