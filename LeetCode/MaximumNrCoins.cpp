#include <vector>
#include <algorithm>
#include "Testing.h"

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(), piles.end());
        int ps = piles.size();
        int s = 0;
        int toAdd = ps / 3;
        for (int i = ps-1; i > toAdd; i -= 2) { // Lowest ps/3 are taken by Bob
            s += piles[i-1];
        }
        return s;
    }
};

void testMaxCoins() {
    vector<vector<int>> pls = { {2,4,1,2,7,8},{2,4,5}, {9,8,7,6,5,1,2,3,4} };
    vector<int> solutions = { 9,4,18 };

    Solution s;
    int correct = 0;
    int incorrect = 0;
    for (size_t i = 0; i < pls.size(); i++) {
        int res = s.maxCoins(pls[i]);

        if (res == solutions[i]) correct++;
        else {
            incorrect++;
            //if (verbose > 1) {
            //    std::cout << "Problem " << i << ":\tExpected: " << outputs[i] << "\t -- got -- \t" << result << std::endl;
            //}
            std::cout << "Problem " << i << ":\tExpected: " << solutions[i] << "\t -- got -- \t" << res << std::endl;
        }
    }

    std::cout << std::endl;

    float percentage = 100. * correct / solutions.size();
    std::cout << "Correct: " << correct << std::endl;
    std::cout << "Incorrect: " << incorrect << std::endl;
    std::cout << "Accuracy: " << percentage << "%" << std::endl;

}