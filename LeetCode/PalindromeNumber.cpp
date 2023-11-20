#include <iostream>
#include <vector>
#include <string>
#include "PalindromeNumber.h"

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x < 10) return true;
        if (x % 10 == 0) return false;

        string s = to_string(x);
        int size = s.size();
        int i = 0;
        while (i < size && s[i] == s[size - i - 1]) {
            i++;
        }
        if (i < size) return false;
        else return true;
    }
};

void testPalindromeNumber() {
    cout << "Determining whether the number is a palindrome..." << endl << endl;

    Solution s;

    vector<int> values = { 121, -121, 10 , 0};
    vector<bool> solutions = { true, false, false, true};

    int correct, incorrect;
    correct = incorrect = 0;
    for (int i = 0; i < values.size(); i++) {
        bool result = s.isPalindrome(values[i]);
        if (result == solutions[i]) {
            correct++;
            // cout << "Correct: " << result << endl;
        }
        else {
            incorrect++;
            // cout << "Incorrect: " << result << endl;
        }
    }
    cout << "Correct:" << correct << endl;
    cout << "Incorrect:" << incorrect << endl;
    cout << "Correct: " << 100. * correct / values.size() << "%" << endl;
}