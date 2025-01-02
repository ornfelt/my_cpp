//
// Created by eciuc on 3/29/2024.
//

#include "MergeSortMirror.h"
#include "utilities.h"

void MergeSortMirror::mirrorsort(unsigned long long st, unsigned long long dr) {
    if(st==dr) return;
    unsigned long long mij = st + (dr-st) /2;

    sort(st,mij);
    sort(mij +1 ,dr);

    unsigned long long s=st;
    unsigned long long m=mij + 1;
    unsigned long long i=st;
    while(s<=mij && m <=dr)
    {
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
}

void MergeSortMirror::sort(unsigned long long st, unsigned long long dr) {
    if(st==dr) return;
    unsigned long long mij = st + (dr-st) /2;

    mirrorsort(st,mij);
    mirrorsort(mij +1 ,dr);

    unsigned long long s=st;
    unsigned long long m=mij + 1;
    unsigned long long i=st;
    while(s<=mij && m <=dr)
    {
        if(m_Numscopy[s]>m_Numscopy[m])
        {
            m_numsToSort[i++]=m_Numscopy[m];
            m++;
        }
        else
        {
            m_numsToSort[i++]=m_Numscopy[s];
            s++;
        }
    }
    while(s<=mij)
    {
        m_numsToSort[i++]=m_Numscopy[s];
        s++;
    }
    while(m<=dr)
    {
        m_numsToSort[i++]=m_Numscopy[m];
        m++;
    }
}

void MergeSortMirror::begin_benchmark() {
    startTime = std::chrono::system_clock::now();
    std::cout<<"MergeSortMirror: Begin benchmark\n";
    sort(0, m_numsToSort.size() - 1);
    endTime = std::chrono::system_clock::now();
    elapsedTime = (int) std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    bool wasSorted = Utilities::isSorted(m_numsToSort);
    if(!wasSorted) {
        std::cout<<"MergeSortMirror: Could not sort.";
    }
    else {
        std::cout<<"MergeSortMirror: Sorting finished in " << elapsedTime << " seconds.";
    }

    m_numsToSort.resize(0);
    m_Numscopy.resize(0);
}