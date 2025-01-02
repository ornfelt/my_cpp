//
// Created by Owner on 3/29/2024.
//

#include "RadixIntSort.h"
#include "utilities.h"


long long int Radix_Int_Sort::getMin(std::vector<long long int>& arr){
    long long int min = arr[0];
    for (long long int i = 1; i < arr.size(); i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}
long long int Radix_Int_Sort::getMaxPlusNormalize(std::vector<long long> &arr,long long int min) {
    long long int max = arr[0]-min;
    arr[0]=arr[0]-min;
    for (long long int i = 1; i < arr.size(); i++) {
        arr[i]=arr[i]-min;
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
void Radix_Int_Sort::countingSort(std::vector<long long int>& arr, int base, unsigned long long int exp){
    std::vector<long long int> output(arr.size());
    std::vector<int> count(base, 0);
    for (size_t i = 0; i < arr.size(); i++) {
        count[(arr[i] / exp) % base]++;
    }
    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }
    for (long long int i = arr.size() - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        count[(arr[i] / exp) % base]--;
    }
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = output[i];
    }
}

void Radix_Int_Sort::sort(int base) {
    long long int min = getMin(m_numsToSort);
    long long int max=getMaxPlusNormalize(m_numsToSort,min);
    for (long long int exp = 1; exp != 0 && max / exp > 0; exp *= base) {

        if(Utilities::isTle(startTime)) {
            return;
        }

        countingSort(m_numsToSort, base, exp);
    }
    for(int i=0;i<m_numsToSort.size();i++)
        m_numsToSort[i]=m_numsToSort[i]+min;
}

void Radix_Int_Sort::begin_benchmark() {
    bool wasSorted;

    m_numsToSort = std::vector<long long int>(m_Nums);
    startTime = std::chrono::system_clock::now();

    std::cout<<"Radix_Int_Sort: Begin benchmark (base = 10)\n";

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
    std::cout<<"\n\n";

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