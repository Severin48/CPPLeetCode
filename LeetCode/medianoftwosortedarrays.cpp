#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

class Solution {
public:
    double getMedianFromVector(vector<int>& vec) {
        int l = vec.size();
        if (l % 2 != 0) {
            return vec[l / 2];
        }
        else {
            return ((double) vec[l / 2] + vec[(l / 2) - 1]) / 2.;
        }
    }

    double getMedianFromPartialVector(vector<int>& vec, int l) {
        int m = (l / 2);
        if (l % 2 != 0) {
            return vec[m];
        }
        else {
            return ((double)vec[m] + vec[m - 1]) / 2.;
        }
    }

    double getMedianFromPartialVector(vector<int>& vec, int l, int offset, int pre_val, int post_val) {
        int m = (l / 2) - offset;
        int preVal, postVal;
        if (m >= vec.size()) {
            postVal = post_val;
        }
        else {
            postVal = vec[m];
        }
        if (m <= 0 || m > vec.size()) {
            preVal = pre_val;
        }
        else {
            preVal = vec[m - 1];
        }
        if (l % 2 != 0) {
            return postVal;
        }
        else {
            return ((double)preVal + postVal) / 2.;
        }
    }

    int binarySearchFirstOccurence(vector<int>& vec, int key) {
        if (vec[0] == key) {
            return 0;
        }
        if (vec.back() == key) {
            return vec.size() - 1;
        }

        int l = 0;
        int r = vec.size();
        int m;
        while (l < r) {
            m = floor((l + r) / 2.);

            if (vec[m] < key) {
                l = m + 1;
            }
            else {
                r = m;
            }
        }
        if (vec[m] > key) return m - 1;
        return m;
    }

    int binarySearchLastOccurence(vector<int>& vec, int key) {
        if (vec.back() == key) {
            return vec.size() - 1;
        }
        if (vec[0] == key) {
            return 0;
        }

        int ans = -1;
        int low = 0;
        int high = vec.size() - 1;
        int mid = 0;

        while (low <= high) {
            mid = ceil((low + high) / 2.);
            int midVal = vec[mid];

            if (midVal < key) {
                low = mid + 1;
            }
            else if (midVal > key) {
                high = mid - 1;
            }
            else if (midVal == key) {
                ans = mid;
                low = mid + 1;
            }
        }
        if (vec.size() > 1 && vec[mid] < key && vec[mid + 1] > key) {
            return mid + 1;
        } else return mid;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int median = 0;
        int l1 = nums1.size();
        int l2 = nums2.size();
        int l = l1 + l2;
        int m = l / 2;
        vector<int> mv;

        if (l1 == 0) {
            return getMedianFromVector(nums2);
        }
        if (l2 == 0) {
            return getMedianFromVector(nums1);
        }
        
        if (nums1.back() <= nums2.front()) {
            nums1.insert(nums1.end(), nums2.begin(), nums2.end());
            return getMedianFromVector(nums1);
        }
        if (nums2.back() <= nums1.front()) {
            nums2.insert(nums2.end(), nums1.begin(), nums1.end());
            return getMedianFromVector(nums2);
        }
        
        // Start and end of overlapping value-span
        int s = max(nums1.front(), nums2.front());
        int e = min(nums1.back(), nums2.back());

        int offset1_initial = binarySearchFirstOccurence(nums1, s);
        int offset2_initial = binarySearchFirstOccurence(nums2, s);
        int end1 = binarySearchLastOccurence(nums1, e);
        int end2 = binarySearchLastOccurence(nums2, e);

        int s1 = nums1[offset1_initial];
        int s2 = nums2[offset2_initial];

        int e1 = nums1[end1];
        int e2 = nums2[end2];

        int newM;

        int r1 = nums1.back() - nums1.front();
        int r2 = nums2.back() - nums2.front();

        // Would be merged left of median
        if (l2/2 > l1){
            newM = m - l1;
            if (newM < l2 && nums1.back() < nums2[newM]) {
                if (l % 2 != 0) {
                    return nums2[newM];
                }
                else if (e1 <= nums2[newM-1]) {
                    return (nums2[newM] + nums2[newM - 1]) / 2.;
                }
            }
        }
        else if (l1/2 > l2){
            newM = m - l2;
            if (newM < l1 && nums2.back() < nums1[newM]) {
                if (l % 2 != 0) {
                    return nums1[newM];
                }
                else if (e2 <= nums1[newM-1]) {
                    return (nums1[newM] + nums1[newM - 1]) / 2.;
                }
            }
        }

        // Would be merged right of median
        if (l2/2 > l1){
            newM = m;
            if (newM < l2 && nums1.front() >= nums2[newM]) {
                if (l % 2 != 0) {
                    return nums2[newM];
                }
                else {
                    return (nums2[newM] + nums2[newM - 1]) / 2.;
                }
            }
        }
        else if (l1/2 > l2) {
            newM = m;
            if (newM < l1 && nums2.front() >= nums1[newM]) {
                if (l % 2 != 0) {
                    return nums1[newM];
                }
                else {
                    return (nums1[newM] + nums1[newM - 1]) / 2.;
                }
            }
        }

        int newLen = end1-offset1_initial + 1 + end2-offset2_initial + 1;
        mv.reserve(newLen);
        // Merging overlapping area into mv
        int v1, v2, offset1, offset2;
        offset1 = offset1_initial;
        offset2 = offset2_initial;
        v1 = nums1[offset1];
        v2 = nums2[offset2];
        for (int i = 0; i < newLen; i++) {
            if (offset1 <= end1) v1 = nums1[offset1];
            if (offset2 <= end2) v2 = nums2[offset2];

            if (offset1 <= end1 && offset2 <= end2 && v1 == v2) {
                v1 = nums1[offset1];
                v2 = nums2[offset2];
                mv.push_back(v1);
                offset1++;
                mv.push_back(v2);
                offset2++;
                if (offset1 <= end1) v1 = nums1[offset1];
                if (offset2 <= end2) v2 = nums2[offset2];
                i++;
            }
            if (offset1 <= end1 && v1 <= v2) {
                v1 = nums1[offset1];
                mv.push_back(v1);
                offset1++;
                if (offset1 <= end1) v1 = nums1[offset1];
            }
            if (offset2 <= end2 && v1 > v2) {
                v2 = nums2[offset2];
                mv.push_back(v2);
                offset2++;
            }
        }
        if (offset1 > end1) {
            while (offset2 <= end2) {
                v2 = nums2[offset2];
                mv.push_back(v2);
                offset2++;
            }
        }
        if (offset2 > end2) {
            while (offset1 <= end1) {
                v1 = nums1[offset1];
                mv.push_back(v1);
                offset1++;
            }
        }

        int e1New, e2New;
        e1New = INT_MAX;
        e2New = INT_MAX;
        if (l1 > end1 + 1) e1New = nums1[end1 + 1];
        if (l2 > end2 + 1) e2New = nums2[end2 + 1];
        int post_val = min(e1New, e2New);


        int s1New, s2New;
        s1New = INT_MIN;
        s2New = INT_MIN;
        if (offset1_initial > 0) s1New = nums1[offset1_initial - 1];
        if (offset2_initial > 0) s2New = nums2[offset2_initial - 1];
        int pre_val = max(s1New, s2New);
        
        return getMedianFromPartialVector(mv, l, max(offset1_initial, offset2_initial), pre_val, post_val);
    }
};

int main() {
    Solution s;
    double m;

    vector<int> v1;
    vector<int> v2;
    vector<int> comp;

    int correct, incorrect;
    correct = 0;
    incorrect = 0;

    std::random_device rd;
    mt19937 rng(rd());
    //uniform_int_distribution<int> uni_sizes(0, 10);
    //uniform_int_distribution<int> uni_values(0, 10);
    uniform_int_distribution<int> uni_sizes(0, 1000);
    uniform_int_distribution<int> uni_values(-1000000, 1000000);
    int size1, size2, val;

    int n_tests = 100000;

    cout << "Starting " << n_tests << " tests..." << endl;

    for (int i = 0; i < n_tests; i++) {
        v1.clear();
        v2.clear();
        size1 = uni_sizes(rng);
        size2 = uni_sizes(rng);
        if (size1 + size2 == 0) {
            if (i % 2 == 0) {
                size1 = 1;
            } else size2 = 1;
        }
        v1.reserve(size1);
        v2.reserve(size2);
        comp.clear();
        comp.reserve(size1 + size2);

        for (int j = 0; j < size1; j++) {
            val = uni_values(rng);
            v1.push_back(val);
            comp.push_back(val);
        }
        for (int j = 0; j < size2; j++) {
            val = uni_values(rng);
            v2.push_back(val);
            comp.push_back(val);
        }

        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());

        sort(comp.begin(), comp.end());
        int solution = s.getMedianFromVector(comp);

        int m = s.findMedianSortedArrays(v1, v2);

        if (solution == m) {
            correct++;
        }
        else {
            incorrect++;
            //cout << "Incorrect" << endl;
            //print_vec(v1, " ");
            //cout << endl;
            //cout << endl;
            //print_vec(v2, " ");
            //cout << endl;
            //cout << endl;
            //s.findMedianSortedArrays(v1, v2);
        }
    }

    cout << "Correct: " << correct << endl;
    cout << "Incorrect: " << incorrect << endl;
    cout << "Correct %: " << 100. * correct / n_tests << endl;

    return 0;
}