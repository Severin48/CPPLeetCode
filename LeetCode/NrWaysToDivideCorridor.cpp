#include <string>
#include <vector>
#include "Testing.h"

using namespace std;

int numberOfWays(string corridor) {

    if (corridor.size() < 2) return 0;
    if (corridor == "SS") return 1;
    if (corridor == "PP") return 0;
    const int MOD = 1000000007;
    unsigned long long ways = 1;
    unsigned long long currWays = 0;
    unsigned long long seats = 0;
    unsigned long long plants = 0;
    bool hasPlants = false;
    for (char c : corridor) {
        if (c == 'S') {
            if (hasPlants) {
                currWays++;
                ways *= currWays % MOD;
            }
            hasPlants = false;
            seats++;
        }
        else {
            if (seats % 2 == 0 && seats > 1) {
                currWays++;
                hasPlants = true;
            }
        }
    }
    if (seats < 2 || seats % 2 != 0) return 0;
    else if (seats > 1 && seats % 2 == 0 && ways == 0) return 1;
    else return (int)(ways % MOD);
}

void testNrWaysToDivideCorridor() {
    vector<string> inputs = {"SPSPPSSPSSSS"};
    vector<int> solutions = {6};

    std::function<int(string)> func = numberOfWays;
    testResults(inputs, solutions, func, 2);

}