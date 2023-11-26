#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int maxArea = 0;
        int colSz = matrix[0].size();
        int rowSz = matrix.size();
        vector<int> consOnes(colSz);

        for (int r = 0; r < rowSz; ++r) {
            for (int c = 0; c < colSz; ++c) {
                if (matrix[r][c] == 1) {
                    consOnes[c] += 1;
                }
                else {
                    consOnes[c] = 0;
                }
            }

            vector<int> sortedConsOnes = consOnes;
            sort(sortedConsOnes.rbegin(), sortedConsOnes.rend());

            for (int c = 0; c < colSz; ++c) {
                int area = sortedConsOnes[c] * (c + 1);
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
};

void testLargestSubmatrixWithRearrangements() {
    Solution s;

    vector<vector<vector<int>>> values = { {{0,0,1},{1,1,1},{1,0,1}}, {{1,0,1,0,1}}, {{1,1,0},{1,0,1}}, {{0,0},{0,0}},
    {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1},{0,1,1,0,1,1,1,1,0,1,1,0,0,1,0,1,1,1,1,0,1,1,1,1,1,1}},
    {{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,0,0,1,1,1,0,1,0,1,0,1,1,0},{0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,
        1,1,1,1,0,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,0,0,1,1,0,
        0,1,1,0,1,1,1,0,0,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},{1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,
        1},{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1},{1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,1,0,1,1,1,1,
        1,1,1,1,1,1,0,1,1,1,1,1,1,0,1},{1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,1,1},{1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1},{1,1,1,0,0,1,1,0,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,1,1,
        1,1,1,0}}, {{1,1,1,0,1,1,1,0},{1,1,1,1,1,1,1,1},{1,0,1,1,1,1,1,1},{1,0,1,0,0,0,1,1},{0,1,1,0,1,1,1,1},{1,1,0,1,1,1,0,1},{1,1,1,1
        ,1,1,0,0},{1,1,1,1,1,1,1,0},{1,1,1,1,0,1,0,1},{1,0,0,1,1,1,1,1},{1,1,1,0,1,1,1,1},{1,1,1,1,1,0,1,1},{1,0,1,0,0,0,0,0},{0,0,1,1,1
        ,0,1,1},{1,1,0,1,1,1,0,1}}};
    vector<int> solutions = { 4, 3, 2, 0, 34, 75, 16 };

    int correct, incorrect;
    correct = incorrect = 0;
    for (int i = 0; i < values.size(); i++) {
        int result = s.largestSubmatrix(values[i]);
        if (result == solutions[i]) {
            correct++;
            // cout << "Correct: " << result << endl;
        }
        else {
            incorrect++;
            cout << "Problem " << i << " Expected\t" << solutions[i] << "  = got =  " << result << endl;
        }
    }
    cout << endl << "Correct:" << correct << endl;
    cout << "Incorrect:" << incorrect << endl;
    cout << "Correct: " << 100. * correct / values.size() << "%" << endl;
}