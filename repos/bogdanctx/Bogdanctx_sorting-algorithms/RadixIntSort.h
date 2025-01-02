//
// Created by Owner on 3/29/2024.
//

#ifndef SORTING_ALGORITHMS_RADIXINTSORT_H
#define SORTING_ALGORITHMS_RADIXINTSORT_H

#include <iostream>
#include <chrono>
#include <vector>

class Radix_Int_Sort {
public:
    explicit Radix_Int_Sort(const std::vector<long long int> &nums) : m_Nums(nums), m_numsToSort(nums) {};
    long long int getMaxPlusNormalize(std::vector<long long int>& arr, long long int min);
    long long int getMin(std::vector<long long int>& arr);
    void countingSort(std::vector< long long int> &nums, int base, unsigned long long int exp);

    void begin_benchmark();

private:
    void sort(int base);
    const std::vector<long long int> m_Nums;
    std::vector<long long int> m_numsToSort;
    std::chrono::system_clock::time_point startTime;
    int elapsedTime;
};

#endif //SORTING_ALGORITHMS_RADIXINTSORT_H
