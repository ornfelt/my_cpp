//
// Created by eciuc on 3/29/2024.
//

#include "BottomUpMergeSort.h"
#include "utilities.h"


void BottomUpMergeSort::sort() {
    unsigned long long s,m,i,mij,dr,st;
    unsigned long long n=m_numsToSort.size();
    for (unsigned long long size = 1; size < n; size = 2 * size) {

        for (st = 0; st < n; st += 2 * size) {

            mij = st + size - 1;
            dr = std::min((st + 2 * size - 1), (n-1));

            if (mij < dr)
            {
                s=st;
                m=mij + 1;
                i=st;
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
                for(s=st;s<=dr;s++)
                {
                    m_numsToSort[s]=m_Numscopy[s];
                }
            }
        }
    }
}

void BottomUpMergeSort::begin_benchmark() {
    startTime = std::chrono::system_clock::now();
    std::cout<<"BottomUpMergeSort: Begin benchmark\n";
    sort();
    endTime = std::chrono::system_clock::now();
    elapsedTime = (int) std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    bool wasSorted = Utilities::isSorted(m_numsToSort);
    if(!wasSorted) {
        std::cout<<"BottomUpMergeSort: Could not sort.";
    }
    else {
        std::cout<<"BottomUpMergeSort: Sorting finished in " << elapsedTime << " seconds.";
    }
}