#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        int l = 0;
        int r = nums.size() - 1;
        int m;

        if (r == 0) {
            if (nums[0] >= target) return 0;
            else return 1;
        }

        while (l < r) {
            m = floor((l + r) / 2);
            if (nums[m] < target) l = m + 1;
            else r = m;
        }
        if (nums[m] == target) return m;
        if (nums[l] < target) return l + 1;
        else return l;
    }
};

void testSearchInsertPosition() {
    Solution s;
    vector<vector<int>> nums_vecs = { {1,3,5,6}, {1,3,5,6}, {1,3,5,6} };
    vector<int> targets = { 5, 2, 7 };
    vector<int> outputs = { 2, 1, 4 };
    int correct = 0;
    int incorrect = 0;

    for (int i = 0; i < nums_vecs.size(); ++i) {
        int res = s.searchInsert(nums_vecs[i], targets[i]);
        if (res == outputs[i]) correct++;
        else incorrect++;
        cout << (res == outputs[i]) << endl;
    }

    cout << "Correct:" << correct << endl;
    cout << "Incorrect:" << incorrect << endl;
    cout << "Correct: " << 100. * correct / nums_vecs.size() << "%" << endl;
}