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
        // Muss Index returnen und falls nicht vorhanden rechts davon wo es eigentlich wäre
        int ans = -1;
        int low = 0;
        int high = vec.size();

        while (low <= high) {
            int mid = low + (high - low + 1) / 2;
            int midVal = vec[mid];
            ans = mid;

            if (midVal < key) {

                // if mid is less than key, all elements
                // in range [low, mid] are also less
                // so we now search in [mid + 1, high]
                low = mid + 1;
            }
            else if (midVal > key) {

                // if mid is greater than key, all elements 
                // in range [mid + 1, high] are also greater
                // so we now search in [low, mid - 1]
                high = mid - 1;
            }
            else if (midVal == key) {

                // if mid is equal to key, we note down
                //  the last found index then we search 
                // for more in left side of mid
                // so we now search in [low, mid - 1]
                ans = mid;
                high = mid - 1;
            }
        }

        return ans;

    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // TODO: 2 oder 4 Pointers (starten in der Mitte), kann man zu beginn errechnen durch jew. 1. und letzten wert, in welchem bereich median liegen muss?
        // Wenn die bereiche sich nicht überschneiden ist der median je nach länge der letzte/erste von einem vec oder beide addiert und durch 2
        // Wenn sich die bereiche überschneiden macht man binary search nach dem höchsten wert (des niedrigeren vec) der noch in der überschneidung ist
        // --> Das letzte Element der Überschneidung ist Median (evtl. mit einem anderen Wert zsm. bei % 2 == 0 Länge)
        // TODO: log(m+n) deutet auf BFS oder DFS - Trees?

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

        // TODO: Nur 1 binary search!! Weil man aus der Strecke auch die andere berechnen kann! Mit l1, l2, l und der neuen Strecke.
        // Man weiß dann die tatsächliche Gesamtlänge lNew und daraus kann die Mitte ermittelt werden! Aber nicht mergen
        // ACHTUNG: Beim einen braucht man die 1. occurence beim anderen die last occurrence --> Aber brauche ja nur 1

        // Wenn die Vektoren erstes oder letztes Element gemeinsam haben (gleich), stimmt die Überschneidung mit dem Kürzeren Vektor überein ==
        // In welchem wird gesucht? --> Im Fall oben muss nicht gesucht werden, da Überschnittlänge bekannt ist!

        // Problem: Verzahnung ist relevant --> Es kann sein, dass sie überschneiden aber obere hauptsächlich links eingeordnet würden. 
        // Man muss nur bis zur (Gesamt-)Mitte sortieren!

        // Wir können schauen, ob der Median im zu mergenden Bereich liegt! Durch die "Schnittpunkte"! --> Wenn nicht, müssen wir nicht mergen
        // Ist aber nicht von Längen abhängig sondern von Extremwerten siehe 4 (8) Fälle
        // Wenn wir mergen müssen dann nur relevanten Bereich in while Schleife beide vecs durchgehen und 3. füllen (sortiert)
        
        // Fall: Median liegt in Schnittbereich --> Man schaut an die Stelle des größeren, wo Median sein sollte --> In großem vec schauen,
        // welcher Wert an Medianstelle liegt (2 Werte?) (ist egal ob er gerade ist, es muss das Gesamtding gerade sein ABER brauchen genug Werte zum VGL mit
        // kleinerem Vec). Also 1-2 Werte vom großen Vec an Medianstelle nehmen und binary search im kleinen Vec, und falls nicht gefunden die umliegenden Werte dazunehmen

        int valRange = max(nums1.back(), nums2.back()) - min(nums1.front(), nums2.front());
        int r1, r2;
        r1 = nums1.back() - nums1.front();
        r2 = nums2.back() - nums2.front();
        //binarySearchFirstOccurence(nums1&&&&, val);

        int s = max(nums1.front(), nums2.front());
        int e = min(nums1.back(), nums2.back()); // Start and end of overlapping value-span

        // TODO: Binary search, um zu 0-index vom rechten vec ein Korrespondent im linken vec zu finden (x), ab da dann mergen bis val == e
        int offset1 = binarySearchFirstOccurence(nums1, s);
        int offset2 = binarySearchFirstOccurence(nums2, s);
        int end1 = binarySearchFirstOccurence(nums1, e);
        int end2 = binarySearchFirstOccurence(nums2, e); // TODO: Brauche ich für end ein anderes binary search?

        if (end1 == 0 && end2 == 0) {
            if (l1 == 1) {
                return nums1[0];
            }
            else {
                return nums2[0];
            }
        }

        // TODO: Schauen, ob m in den Schnittbereich fällt, falls ja, mergen wie schon unten getan
        if (offset1 != offset2 && m < max(offset1, offset2)) {
            if (offset1 == 0) {
                return getMedianFromPartialVector(nums1, l);
            }
            else {
                return getMedianFromPartialVector(nums2, l);
            }
        }
        if (end1 != end2 && m > min(end1, end2)) { // TODO: Hier kann auch m - 1 > min(end1, end2) sein müssen!! Wenn %2 etc.
            // Also wenn m-1 == min(end1, end2): Es darf eigentlich nur 1 Wert hier aus nums1 oder nums2 genommen werden!! --> Aufgeteilt, das selbe gilt
            // für das obere if (mit offset1,2) dort kann auch 1 Wert drin sein und einer im gemergten Teil --> Nicht direkt returnen
            // Anstatt wegen dem einen Eintrag zu mergen kann man einfach das nächste hinter offset1,2 nehmen!! bzw end1,2 je nach edge case
            // TODO: INSERT in front or back ABER INSERT BEIM OFFSET BEACHTEN!!!!
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
        //int first_of_last_vec = 0;
        //if (end1 > end2) {
        //    last_of_first_vec = nums1[offset1+1];
        //}
        //else if (end1 < end2) {
        //    last_of_first_vec = nums2[offset2+1];
        //}
        
        return getMedianFromPartialVector(mv, l, max(offset1, offset2), last_of_first_vec);
        // TODO: Median ist im gemergten Teil --> durch m einfach raussuchen mv[(m - max(offsets))]
        
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