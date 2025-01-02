//
// Created by eciuc on 3/29/2024.
//

#ifndef SORTING_ALGORITHMS_TIMSORT_H
#define SORTING_ALGORITHMS_TIMSORT_H

#include <vector>
#include <iostream>
#include <chrono>
#include <stack>
#include "random.hpp"


class TimSort {
public:
    explicit TimSort(const std::vector<long long int>& nums) : m_numsToSort(nums), m_Numscopy(nums) {};

    void begin_benchmark();

private:
    void sort(unsigned long long n);

    std::vector<long long int> m_numsToSort;
    std::vector<long long int> m_Numscopy;

    std::chrono::system_clock::time_point startTime, endTime;
    int elapsedTime;

    void merge(unsigned long long l, unsigned long long m, unsigned long long r);

    void InsertionSort(unsigned long long left, unsigned long long right);
};


#endif //SORTING_ALGORITHMS_TIMSORT_H
