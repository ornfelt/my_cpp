//
// Created by eciuc on 3/29/2024.
//

#ifndef SORTING_ALGORITHMS_MERGESORTMIRROR_H
#define SORTING_ALGORITHMS_MERGESORTMIRROR_H

#include <vector>
#include <iostream>
#include <chrono>
#include <stack>
#include "random.hpp"


class MergeSortMirror {
public:
    explicit MergeSortMirror(const std::vector<long long int>& nums) : m_numsToSort(nums), m_Numscopy(nums) {};

    void begin_benchmark();

private:
    void sort(unsigned long long st, unsigned long long dr);
    void mirrorsort(unsigned long long st, unsigned long long dr);

    std::vector<long long int> m_numsToSort;
    std::vector<long long int> m_Numscopy;

    std::chrono::system_clock::time_point startTime, endTime;
    int elapsedTime;
};


#endif //SORTING_ALGORITHMS_MERGESORTMIRROR_H
