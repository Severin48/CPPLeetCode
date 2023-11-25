//#include "LongestPalindromicSubstring.h"
//#include "PalindromeNumber.h"
//#include "MinimumTimeGarbageCollection.h"
//#include "RemoveDuplicatesFromSortedArray.h"
//#include "HappyNumber.h"
//#include "SearchInsertPosition.h"
//#include "DiagonalTraverse2.h"
//#include "StringToInteger.h"
//#include "ArithmeticSubarrays.h"
//#include "RegexMatching.h"
//#include "MaximumNrCoins.h"
//#include "IntegerToRoman.h"
#include "ZigZagConversion.h"

int main() {
	testZigZagConversion();
	// testPalindromicSubstring();
	// testPalindromeNumber();
	// testMinimumTimeGarbageCollection();
	// testRemoveDuplicatesFromSortedArray();
	// testIsHappy();
	// testSearchInsertPosition();
	// testDiagonalTraverse2();
	// testStringToInteger();
	// testArithmeticSubarrays();
	// testRegexMatching();
	// testMaxCoins();
	// testIntegerToRoman();
}

/** LeetCode speed boost
 
#pragma GCC optimize("Ofast","inline","ffast-math","unroll-loops","no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native","f16c")
static const auto fast = []() { std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0); return 0; } ();

#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,mmx,sse2,sse3,sse4")
static const int _ = []() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr); return 0; }();

*/

/*

    Solution s;
    int correct, incorrect;
    correct = incorrect = 0;
    for (int i = 0; i < nums.size(); i++) {
        vector<int> result = s.findDiagonalOrder(nums[i]); // TODO: Nicht das - Das ist die Version mit nested result vector
        bool cor = true;
        if (result.size() != solutions[i].size()) {
            cor = false;
            incorrect++;
            break;
        }
        for (int j = 0; j < result.size(); ++j) {
            if (result[j] != solutions[i][j]) cor = false;
            std::cout << "Problem " << i << ": Expected " << solutions[i] << " -- got -- " << result[j] << std::endl;
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
    cout << "Correct: " << 100. * correct / solutions.size() << "%" << endl;


*/