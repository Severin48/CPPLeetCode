#include <string>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p, int skippedWCs = -1, bool call_recursive=true) {
        bool ret = true;
        int ss = s.size();
        int ps = p.size();
        char sc = -1;
        char pwc = -1;
        int i = ps - 1;
        int j = ss - 1;
        int pwcCount = 0;
        int virtI, leaveOut, lastToLeaveOutIdx, lastIdx, mtc;
        string leaveOutStr;
        char lc = -1;
        char leaveChar = -1;
        while (i >= 0 && j >= 0) {
            char cp = p[i];
            if (cp == s[j] || cp == '.') {
                --j;
                --i;
            }
            else if (cp == '*') {
                if (skippedWCs > 0) {
                    skippedWCs--;
                    i -= 2;
                    continue;
                }
                lc = p[i - 1]; // Can never be -1 according to question description
                if (lc == s[j]) {
                    leaveOut = 0;
                    //lastToLeaveOutIdx = -1;
                    leaveChar = -1;
                    leaveOutStr = "";
                    for (int i2 = 0; i2 < i; i2++) {
                        if (i2 + 1 < ps && p[i2 + 1] == '*') i2++; // Skip 2 (1 in loop head)
                        else {
                            leaveOut++;
                            //lastToLeaveOutIdx = i2;
                            leaveChar = p[i2];
                            leaveOutStr += leaveChar;
                        }
                    }
                    lastIdx = -1;
                    mtc = 0;
                    for (int j2 = 0; j2 < ss; ++j2) {
                        if (mtc >= leaveOutStr.size()) break;
                        if (leaveOutStr[mtc] == '.' || leaveOutStr[mtc] == s[j2]) {
                            lastIdx = j2;
                            mtc++;
                        }
                    }
                    
                    char leftOflc = -1;
                    if (i > 1) leftOflc = p[i - 2];
                    while (j > lastIdx && j > -1 && lc == s[j]) {
                        --j;
                    }
                    if (leftOflc == lc) --i;

                    i -= 2;
                }
                else if (lc == '.') {
                    i -= 2;
                    virtI = i;
                    leaveOut = 0;
                    leaveChar = -1;
                    leaveOutStr = "";
                    for (int i2 = 0; i2 <= i; i2++) {
                        if (i2 + 1 < ps && p[i2 + 1] == '*') i2++; // Skip 2 (1 in loop head)
                        else {
                            leaveOut++;
                            leaveChar = p[i2];
                            leaveOutStr += leaveChar;
                        }
                    }
                    if (leaveOut == 0) return true;
                    char lastChar = -1;
                    while (virtI >= 0 && sc == -1) {
                        char cc = p[virtI];
                        if (cc == '*') {
                            virtI -= 2;
                        }
                        else {
                            sc = cc;
                            i = virtI;
                        }
                    }
                    if (sc == -1) j = leaveOut-1;
                    else {
                        lastIdx = -1;
                        mtc = 0;
                        for (int j2 = 0; j2 < ss; ++j2) {
                            if (mtc >= leaveOutStr.size()) break;
                            if (leaveOutStr[mtc] == '.' || leaveOutStr[mtc] == s[j2]) {
                                lastIdx = j2;
                                mtc++;
                            }
                        }
                        if (lastIdx == -1) return false;
                        else j = lastIdx;
                    }
                    if (sc == -1 && leaveOut == 0) return true;
                }
                else {
                    i -= 2;
                }
            }
            else {
                if (call_recursive) {
                    bool matching = false;
                    int toSkip = 1;
                    int maxSkip = ps / 2;
                    while (toSkip <= maxSkip && !matching) {
                        matching = isMatch(s, p, toSkip, false);
                        toSkip++;
                    }
                    return matching;
                }
                return false;
            }
        }
        while (i >= 0) {
            if (p[i] == '*') i -= 2;
            else if (p[i] == '.' && j > -1) --i;
            else return false;
        }
        if (j > -1 || i > -1) return false;
        else return true;
    }
};


void testRegexMatching() {
    Solution s;
    int correct = 0;
    int incorrect = 0;
    vector<string> svec;
    vector<string> pvec;
    vector<bool> solvec;

    svec = { "aa", "aa", "ab", "aaa", "abcd", "aaa", "aaca", "a", "b", "aabcbcbcaccbcaabc",
        "aaa", "a", "abcdede", "abbabaaaaaaacaa", "bcaccbbacbcbcab", "cabbbbcbcacbabc", "abcaaaaaaabaabcabac",
        "baabbbaccbccacacc","aabccbcbacabaab", "abbbaabccbaabacab","abcbccbcbaabbcbb", "aacaababacccccabac"};
    pvec = { "a", "a*", ".*", "ab*a*c*a", "d*", "aaaa", "ab*a*c*a", ".*..a*", "a.*", ".*a*aa*.*b*.c*.*a*", ".a", "..*", "ab.*de",
        "a*.*b.a.*c*b*a*c*", "b*.c*..*.b*b*.*c*",".*b.*.ab*.*b*a*c", ".*ab.a.*a*a*.*b*b*","c*..b*a*a.*a..*c",".*c*a*b.*a*ba*bb*",
        "ab*b*b*bc*ac*.*bb*", "c*a.*ab*.*ab*a*..b*", ".*c*.*abab*c*a*c" };
    solvec = { false, true, true, true, false, false, true, false, false, true, false, true, true, true, true, true, true,true,
    true, true, true, true};

    for (size_t i = 0; i < svec.size(); i++) {
        bool res = s.isMatch(svec[i], pvec[i]);

        if (res == solvec[i]) correct++;
        else {
            incorrect++;
            std::cout << "Problem " << i << ":\tExpected: " << solvec[i] << "\t -- got -- \t" << res << std::endl;
        }
    }

    std::cout << std::endl;

    float percentage = 100. * correct / svec.size();
    std::cout << "Correct: " << correct << std::endl;
    std::cout << "Incorrect: " << incorrect << std::endl;
    std::cout << "Accuracy: " << percentage << "%" << std::endl;

}