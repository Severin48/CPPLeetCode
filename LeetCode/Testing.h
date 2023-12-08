#pragma once
#ifndef TESTING
#define TESTING

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

template <typename T, typename U>
float testResults(const std::vector<T>& inputs, const std::vector<U>& outputs, std::function<U(T)> func, int verbose=1) {
    int correct = 0;
    int incorrect = 0;
    for (size_t i = 0; i < inputs.size(); i++) {
        U result = func(inputs[i]);

        if (result == outputs[i]) correct++;
        else {
            incorrect++;
            if (verbose > 1) {
                std::cout << "Problem " << i << ": Expected " << outputs[i] << " -- got -- " << result << std::endl;
            }
        }
    }

    std::cout << std::endl;

    float percentage = 100. * correct / inputs.size();
    if (verbose) {
        std::cout << "Correct: " << correct << std::endl;
        std::cout << "Incorrect: " << incorrect << std::endl;
        std::cout << "Accuracy: " << percentage << "%" << std::endl;
    }
    return percentage;
}

template <typename T, typename U>
float testResults(const std::vector<T>& inputs, const std::vector<vector<U>>& outputs, std::function<vector<U>(T)> func, int verbose = 1) {
    int correct = 0;
    int incorrect = 0;
    for (size_t i = 0; i < inputs.size(); i++) {
        vector<U> result = func(inputs[i]);

        if (result.size() != outputs[i].size()) {
            incorrect++;
            if (verbose > 1) {
                std::cout << "Problem " << i << ": Expected size " << outputs[i].size() << " -- got -- " << result.size() << std::endl;
            }
        }
        else {
            std::vector<U> sortedExpected = outputs[i];
            std::sort(sortedExpected.begin(), sortedExpected.end());
            sort(result.begin(), result.end());
            bool cor = true;
            for (int j = 0; j < result.size(); ++j) {
                if (result[j] != outputs[i][j]) {
                    cor = false;
                    break;
                }
            }
            if (!cor) {
                incorrect++;
                if (verbose > 1) {
                    for (int j = 0; j < result.size(); ++j) {
                        std::cout << "Problem " << i << ": Expected " << outputs[i][j] << " -- got -- " << result[j] << std::endl;
                    }
                }
            }
            else correct++;
        }
    }

    std::cout << std::endl;

    float percentage = 100. * correct / inputs.size();
    if (verbose) {
        std::cout << "Correct: " << correct << std::endl;
        std::cout << "Incorrect: " << incorrect << std::endl;
        std::cout << "Accuracy: " << percentage << "%" << std::endl;
    }
    return percentage;
}

#endif // TESTING

/*
Example usage:

    std::function<string(int)> func = intToRoman;
    testResults(inputs, solutions, func, 2);

*/