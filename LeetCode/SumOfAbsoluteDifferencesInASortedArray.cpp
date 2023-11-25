//#pragma GCC optimize("Ofast","inline","ffast-math","unroll-loops","no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native","f16c")
//static const auto fast = []() { std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0); return 0; } ();
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int sm = accumulate(nums.begin(), nums.end(), 0);
        int sz = nums.size();
        int leftSum = 0;
        int rightSum = sm;
        int leftDiff, rightDiff;
        vector<int> res = {};
        if (sz == 0) return res;
        int pivot = 0;

        for (int i = 0; i < sz; ++i) {
            leftSum += pivot;
            pivot = nums[i];
            rightSum -= pivot;
            leftDiff = abs(leftSum - (i * pivot));
            rightDiff = abs(rightSum - ((sz - 1 - i) * pivot));
            res.push_back(leftDiff + rightDiff);
        }
        return res;
    }
};