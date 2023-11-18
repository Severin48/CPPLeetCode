#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

template<typename T>
void print_vec(vector<T>& vec, string sep) {
    for (auto t : vec) {
        cout << t << sep;
    }
    cout << endl;
}

template<typename T>
void print_mat(vector<vector<T>>& mat, string sep) {
    cout << endl;
    for (vector<T> vec : mat) {
        for (T t : vec) {
            cout << t << sep;
        }
        cout << endl;
    }
    cout << endl;
}
    

//int main() {
//    vector<int>nums = {3,2,4};
//    int target = 6;
//
//    string sep = " ";
//
//    vector<int> indices(2);
//
//    unordered_map<int, int> hMap;
//    
//    for (int i = 0; i < nums.size(); i++) {
//        int num = nums[i];
//        int complement = target - num;
//
//        if (hMap.find(complement) != hMap.end()) {
//            cout << hMap[complement] << sep << i << endl;
//            return 0;
//        }
//        else hMap[num] = i;
//    }
//    cout << "{}" << endl;
//
//    print_vec(indices, " ");
//
//    // print_mat(sums, "\t");
//
//    return 0;
//}