//
// Created by Radu on 3/24/2024.
//

#ifndef SORTING_ALGORITHMS_RADIXSORT_H
#define SORTING_ALGORITHMS_RADIXSORT_H


#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

class Radix_Sort {
public:
    explicit Radix_Sort(const std::vector<long long int> &nums) : m_Nums(nums), m_numsToSort(nums) {};
    unsigned long long int getMax(std::vector<unsigned long long int>& arr);
    void countingSort(std::vector<unsigned long long int> &nums, int base, unsigned long long int exp);

    void begin_benchmark();

private:

    void sort(int base);
    const std::vector<long long int> m_Nums;
    std::vector<long long int> m_numsToSort;
    std::chrono::system_clock::time_point startTime;
    int elapsedTime;
};


#endif //SORTING_ALGORITHMS_RADIXSORT_H
