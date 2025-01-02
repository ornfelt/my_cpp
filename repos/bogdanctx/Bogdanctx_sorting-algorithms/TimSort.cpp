//
// Created by eciuc on 3/29/2024.
//

#include "TimSort.h"
#include "utilities.h"


void TimSort::InsertionSort(unsigned long long st, unsigned long long dr)
{
    for (unsigned long long i = st + 1; i <= dr; i++) {
        long long int temp = m_numsToSort[i];
        unsigned long long j = i;
        while (j > st && m_numsToSort[j-1] > temp) {
            m_numsToSort[j] = m_numsToSort[j-1];
            j--;
        }
        m_numsToSort[j] = temp;
    }
}


void TimSort::merge(unsigned long long st, unsigned long long mij, unsigned long long dr)
{
    unsigned long long s=st;
    unsigned long long m=mij + 1;
    unsigned long long i=st;
    while(s<=mij && m <=dr)
    {
        /*if(Utilities::isTle(startTime)) {
            return;
        }
        if(m_numsToSort[s]>1e8)
            std::cout<< s << " " << m_numsToSort[s] <<" how  s?\n";
        if(m_numsToSort[m]>1e8)
            std::cout<< m << " " << m_numsToSort[m] <<" how  m?\n";
            */
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

void TimSort::sort(unsigned long long n) {
    const int runsize = 32;
    for (unsigned long long i = 0; i < n; i += runsize)
        InsertionSort( i, std::min((i + runsize - 1), (n - 1)));

    for (unsigned long long size = runsize; size < n; size = 2 * size) {
        /*if(Utilities::isTle(startTime)) {
            return;
        }*/
        for (unsigned long long st = 0; st < n; st += 2 * size) {

            unsigned long long mij = st + size - 1;
            unsigned long long dr = std::min((st + 2 * size - 1), (n - 1));

            if (mij < dr)
                merge( st, mij, dr);
        }
    }
}

void TimSort::begin_benchmark() {
    startTime = std::chrono::system_clock::now();
    std::cout<<"TimSort: Begin benchmark\n";
    sort(m_numsToSort.size());
    endTime = std::chrono::system_clock::now();
    elapsedTime = (int) std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    bool wasSorted = Utilities::isSorted(m_numsToSort);
    if(!wasSorted) {
        std::cout<<"TimSort: Could not sort.";
    }
    else {
        std::cout<<"TimSort: Sorting finished in " << elapsedTime << " seconds.";
    }
}

