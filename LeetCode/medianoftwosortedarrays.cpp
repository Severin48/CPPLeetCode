#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>

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

    double getMedianFromPartialVector(vector<int>& vec, int l, int offset) {
        int m = (l / 2) - offset;
        if (l % 2 != 0) {
            return vec[m];
        }
        else {
            return ((double)vec[m] + vec[m - 1]) / 2.;
        }
    }

    double getMedianFromPartialVector(vector<int>& vec, int l, int offset, int lof) {
        int m = (l / 2) - offset;
        if (l % 2 != 0) {
            return vec[m];
        }
        else {
            if (m - 1 < 0) {
                return ((double)vec[m] + lof ) / 2.;
            }
            else {
                return ((double)vec[m] + vec[m - 1]) / 2.;
            }
        }
    }

    int binarySearchFirstOccurence(vector<int>& vec, int key) {
        if (vec[0] == key) {
            return 0;
        }
        if (vec.back() == key) {
            return vec.size() - 1;
        }

        int ans = -1;
        int low = 0;
        int high = vec.size();

        while (low <= high) {
            int mid = low + (high - low + 1) / 2;
            int midVal = vec[mid];
            ans = mid;

            if (midVal < key) {
                low = mid + 1;
            }
            else if (midVal > key) {
                high = mid - 1;
            }
            else if (midVal == key) {
                ans = mid;
                high = mid - 1;
            }
        }

        return ans;

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

        int valRange = max(nums1.back(), nums2.back()) - min(nums1.front(), nums2.front());
        int r1, r2;
        r1 = nums1.back() - nums1.front();
        r2 = nums2.back() - nums2.front();
        
        // Start and end of overlapping value-span
        int s = max(nums1.front(), nums2.front());
        int e = min(nums1.back(), nums2.back());

        int offset1 = binarySearchFirstOccurence(nums1, s);
        int offset2 = binarySearchFirstOccurence(nums2, s);
        int end1 = binarySearchFirstOccurence(nums1, e);
        int end2 = binarySearchFirstOccurence(nums2, e);

        if (end1 == 0 && end2 == 0) {
            if (l1 == 1) {
                return nums1[0];
            }
            else {
                return nums2[0];
            }
        }

        // Case: Median is outside of overlapping area (left or right)
        if (offset1 != offset2 && m < max(offset1, offset2)) {
            if (offset1 == 0) {
                return getMedianFromPartialVector(nums1, l);
            }
            else {
                return getMedianFromPartialVector(nums2, l);
            }
        }
        if (end1 != end2 && m > min(end1, end2)) {
            int offset = max(end1, end2);
            if (end1 > end2) {
                return getMedianFromPartialVector(nums1, l, end2);
            }
            else {
                return getMedianFromPartialVector(nums2, l, end1);
            }
        }
        

        int newLen = max(end1-offset1, end2-offset2);
        mv.reserve(newLen);
        // Merging overlapping area into mv
        int v1, v2;
        for (int i = 0; i < newLen; i++) {
            v1 = nums1[offset1];
            v2 = nums2[offset2];
            if (v1 < v2) {
                mv.push_back(v1);
                offset1++;
            }
            else {
                mv.push_back(v2);
                offset2++;
            }
        }
        
        // Case: Median requires one value from merged area and one left or right of it
        int last_of_first_vec = 0;
        bool lof_available = false;
        if (offset1 > offset2) {
            last_of_first_vec = nums1[offset1-1];
        } else if (offset1 < offset2) {
            last_of_first_vec = nums2[offset2-1];
        }
        
        return getMedianFromPartialVector(mv, l, max(offset1, offset2), last_of_first_vec);
        
        return median;
    }
};

int main() {
    Solution s;

    int n_runs = 1;
    double m;

    vector<int> v1;
    vector<int> v2;
    
    v1 = { 1, 3 };
    v2 = { 2 };
    m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    v1 = { };
    v2 = { 2,3 };
    m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    v1 = { };
    v2 = { 1 };
    m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    auto t1 = chrono::high_resolution_clock::now();
    for (int i = 0; i < n_runs; i++) {
        v1 = { 1 };
        v2 = { 2, 3, 4 };
        m = s.findMedianSortedArrays(v1, v2);
        //cout << m << endl;
    }
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    duration<double, milli> ms_double = t2 - t1;

    std::cout << ms_double.count() << "ms\n";

    v1 = { 1,2,3,4,5,6};
    v2 = { 1,2,3,7,11,12,13,16 };
    m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    v1 = { 1,2,3,7,11,12,13,16 };
    v2 = { 1,2,3,4,5,6 };
    m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    return 0;
}