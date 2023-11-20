#include <vector>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
public:
    void getDigits(vector<int>& vec, int x) {
        vec.clear();
        stack<int> sd;
        while (x > 0)
        {
            int digit = x % 10;
            x /= 10;
            vec.push_back(digit);
        }
    }

    bool isHappy(int n) {
        unordered_map<int, int> umap;
        vector<int> digits;
        getDigits(digits, n);
        int number = n;
        unsigned long sum = 0;

        do {
            sum = 0;
            for (int i = 0; i < digits.size(); i++) {
                // if (digits[i] > INT_MAX/2) return false;
                int sq = digits[i] * digits[i];
                sum += sq;
            }
            if (umap.find(sum) == umap.end()) umap[sum] = 1;
            else return false;
            if (sum == 1) return true;
            getDigits(digits, sum);
        } while (sum < INT_MAX);
        return false;
    }
};

void testIsHappy() {
    Solution s;

    bool result = s.isHappy(19);
    cout << (result == true) << endl;
}