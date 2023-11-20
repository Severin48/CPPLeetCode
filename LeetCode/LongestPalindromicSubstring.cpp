#include <string>
#include <iostream>
#include <vector>
#include "LongestPalindromicSubstring.h"

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        string palindrome = "";
        string maxPal;
        int size = s.size();
        int counter = 0;
        int max = -1;

        for (int i = 0; i < size; i++) {
            int cs = size - i;
            int m = cs / 2;
            int mod = 1 - (cs % 2);
            int offset = 0;
            if (max > size - i) return maxPal;
            while (cs > m + offset && s[m + offset] == s[m - offset - mod]) {
                if (m - offset - mod != m + offset) {
                    palindrome = s[m + offset] + palindrome;
                    counter++;
                }
                palindrome += s[m + offset];
                counter++;
                offset++;
            }
            if (counter > max) {
                maxPal = palindrome;
                max = counter;
            }

            if (max > size - i) return maxPal;

            palindrome = "";
            counter = 0;
            offset = 0;
            cs = size + i;
            m = cs / 2;

            while (cs > m + offset && s[m + offset] == s[m - offset - mod]) {
                if (m - offset - mod != m + offset) {
                    palindrome = s[m + offset] + palindrome;
                    counter++;
                }
                palindrome += s[m + offset];
                counter++;
                offset++;
            }
            if (counter > max) {
                maxPal = palindrome;
                max = counter;
            }
            palindrome = "";
            counter = 0;
        }
        return maxPal;
    }
};

void testPalindrome1() {
    cout << "Finding longest palindrome..." << endl << endl;

    Solution s;

    vector<string> strings = { "babad", "cbbd", "abb", "aacabdkacaa", "caba" };
    vector<string> palindromes = { "aba", "bb", "bb", "aca", "aba" };

    //vector<string> strings = { "caba" };
    //vector<string> palindromes = { "aba" };

    int correct, incorrect;
    correct = incorrect = 0;
    for (int i = 0; i < strings.size(); i++) {
        string result = s.longestPalindrome(strings[i]);
        if (result == palindromes[i]) {
            correct++;
            cout << "Correct: " << result << endl;
        }
        else {
            incorrect++;
            cout << "Incorrect: " << result << endl;
        }
    }
    cout << "Correct:" << correct << endl;
    cout << "Incorrect:" << incorrect << endl;
    cout << "Correct: " << 100. * correct / strings.size() << "%" << endl;
}