//
// Created by eciuc on 3/28/2024.
//


#include "MergeSort.h"
#include "utilities.h"


void MergeSort::sort(unsigned long long st, unsigned long long dr) {
    if(st==dr) return;
    unsigned long long mij = st + (dr-st) /2;

    sort(st,mij);
    sort(mij +1 ,dr);

    unsigned long long s=st;
    unsigned long long m=mij + 1;
    unsigned long long i=st;
    while(s<=mij && m <=dr)
    {
        /*if(Utilities::isTle(startTime)) {
            return;
        }*/
        if(m_numsToSort[s]>m_numsToSort[m])
        {
            m_Numscopy[i++]=m_numsToSort[m];
            m++;
        }
        else
        {
            m_Numscopy[i++]=m_numsToSort[s];
            s++;
        }
    }
    while(s<=mij)
    {
        m_Numscopy[i++]=m_numsToSort[s];
        s++;
    }
    while(m<=dr)
    {
        m_Numscopy[i++]=m_numsToSort[m];
        m++;
    }
    for(s=st;s<=dr;s++)
    {
        m_numsToSort[s]=m_Numscopy[s];
    }
}

void MergeSort::begin_benchmark() {
    startTime = std::chrono::system_clock::now();
    std::cout<<"MergeSort: Begin benchmark\n";
    sort(0, m_numsToSort.size() - 1);
    endTime = std::chrono::system_clock::now();
    elapsedTime = (int) std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    bool wasSorted = Utilities::isSorted(m_numsToSort);
    if(!wasSorted) {
        std::cout<<"MergeSort: Could not sort.";
    }
    else {
        std::cout<<"MergeSort: Sorting finished in " << elapsedTime << " seconds.";
    }

    m_numsToSort.resize(0);
    m_Numscopy.resize(0);
}