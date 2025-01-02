//
// Created by Bogdan on 3/24/2024.
//

#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H

#include <vector>
#include <iostream>
#include <chrono>
#include <stack>
#include "random.hpp"


class QuickSort {
public:
    explicit QuickSort(const std::vector<long long int> &nums) : m_Nums(nums), m_numsToSort(nums) {};

    static long long int partition(long long int left, long long int right, std::vector<long long int> &nums);

    void begin_benchmark();

private:
    enum pivotTypes {
        pt_Random = 1,
        pt_Rightest = 2,
        pt_Mediana3 = 3
    };

    void sort(long long int left, long long int right, pivotTypes pt);
    const std::vector<long long int> m_Nums;
    std::vector<long long int> m_numsToSort;
    std::chrono::system_clock::time_point startTime;
    int elapsedTime;
};


#endif //SORTING_ALGORITHMS_QUICKSORT_H
