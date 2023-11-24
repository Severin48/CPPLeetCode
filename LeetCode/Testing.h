#pragma once
#ifndef TESTING
#define TESTING

#include <iostream>
#include <vector>
#include <functional>

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
                std::cout << "Problem " << i << ":\tExpected: " << outputs[i] << "\t -- got -- \t" << result << std::endl;
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

#endif // TESTING