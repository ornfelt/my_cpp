//
// Created by Radu on 3/24/2024.
//

#include "RadixSort.h"
#include "utilities.h"

unsigned long long int Radix_Sort::getMax(std::vector<unsigned long long int>& arr){
    unsigned long long int max = arr[0];
    for (long long int i = 1; i < arr.size(); i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void Radix_Sort::countingSort(std::vector<unsigned long long int>& arr, int base, unsigned long long int exp){
    std::vector<unsigned long long int> output(arr.size());
    std::vector<int> count(base, 0);
    for (size_t i = 0; i < arr.size(); i++) {
        count[(arr[i] / exp) % base]++;
    }
    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        count[(arr[i] / exp) % base]--;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

void Radix_Sort::sort(int base) {
    std::vector<unsigned long long int> unsigned_arr;
    for (long long int num : m_numsToSort) {
        unsigned_arr.push_back((static_cast<unsigned long long int>(num))^0x8000000000000000);
    }

    unsigned long long int max = getMax(unsigned_arr);

    for (unsigned long long int exp = 1; max / exp > 0; exp *= base) {
        if(exp) {
            if(Utilities::isTle(startTime)) {
                return;
            }

            countingSort(unsigned_arr, base, exp);
        }
        else break;
    }

    for (size_t i = 0; i < m_numsToSort.size(); i++) {
        m_numsToSort[i] = static_cast<long long int>((unsigned_arr[i])^0x8000000000000000);
    }
}

void Radix_Sort::begin_benchmark() {
    bool wasSorted;

    m_numsToSort = std::vector<long long int>(m_Nums);
    startTime = std::chrono::system_clock::now();

    std::cout<<"Radix_Sort: Begin benchmark (base = 10)\n";

    sort(10);

    elapsedTime = Utilities::getElapsedSeconds(startTime);
    wasSorted = Utilities::isSorted(m_numsToSort);

    if(!wasSorted) {
        std::cout<<"Radix_Sort: Could not sort.";
    }
    else {
        std::cout<<"Radix_Sort: Sorting finished in " << elapsedTime << " seconds.";
        //std::cout<<"\n"<<m_numsToSort[m_numsToSort.size()-1];

    }
    std::cout<<'\n';

    m_numsToSort = std::vector<long long int>(m_Nums);
    startTime = std::chrono::system_clock::now();

    std::cout<<"Radix_Sort: Begin benchmark (base = 2^16)\n";

    sort(65536);

    elapsedTime = Utilities::getElapsedSeconds(startTime);
    wasSorted = Utilities::isSorted(m_numsToSort);

    if(!wasSorted) {
        std::cout<<"Radix_Sort: Could not sort";
    }
    else {
        std::cout<<"Radix_Sort: Sorting finished in " << elapsedTime << " seconds.";
    }
}
