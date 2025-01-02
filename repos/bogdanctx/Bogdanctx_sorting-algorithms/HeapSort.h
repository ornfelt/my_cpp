//
// Created by Owner on 3/28/2024.
//

#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H

#include <vector>
#include <chrono>
#include <iostream>

class HeapSort{
public:
    explicit HeapSort(const std::vector<long long int> &nums) : m_numsToSort(nums) {};
    void heapify_down(long long int i, long long int n);
    void build_max_heap();
    void begin_benchmark();

private:
    void sort();
    std::vector<long long int> m_numsToSort;
    std::chrono::system_clock::time_point startTime;
    int elapsedTime;
};


#endif //SORTING_ALGORITHMS_HEAPSORT_H
