#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
std::vector<T> flatten(std::vector<std::vector<T>> const& vec)
{
    std::vector<T> flattened;
    for (auto const& v : vec) {
        flattened.insert(flattened.end(), v.begin(), v.end());
    }
    return flattened;
}

class Solution {
public:

    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<vector<int>> diag;

        int s = nums.size();

        for (int r = s - 1; r >= 0; --r) {
            for (int c = 0; c < nums[r].size(); ++c) {
                int sum = r + c;
                if (diag.size() <= sum) {
                    diag.resize(sum+1);
                    diag[sum] = {};
                }
                diag[sum].push_back(nums[r][c]);
            }
        }

        return flatten(diag);


        //int rows, cols;
        //rows = nums.size();
        //int colmax = nums[0].size();

        //vector<int> diags;
        ////diags.reserve(nums.size()*nums.size());
        //int rc;
        //for (int r = 0; r < rows; ++r) {
        //    int sz = nums[r].size();
        //    rc = r;
        //    colmax = sz > colmax ? sz : colmax;
        //    for (int c = 0;; ++c) {
        //        if (nums[rc].size() <= c) {
        //            if (rc == 0) break;
        //            rc--;
        //            continue;
        //        }
        //        else diags.push_back(nums[rc][c]);
        //        if (rc == 0) break;
        //        else --rc;
        //    }
        //}

        //rc = rows - 1;
        //for (int c = 1; c < colmax; c++) {
        //    int cr = c;
        //    for (int r = rows - 1; r >= 0; --r) {
        //        if (nums[r].size() <= cr) {
        //            if (cr == 0) break;
        //            cr++;
        //            continue;
        //        }
        //        else diags.push_back(nums[r][cr]);
        //        if (cr == colmax) break;
        //        else ++cr;
        //    }
        //}

        //return diags;
        //return flattened;
    }
};

void testDiagonalTraverse2() {
    cout << "Traversing diagonally..." << endl << endl;

    Solution s;

    vector<vector<vector<int>>> nums = { { {1,2,3} ,{4,5,6},{7,8,9}},{{1,2,3,4,5},{6,7},{8},{9,10,11},{12,13,14,15,16}}, {{1,2,3},{4},{5,6,7},{8},{9,10,11}} };
    vector<vector<int>> solutions = { {1,4,2,7,5,3,8,6,9},{1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16}, {1,4,2,5,3,8,6,9,7,10,11} };

    //vector<vector<vector<int>>> nums = { {{1,2,3},{4},{5,6,7},{8},{9,10,11}} };
    //vector<vector<int>> solutions = { {1,4,2,5,3,8,6,9,7,10,11} };

    int correct, incorrect;
    correct = incorrect = 0;
    for (int i = 0; i < nums.size(); i++) {
        vector<int> result = s.findDiagonalOrder(nums[i]);
        bool cor = true;
        if (result.size() != solutions[i].size()) {
            cor = false;
            incorrect++;
            break;
        }
        for (int j = 0; j < result.size(); ++j) {
            if (result[j] != solutions[i][j]) cor = false;
        }

        if (cor) {
            correct++;
        }
        else {
            incorrect++;
        }
    }
    cout << "Correct:" << correct << endl;
    cout << "Incorrect:" << incorrect << endl;
    cout << "Correct: " << 100. * correct / nums.size() << "%" << endl;

}