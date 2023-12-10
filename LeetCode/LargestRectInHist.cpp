#include <vector>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int l, r, li, ri, delta, rectH, nElem, tmp;
        long area, maxArea;
        maxArea = INT_MIN;
        // TODO: Löst glaube ich das Problem: Die while-Schleifen in eins machen und immer die jenige Seite (rechts/links) zuerst, welche die kleinste Höhenreduzierung erfordert!!
        for (int i = 0; i < heights.size(); ++i) {
            area = heights[i];
            rectH = area;
            nElem = 1;
            li = i - 1;
            while (li >= 0) {
                delta = heights[li] - rectH;
                if (delta <= 0) {
                    tmp = heights[li] * (nElem + 1);
                    if (tmp < area) break;
                    else {
                        rectH = heights[li];
                        area = tmp;
                    }
                }
                else {
                    area += rectH;
                }
                nElem++;
                --li;
            }

            // Wenn durch verkeinerung des rect eine Erweiterung möglich ist müsste zuerst nach rechts gegangen werden und danach noch versucht werden links und rechts mit verkleinerung weiter zu gehen
            // In diesem Fall müsste mit Höhe 4 nach rechts geschaut werden anstatt zuerst mit 3 nach links zu erweitern --> Beides in ein While loop packen und immer die Seite wählen wo die Höhe am wenigsten reduziert werden muss!

            ri = i + 1;
            while (ri < heights.size()) {
                delta = heights[ri] - rectH;
                if (delta < 0) {
                    tmp = heights[ri] * (nElem + 1);
                    if (tmp < area) {
                        i = ri;
                        break;
                    }
                    else {
                        rectH = heights[ri];
                        area = tmp;
                    }
                }
                else {
                    area += rectH;
                }
                nElem++;
                ++ri;
            }
            if (area > maxArea) maxArea = area;
        }
        return maxArea;
    }
};