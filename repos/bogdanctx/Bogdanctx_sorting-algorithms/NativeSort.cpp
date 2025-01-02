//
// Created by Bogdan on 3/24/2024.
//

#include "NativeSort.h"
#include "utilities.h"

void NativeSort::begin_benchmark() {
    startTime = std::chrono::system_clock::now();

    std::cout<<"Native sort: Begin benchmark\n";

    std::sort(m_numsToSort.begin(), m_numsToSort.end());

    elapsedTime = Utilities::getElapsedSeconds(startTime);
    bool wasSorted = Utilities::isSorted(m_numsToSort);

    if(!wasSorted) {
        std::cout<<"Native sort: Could not sort.";
    }
    else {
        std::cout<<"Native sort: Sorting finished in " << elapsedTime << " seconds.";
    }
}