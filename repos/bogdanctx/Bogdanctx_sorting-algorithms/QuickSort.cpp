//
// Created by Bogdan on 3/24/2024.
//

#include "QuickSort.h"
#include "utilities.h"

long long int QuickSort::partition(const long long int left, const long long int right, std::vector<long long int> &nums) {
    long long int i = left - 1;
    long long int pivot = nums[right];

    for(long long int j = left; j <= right - 1; j++) {
        if(nums[j] <= pivot) {
            ++i;
            std::swap(nums[i], nums[j]);
        }
    }

    ++i;
    std::swap(nums[i], nums[right]);
    return i;
}

void QuickSort::sort(long long int left, long long int right, const QuickSort::pivotTypes pt) {
    std::stack<std::pair<long long int, long long int>> st;

    st.emplace(left, right);

    while(!st.empty()) {

        if(Utilities::isTle(startTime)) {
            return;
        }

        const std::pair<long long int, long long int> stackTop = st.top();
        st.pop();
        left = stackTop.first;
        right = stackTop.second;

        if(left >= right) {
            continue;
        }

        long long int pivotIndex;

        switch (pt) {
            case pivotTypes::pt_Random:
            {
                pivotIndex = left + effolkronium::random_static::get( (long long int)0, right-left);
                std::swap(m_numsToSort[right], m_numsToSort[pivotIndex]);
                break;
            }
            case pivotTypes::pt_Mediana3:
            {
                const long long int a = m_numsToSort[left];
                const long long int b = m_numsToSort[(left+right)/2];
                const long long int c = m_numsToSort[right];

                const long long int mediana = std::max(std::min(a,b), std::min(std::max(a,b),c));

                if(mediana == a) pivotIndex = left;
                if(mediana == b) pivotIndex = (left+right)/2;
                if(mediana == c) pivotIndex = right;

                std::swap(m_numsToSort[right], m_numsToSort[pivotIndex]);

                break;
            }
            default:
                break;
        }

        long long int part = partition(left, right, m_numsToSort);

        st.emplace(left, part - 1);
        st.emplace(part + 1, right);
    }
}

void QuickSort::begin_benchmark() {
    bool wasSorted;

    m_numsToSort = std::vector<long long int>(m_Nums);
    startTime = std::chrono::system_clock::now();

    std::cout<<"Quicksort: Begin benchmark (pivot = random)\n";

    sort(0, m_numsToSort.size() - 1, pivotTypes::pt_Random);

    elapsedTime = Utilities::getElapsedSeconds(startTime);
    wasSorted = Utilities::isSorted(m_numsToSort);

    if(!wasSorted) {
        std::cout<<"Quicksort: Could not sort.";
    }
    else {
        std::cout<<"Quicksort: Sorting finished in " << elapsedTime << " seconds.";
    }

    std::cout<<"\n\n";

    m_numsToSort = std::vector<long long int>(m_Nums);
    startTime = std::chrono::system_clock::now();

    std::cout<<"Quicksort: Begin benchmark (pivot = mediana din 3)\n";

    sort(0, m_numsToSort.size() - 1, pivotTypes::pt_Mediana3);

    elapsedTime = Utilities::getElapsedSeconds(startTime);
    wasSorted = Utilities::isSorted(m_numsToSort);

    if(!wasSorted) {
        std::cout<<"Quicksort: Could not sort";
    }
    else {
        std::cout<<"Quicksort: Sorting finished in " << elapsedTime << " seconds.";
    }

    std::cout<<"\n\n";

    m_numsToSort = std::vector<long long int>(m_Nums);
    startTime = std::chrono::system_clock::now();

    std::cout<<"Quicksort: Begin benchmark (pivot = elementul din dreapta)\n";

    sort(0, m_numsToSort.size() - 1, pivotTypes::pt_Rightest);

    elapsedTime = Utilities::getElapsedSeconds(startTime);
    wasSorted = Utilities::isSorted(m_numsToSort);

    if(!wasSorted) {
        std::cout<<"Quicksort: Could not sort";
    }
    else {
        std::cout<<"Quicksort: Sorting finished in " << elapsedTime << " seconds.";
    }
}
