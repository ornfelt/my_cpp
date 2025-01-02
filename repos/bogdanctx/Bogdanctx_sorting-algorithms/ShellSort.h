//
// Created by Bogdan on 3/24/2024.
//

#ifndef SORTING_ALGORITHMS_SHELLSORT_H
#define SORTING_ALGORITHMS_SHELLSORT_H

#include <iostream>
#include <vector>
#include <chrono>

class ShellSort {
public:
    explicit ShellSort(const std::vector<long long int> &nums) : m_Nums(nums), m_numsToSort(nums) {};

    void begin_benchmark();

private:
    void sort();

    const std::vector<long long int> m_Nums;
    std::vector<long long int> m_numsToSort;

    std::chrono::system_clock::time_point startTime;
    int elapsedTime;
};


#endif //SORTING_ALGORITHMS_SHELLSORT_H
