#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int x, y;
        int xprev, yprev, curx, cury;
        int dx;
        int dy;
        int ret = 0;
        for (int i = 0; i < points.size(); ++i) {
            x = points[i][0];
            y = points[i][1];
            if (i == 0) {
                curx = x;
                cury = y;
                xprev = x;
                yprev = y;
            }

            while (curx != x || cury != y) {
                if (curx < x) dx = 1;
                else if (curx > x) dx = -1;
                else dx = 0;
                if (cury < y) dy = 1;
                else if (cury > y) dy = -1;
                else dy = 0;
                xprev = curx;
                yprev = cury;
                curx += dx;
                cury += dy;
                //if (dx != 0 && dy != 0) ++ret;
                ++ret;
            }
        }
        return ret;
    }
};

void testMinTimeVisitingAllPoints() {
    Solution s;
    vector<vector<vector<int>>> values = { {{1,1},{3,4},{-1,0}} };
    vector<int> solutions = { 7 };
    int correct, incorrect;
    correct = incorrect = 0;
    for (int i = 0; i < values.size(); i++) {
        int result = s.minTimeToVisitAllPoints(values[i]);
        if (result == solutions[i]) {
            correct++;
            // cout << "Correct: " << result << endl;
        }
        else {
            incorrect++;
            cout << "Problem " << i << " Expected\t" << solutions[i] << "  = got =  " << result << endl;
        }
    }
    cout << endl << "Correct:" << correct << endl;
    cout << "Incorrect:" << incorrect << endl;
    cout << "Correct: " << 100. * correct / values.size() << "%" << endl;
}