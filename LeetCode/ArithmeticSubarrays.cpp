#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
    vector<bool> answer(l.size(), false);
    int diff;
    for (int i = 0; i < l.size(); ++i) {
        if (r[i] - l[i] < 2) {
            answer[i] = true;
            continue;
        }
        vector<int> subarray(nums.begin() + l[i], nums.begin() + r[i]+1);
        sort(subarray.begin(), subarray.end());
        for (int j = 0; j < subarray.size() - 1; ++j) {
            if (j == 0) diff = abs(subarray[j + 1] - subarray[j]);
            else if (abs(subarray[j + 1] - subarray[j]) != diff) {
                answer[i] = false;
                break;
            }
            else answer[i] = true;
        }
    }

    return answer;
}

//vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
//    vector<bool> answer(l.size(), true);
//    vector<unordered_map<int, int>> u(l.size(), { {} });
//    int jmin = 0;
//    vector<int> gcds(l.size(), -1);
//    for (int i = 0; i < nums.size() - 1; ++i) {
//        for (int j = jmin; j < l.size(); ++j) {
//            if (i >= l[j] && i < r[j]) {
//                int nconnections = r[j] - l[j];
//                if (gcds[j] == -1) {
//                    gcds[j] = gcd(abs(nums[i] - nums[i + 1]), abs(nums[i + 1] - nums[i + 2]));
//                    if (gcds[j] == 0) {
//                        answer[j] = false;
//                    }
//                }
//                if (nums[i] - nums[i + 1] == 0 || gcds[j] == 0 || (nums[i] - nums[i + 1]) % gcds[j] != 0 || abs(nums[i] - nums[i + 1]) > gcds[j] * nconnections) {
//                    answer[j] = false;
//                }
//                else {
//                    u[j][nums[i]] = 1;
//                }
//            }
//            if (i > r.back()) break;
//        }
//    }
//    return answer;
//}

//vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
//    vector<bool> answer(l.size(), true);
//    vector<unordered_map<int, int>> u(l.size(), { {} });
//    int jmin = 0;
//    vector<int> gcds(l.size(), -1);
//    for (int i = 0; i < nums.size() - 1; ++i) {
//        for (int j = jmin; j < l.size(); ++j) {
//            if (i >= l[j] && i < r[j]) {
//                int nconnections = r[j] - l[j];
//                if (gcds[j] == -1) {
//                    gcds[j] = gcd(abs(nums[i] - nums[i + 1]), abs(nums[i + 1] - nums[i + 2]));
//                    if (gcds[j] == 0) {
//                        answer[j] = false;
//                    }
//                }
//                if (u[j][nums[i]] == 1 || u[j][nums[i + 1]] == 1 || nums[i] - nums[i + 1] == 0 || gcds[j] == 0 || (nums[i] - nums[i + 1]) % gcds[j] != 0 || abs(nums[i] - nums[i + 1]) > gcds[j] * nconnections) {
//                    answer[j] = false;
//                }
//                else {
//                    u[j][nums[i]] = 1;
//                }
//            }
//            if (i > r.back()) break;
//        }
//    }
//    return answer;
//}

void testArithmeticSubarrays() {
    //vector<int> nums = { 4, 6, 5, 9, 3, 7 };
    //vector<int> l = { 0,0,2 };
    //vector<int> r = { 2,3,5 };
    //vector<bool> expected = { true,false,true };

    //vector<int> nums = { -12,-9,-3,-12,-6,15,20,-25,-20,-15,-10 };
    //vector<int> l = { 0,1,6,4,8,7 };
    //vector<int> r = { 4,4,9,7,9,10 };
    ////vector<int> l = { 6 };
    ////vector<int> r = { 9 };

    //vector<bool> expected = { false,true,false,false,true,true };
    //vector<bool> expected = { false };

    vector<int> nums = { -3,-6,-8,-4,-2,-8,-6,0,0,0,0 };
    vector<int> l = { 5,4,3,2,4,7,6,1,7 };
    vector<int> r = { 6,5,6,3,7,10,7,4,10 };
    vector<bool> expected = { true,true,true,true,false,true,true,true,true };

    //vector<int> nums = { -3,-6,-8,-4,-2,-8,-6,0,0,0,0 };
    //vector<int> l = { 3 };
    //vector<int> r = { 6 };
    //vector<bool> expected = { true };
    //

    vector<bool> res = checkArithmeticSubarrays(nums, l, r);

    int correct = 0;
    int incorrect = 0;
    if (res.size() == expected.size()) {
        for (int i = 0; i < res.size(); i++) {
            if (res[i] == expected[i]) {
                correct++;
                cout << "correct ";
            }
            else {
                incorrect++;
                cout << "incorrect ";
            }
        }
        cout << endl;
    }
    else cout << "Output size not matching." << endl;

    cout << "Correct:" << correct << endl;
    cout << "Incorrect:" << incorrect << endl;
    cout << "Correct: " << 100. * correct / expected.size() << "%" << endl;

}