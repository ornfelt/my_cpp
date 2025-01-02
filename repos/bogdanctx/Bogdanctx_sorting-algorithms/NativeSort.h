//
// Created by Bogdan on 3/24/2024.
//

#ifndef SORTING_ALGORITHMS_NATIVESORT_H
#define SORTING_ALGORITHMS_NATIVESORT_H

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

class NativeSort {
public:
    explicit NativeSort(const std::vector<long long int> &nums) : m_numsToSort(nums) {};

    void begin_benchmark();

private:
    std::vector<long long int> m_numsToSort;
    std::chrono::system_clock::time_point startTime;
    int elapsedTime;
};


#endif //SORTING_ALGORITHMS_NATIVESORT_H
