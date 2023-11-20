#include <vector>
#include <iostream>
#include "RemoveDuplicatesFromSortedArray.h"

using namespace std;

int binarySearchRight(vector<int>& vec, int key) {
    int l = 0;
    int r = vec.size();
    int m;

    while (l < r) {
        m = floor((l + r) / 2.);
        if (vec[m] > key) r = m;
        else l = m + 1;
    }
    return r - 1;
}

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int sz = nums.size();
        int valRange = nums.back() - nums.front();
        vector<int> unums;
        unums.reserve(sz);
        int lastIdx;

        for (int i = 0; i < sz; i++) {
            lastIdx = binarySearchRight(nums, nums[i]);
            unums.push_back(nums[i]);
            i = lastIdx;
        }

        nums = unums;

        return nums.size();
    }
};

void testRemoveDuplicatesFromSortedArray() {
    Solution s;

    vector<int> nums = { 1,1,2 };
    vector<int> expectedNums = { 1,2 };
    int l, expectedL;
    expectedL = 2;

    if (s.removeDuplicates(nums) == expectedL) {
        bool correct = true;
        for (int i = 0; i < expectedL; i++) {
            if (nums[i] != expectedNums[i]) {
                correct = false;
                break;
            }
        }
        if(correct) cout << "Correct" << endl;
        else cout << "Incorrect" << endl;
    } else cout << "Incorrect" << endl;
}