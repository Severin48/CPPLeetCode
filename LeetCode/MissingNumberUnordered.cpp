#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size() + 1;
        int expectedSum = (n * (n - 1)) / 2;
        int sum = accumulate(nums.begin(), nums.end(), 0);

        return expectedSum - sum;
    }
};