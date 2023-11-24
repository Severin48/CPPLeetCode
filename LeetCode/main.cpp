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
#include "MaximumNrCoins.h"

int main() {
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
	testMaxCoins();
}

/** LeetCode speed boost
 
#pragma GCC optimize("Ofast","inline","ffast-math","unroll-loops","no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native","f16c")
static const auto fast = []() { std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0); return 0; } ();

#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,mmx,sse2,sse3,sse4")
static const int _ = []() { std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr); return 0; }();

*/