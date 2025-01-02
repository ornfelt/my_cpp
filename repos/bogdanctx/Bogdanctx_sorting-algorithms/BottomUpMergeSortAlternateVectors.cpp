//
// Created by eciuc on 3/29/2024.
//

#include "BottomUpMergeSortAlternateVectors.h"
#include "utilities.h"


void BottomUpMergeSortAlternateVectors::sort() {
    unsigned long long s,m,i,mij,dr,st,cn;
    unsigned long long n=m_numsToSort.size();
    cn=1;
    int reps=0;
    while(cn<n)
    {
        reps++;
        cn*=2;
    }
    for (unsigned long long size = 1; size < n; size = 2 * size) {

        if(reps%2==0) {
            for (st = 0; st < n; st += 2 * size) {

                mij = st + size - 1;
                dr = std::min((st + 2 * size - 1), (n - 1));

                if (mij < dr) {
                    s = st;
                    m = mij + 1;
                    i = st;


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
                else
                {
                    for (s = st; s < n; s++) {
                        m_Numscopy[s] = m_numsToSort[s];
                    }
                }
            }
        }
        else
        {
            for (st = 0; st < n; st += 2 * size) {

                mij = st + size - 1;
                dr = std::min((st + 2 * size - 1), (n - 1));

                if (mij < dr) {
                    s = st;
                    m = mij + 1;
                    i = st;
                    while (s <= mij && m <= dr) {
                        if (m_Numscopy[s] > m_Numscopy[m]) {
                            m_numsToSort[i++] = m_Numscopy[m];
                            m++;
                        } else {
                            m_numsToSort[i++] = m_Numscopy[s];
                            s++;
                        }
                    }
                    while (s <= mij) {
                        m_numsToSort[i++] = m_Numscopy[s];
                        s++;
                    }
                    while (m <= dr) {
                        m_numsToSort[i++] = m_Numscopy[m];
                        m++;
                    }
                }
                else
                {
                    for (s = st; s < n; s++) {
                        m_numsToSort[s] = m_Numscopy[s];
                    }
                }
            }
        }
        reps--;
    }
}

void BottomUpMergeSortAlternateVectors::begin_benchmark() {
    startTime = std::chrono::system_clock::now();
    std::cout<<"BottomUpMergeSortAlternateVectors: Begin benchmark\n";
    sort();
    endTime = std::chrono::system_clock::now();
    elapsedTime = (int) std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    bool wasSorted = Utilities::isSorted(m_numsToSort);
    if(!wasSorted) {
        std::cout<<"BottomUpMergeSortAlternateVectors: Could not sort.";
    }
    else {
        std::cout<<"BottomUpMergeSortAlternateVectors: Sorting finished in " << elapsedTime << " seconds.";
    }
}