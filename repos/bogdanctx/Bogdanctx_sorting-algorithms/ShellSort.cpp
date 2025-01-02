//
// Created by Bogdan on 3/24/2024.
//

#include "ShellSort.h"
#include "utilities.h"

void ShellSort::sort() {
    long long int n = m_numsToSort.size();
    for(long long int gap = n / 2; gap > 0; gap = gap / 2) {
        if(Utilities::isTle(startTime)) {
            return;
        }

        for(long long int i = gap; i < n; i++) {
            long long int temp = m_numsToSort[i];
            long long int j;

            for(j = i; j >= gap && m_numsToSort[j-gap] > temp; j -= gap) {
                m_numsToSort[j] = m_numsToSort[j - gap];
            }

            m_numsToSort[j] = temp;
        }
    }
}

void ShellSort::begin_benchmark() {
    startTime = std::chrono::system_clock::now();

    std::cout<<"Shellsort: Begin benchmark\n";

    sort();

    elapsedTime = Utilities::getElapsedSeconds(startTime);

    bool wasSorted = Utilities::isSorted(m_numsToSort);
    if(!wasSorted) {
        std::cout<<"Shellsort: Could not sort.";
    }
    else {
        std::cout<<"Shellsort: Sorting finished in " << elapsedTime << " seconds.";
    }
}