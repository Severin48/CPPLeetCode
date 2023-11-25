#include <string>
#include <vector>
#include "Testing.h"

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> strs(numRows, "");
        if (numRows < 2) return s;
        int off = 0;
        int sz = s.size();
        bool asc = true;
        for (int i = 0; i < sz; ++i) {
            strs[off] += s[i];
            if (off == numRows-1) {
                asc = false;
            }
            else if (off == 0) asc = true;
            if (!asc) --off;
            else ++off;
        }
        string ret = "";
        for (int i = 0; i < numRows; ++i) {
            ret += strs[i];
        }
        return ret;
    }
};

void testZigZagConversion() {
    vector<string> ss = { "PAYPALISHIRING","PAYPALISHIRING", "A" };
    vector<int> nRs = { 3,4,1 };

    vector<string> solutions = { "PAHNAPLSIIGYIR","PINALSIGYAHRPI", "A" };

    Solution s;
    int correct, incorrect;
    correct = incorrect = 0;
    for (int i = 0; i < ss.size(); i++) {
        string result = s.convert(ss[i], nRs[i]);

        if (result == solutions[i]) {
            correct++;
        }
        else {
            incorrect++;
            std::cout << "Problem " << i << ": Expected " << solutions[i] << " -- got -- " << result << std::endl;
        }
    }
    cout << "Correct:" << correct << endl;
    cout << "Incorrect:" << incorrect << endl;
    cout << "Correct: " << 100. * correct / solutions.size() << "%" << endl;

}