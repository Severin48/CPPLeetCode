#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // TODO: 2 oder 4 Pointers (starten in der Mitte), kann man zu beginn errechnen durch jew. 1. und letzten wert, in welchem bereich median liegen muss?
        // Wenn die bereiche sich nicht überschneiden ist der median je nach länge der letzte/erste von einem vec oder beide addiert und durch 2
        // Wenn sich die bereiche überschneiden macht man binary search nach dem höchsten wert (des niedrigeren vec) der noch in der überschneidung ist
        // --> Das letzte Element der Überschneidung ist Median (evtl. mit einem anderen Wert zsm. bei % 2 == 0 Länge)
        // TODO: log(m+n) deutet auf BFS oder DFS - Trees?


        int l1 = nums1.size();
        int l2 = nums2.size();
        if (l1 == 0 && l2 == 0) {
            return 0;
        }

        vector<int> mv;

        int m1 = l1 / 2;
        int m2 = l2 / 2;

        if (l1 > 0) {
            mv.push_back(nums1[m1]);
            if (l1 % 2 == 0) {
                mv.push_back(nums1[m1 - 1]);
            }
        }

        if (l2 > 0) {
            mv.push_back(nums2[m2]);
            if (l2 % 2 == 0) {
                mv.push_back(nums2[m2 - 1]);
            }
        }
        sort(mv.begin(), mv.end());
        int lv = mv.size();
        int midv = lv / 2;
        double median = mv[midv];

        if (lv % 2 == 0 && lv > 0) {
            median = (median + mv[midv - 1]) / 2.;
        }
        return median;
    }
};

int main() {
    Solution s;

    vector<int> v1 = { 1, 3 };
    vector<int> v2 = { 2 };
    double m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    v1 = { };
    v2 = { 2,3 };
    m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    v1 = { };
    v2 = { 1 };
    m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    v1 = { 1 };
    v2 = { 2, 3, 4};
    m = s.findMedianSortedArrays(v1, v2);
    cout << m << endl;

    return 0;
}