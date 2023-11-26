#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        if (matrix.size() == 0) return 0;
        int area;
        int maxArea = INT_MIN;
        int colSz = matrix[0].size();
        int rowSz = matrix.size();
        vector<int> consOnes(colSz);
        vector<int> counts(rowSz+1);

        for (int r = rowSz - 1; r >= 0; --r) {
            area = 0;
            for (int c = 0; c < colSz; ++c) {
                if (matrix[r][c] == 1) {
                    consOnes[c]++;
                    counts[consOnes[c]]++;
                    counts[consOnes[c] - 1]--;
                    area = *max_element(counts.begin(), counts.end()) * consOnes[c];
                    if (area > maxArea) maxArea = area;
                }
                else {
                    //counts[consOnes[c]] = 0; // Oder --?
                    consOnes[c] = 0;
                }
            }
            //if (area > maxArea) maxArea = area;
        }
        return maxArea;
    }
};

void testLargestSubmatrixWithRearrangements() {
    Solution s;

    vector<vector<vector<int>>> values = { {{0,0,1},{1,1,1},{1,0,1}}, {{1,0,1,0,1}}, {{1,1,0},{1,0,1}} };
    vector<int> solutions = { 4, 3, 2 };

    int correct, incorrect;
    correct = incorrect = 0;
    for (int i = 0; i < values.size(); i++) {
        bool result = s.largestSubmatrix(values[i]);
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