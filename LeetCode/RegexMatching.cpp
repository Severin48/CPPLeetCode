#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        bool ret = true;
        int ss = s.size();
        int ps = p.size();
        int j = ss - 1;
        char sc = '0';
        char pwc = -1;
        int i = ps - 1;
        for (; i >= 0; --i) {
            if (j < 0) break;
            if (p[i] == s[j] || p[i] == '.') --j;
            else if (p[i] == '*') {
                char wc = p[i - 1];
                --i;
                if (wc == '.') {
                    wc = s[j];
                    if (i > 0) sc = p[i - 1];
                    else return true;
                    while (j >= 0 && s[j] != sc) {
                        --j;
                        pwc = '.';
                    }
                } else if (s[j] == wc) {
                    bool brk = false;
                    if (i > 0) sc = p[i-1];
                    else brk = true;
                    int cnt = 1;
                    while (i >= 0 && (sc == '*' || sc == wc)) {
                        sc = p[i - cnt];
                        cnt--;
                    }
                    while (j >= 0 && wc == s[j] && s[j] != sc) {
                        --j;
                        pwc = wc;
                    }
                    if (brk) break;
                }
            }
            else if (s[j] == pwc) {
                pwc = -1;
                --j;
            }
            else return false;
        }
        while (i >= 0) {
            if (p[i] == '*') i -= 2;
            else if (p[i] == pwc) --i;
            else if (p[i] == '.' && j > -1) --i;
            else return false;
        }
        if (j == 0 && p[0] == '.') return true;
        if (j > -1 || i >= 0) return false;
        return ret;
    }
};

//class Solution {
//public:
//    bool isMatch(string s, string p) {
//        bool ret = true;
//        int ss = s.size();
//        int ps = p.size();
//        int j = 0;
//        for (int i = 0; i < ps; ++i) {
//            if (j >= ss) return false;
//            if (i + 1 < ps && p[i + 1] == '*') {
//                continue;
//            }
//            if (p[i] == '*') {
//                char wc = p[i - 1];
//                if (wc == '.') wc = s[++j];
//                while (j < ss && wc == s[j]) {
//                    ++j;
//                }
//                if (i + 1 < ps && p[i + 1] == wc) {
//                    i += 2;
//                    ++j;
//                }
//            }
//            else if (p[i] != '.' && p[i] != s[j]) return false;
//            else ++j;
//        }
//        if (j < ss) return false;
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

    svec = { "aa", "aa", "ab", "aaa", "abcd", "aaa", "aaca", "a", "b", "aabcbcbcaccbcaabc" };
    pvec = { "a", "a*", ".*", "ab*a*c*a", "d*", "aaaa", "ab*a*c*a", ".*..a*", "a.*", ".*a*aa*.*b*.c*.*a*" };
    solvec = { false, true, true, true, false, false, true, false, false, true };

    svec = { "aabcbcbcaccbcaabc" };
    pvec = { ".*a*aa*.*b*.c*.*a*" };
    solvec = { true };

    //svec = {"aaa" };
    //pvec = { "ab*a*c*a" };
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