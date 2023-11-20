#include <vector>
#include <string>
#include <iostream>
#include "MinimumTimeGarbageCollection.h"

using namespace std;

class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int time = 0;
        int size = garbage.size();
        if (size > 0) time += garbage[0].size();
        int g, p, m;
        g = p = m = 0;

        for (int i = size - 1; i > 0; i--) { // != 0 because we already did index 0 (Trucks don't have to drive)
            time += garbage[i].size();
            if (g == 0 || p == 0 || m == 0) {
                for (char c : garbage[i]) {
                    if (g == 0 && c == 'G') g = i;
                    else if (p == 0 && c == 'P') p = i;
                    else if (m == 0 && c == 'M') m = i;
                }
            }
        }
        for (int i = 1; i <= travel.size(); i++) {
            if (i <= g) time += travel[i-1];
            if (i <= p) time += travel[i-1];
            if (i <= m) time += travel[i-1];
        }
        cout << "Time: " << time << endl;
        return time;
    }
};

void testMinimumTimeGarbageCollection() {
    Solution s;

    vector<string> garbage = {"G", "P", "GP", "GG"};
    vector<int> travel = { 2,4,3 };
    int time = 21;

    if (s.garbageCollection(garbage, travel) == time) {
        cout << "Correct" << endl;
    }
    else {
        cout << "Incorrect" << endl;
    }

}