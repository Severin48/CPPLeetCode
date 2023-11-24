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
                        // Hier müsste eig der letzte Index rauskommen - Ich nehme hier falsch an, dass zwischen den leaveOutStr chars alle eine passende wildcard haben
                        if (leaveOutStr[mtc] == '.' || leaveOutStr[mtc] == s[j2]) {
                            lastIdx = j2;
                            mtc++;
                        }
                    }
                    // if (lastIdx == -1) return false;
                    // else j = lastIdx;
                    //int maxIdx = max(lastToLeaveOutIdx, lastIdx); // Beide bs hätten abgezogen werden müssen
                    
                    char leftOflc = -1;
                    if (i > 1) leftOflc = p[i - 2];
                    while (j > lastIdx && j > -1 && lc == s[j]) {
                        --j;
                    }
                    if (leftOflc == lc) --i;

                    i -= 2;
                    //virtI = i;
                    //while (virtI >= 0 && (p[virtI] == lc || p[virtI] == '*' || p[virtI] == '.')) { // virtI > maxIdx &&  
                    //    if (p[virtI] == '*') virtI -= 2;
                    //    else if (p[virtI] == lc) {
                    //        i = virtI - 1;
                    //        break;
                    //    }
                    //    else --virtI;
                    //}
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
                        //else if (cc == '.') {
                        //     --virtI;
                        //}
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

//if (sc == -1) break;
//if (i <= 0) return false;
//bool matching = false;
//int lastIdx = s.find_last_of(sc);
//string sSub = s.substr(0, lastIdx); // Ist der letzte matchende char hier dabei? Sollte nicht
//string pSub = p.substr(0, i);
//matching = isMatch(sSub, pSub);
//while (!matching) {
//    // i offset ist current i, j offset ist find first of
//    lastIdx = sSub.find_last_of(sc);
//    sSub = sSub.substr(0, lastIdx); // Ist der letzte matchende char hier dabei? Sollte nicht
//    pSub = pSub.substr(0, i);
//    matching = isMatch(sSub, pSub);
//}
//return true;

//class Solution {
//public:
//    bool isMatch(string s, string p, int ioff = 0, int joff = 0) {
//        bool ret = true;
//        int ss = s.size();
//        int ps = p.size();
//        char sc = '0';
//        char pwc = -1;
//        int i = ps - 1 - ioff;
//        int j = ss - 1 - joff;
//        int pwcCount = 0;
//        while (i >= 0 && j >= 0) {
//            pwcCount = 0;
//            if (p[i] == s[j] || p[i] == '.') {
//                --j;
//                --i;
//            }
//            else if (p[i] == '*') {
//                char wc = p[i - 1];
//                --i;
//                function<bool()> cond;
//                bool brk = false;
//                wc = s[j];
//                if (wc == '.') {
//                    if (i > 0) sc = p[i - 1];
//                    else return true;
//                    function<bool()> cond = [&]() {return j >= 0 && s[j] != sc; };
//                }
//                else if (s[j] == wc) {
//                    function<bool()> cond = [&]() {return j >= 0 && wc == s[j] && s[j] != sc; };
//                    if (i > 0) sc = p[i - 1];
//                    else brk = true;
//                }
//                int cnt = 1;
//                while (i >= 0 && (sc == '*' || sc == wc)) {
//                    sc = p[i - cnt];
//                    cnt--;
//                    //--i;
//                }
//                while (cond) {
//                    --j;
//                    pwc = wc;
//                    pwcCount++;
//                }
//                --i;
//                if (brk) break;
//            }
//            else if (s[j] == pwc) {
//                pwc = -1;
//                --j;
//                --i;
//            }
//            else return false;
//        }
//        while (i >= 0) {
//            if (p[i] == '*') i -= 2;
//            else if (p[i] == pwc && pwcCount > 0) --i;
//            else if (p[i] == '.' && j > -1) --i;
//            else return false;
//        }
//        if (j == 0 && p[0] == '.') return true;
//        if (j > -1 || i >= 0) return false;
//        return ret;
//    }
//};

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

    //int test_nr = 21;
    //bool res = s.isMatch(svec[test_nr], pvec[test_nr]);

    //if (res == solvec[test_nr]) correct++;
    //else {
    //    incorrect++;
    //    //if (verbose > 1) {
    //    //    std::cout << "Problem " << i << ":\tExpected: " << outputs[i] << "\t -- got -- \t" << result << std::endl;
    //    //}
    //    std::cout << "Problem " << test_nr << ":\tExpected: " << solvec[test_nr] << "\t -- got -- \t" << res << std::endl;
    //}

    //return;

    //svec = { "abcaaaaaaabaabcabac" };
    //pvec = { ".*ab.a.*a*a*.*b*b*" };
    //solvec = { true };
    
    //svec = { "abbabaaaaaaacaa" };
    //pvec = { "a*.*b.a.*c*b*a*c*" };
    //solvec = { true };

    //svec = { "aabcbcbcaccbcaabc" };
    //pvec = { ".*a*aa*.*b*.c*.*a*" };
    //solvec = { true };

    //svec = {"abcdede" };
    //pvec = { "ab.*de" };
    //solvec = { true };

    //svec = {"abcd" };
    //pvec = { "d*" };
    //solvec = { false };

    //svec = {"aaa" };
    //pvec = { "aaaa" };
    //solvec = { false };

    //svec = {"aaca" };
    //pvec = { "ab*a*c*a" };
    //solvec = { true };

    //svec = {"b" };
    //pvec = { "a.*" };
    //solvec = {false};

    for (size_t i = 0; i < svec.size(); i++) {
        bool res = s.isMatch(svec[i], pvec[i]);

        if (res == solvec[i]) correct++;
        else {
            incorrect++;
            //if (verbose > 1) {
            //    std::cout << "Problem " << i << ":\tExpected: " << outputs[i] << "\t -- got -- \t" << result << std::endl;
            //}
            std::cout << "Problem " << i << ":\tExpected: " << solvec[i] << "\t -- got -- \t" << res << std::endl;
        }
    }

    std::cout << std::endl;

    float percentage = 100. * correct / svec.size();
    std::cout << "Correct: " << correct << std::endl;
    std::cout << "Incorrect: " << incorrect << std::endl;
    std::cout << "Accuracy: " << percentage << "%" << std::endl;

}