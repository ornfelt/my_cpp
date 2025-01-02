//
// Created by eciuc on 3/29/2024.
//

#include "MergeSortIfState.h"
#include "utilities.h"


void MergeSortIfState::sort(unsigned long long st, unsigned long long dr,bool state =true) {
    if(st==dr) return;
    unsigned long long mij = st + (dr-st) /2;

    sort(st,mij,!state);
    sort(mij +1 ,dr,!state);

    unsigned long long s=st;
    unsigned long long m=mij + 1;
    unsigned long long i=st;
    if(state)
    {
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
    else {
        while (s <= mij && m <= dr) {
            if (m_numsToSort[s] > m_numsToSort[m]) {
                m_Numscopy[i++] = m_numsToSort[m];
                m++;
            } else {
                m_Numscopy[i++] = m_numsToSort[s];
                s++;
            }
        }
        while (s <= mij) {
            m_Numscopy[i++] = m_numsToSort[s];
            s++;
        }
        while (m <= dr) {
            m_Numscopy[i++] = m_numsToSort[m];
            m++;
        }
    }
}

void MergeSortIfState::begin_benchmark() {
    startTime = std::chrono::system_clock::now();
    std::cout<<"MergeSortIfState: Begin benchmark\n";
    sort(0, m_numsToSort.size() - 1);
    endTime = std::chrono::system_clock::now();
    elapsedTime = (int) std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    bool wasSorted = Utilities::isSorted(m_numsToSort);
    if(!wasSorted) {
        std::cout<<"MergeSortIfState: Could not sort.";
    }
    else {
        std::cout<<"MergeSortIfState: Sorting finished in " << elapsedTime << " seconds.";
    }

    m_numsToSort.resize(0);
    m_Numscopy.resize(0);
}