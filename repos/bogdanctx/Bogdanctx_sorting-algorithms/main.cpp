#include <iostream>
#include <vector>

#include "QuickSort.h"
#include "NativeSort.h"
#include "ShellSort.h"
#include "HeapSort.h"
#include "RadixIntSort.h"
#include "MergeSort.h"
#include "TimSort.h"
#include "MergeSortMirror.h"
#include "MergeSortIfState.h"
#include "BottomUpMergeSort.h"
#include "BottomUpMergeSortAlternateVectors.h"

#include "random.hpp"

int main() {
    // (size, nr_minim, nr_maxim)
    const std::vector<std::vector<long long int>> tests = {
            {1000, 0, 1000000}, // N=10^3, min=0, max=10^6 0)
            {1000, -1000000, 1000000}, // N=10^4, min=-10^6, max=10^6 1)
            {10000, 0, 1000}, // N=10^5, min=0, max=10^4 2)
            {100000, -100000, 100000}, // N=10^6, min=-10^6, max=10^6 3)
            {1000000, 0, 10000000}, // N=10^7, min=0, max=10^7 4)
            {100000000, 0, 1000}, // N=10^8, min=0, max=10^3 5)
            {100000000, -100000, 100000}, // N=10^8, min=-10^5, max=10^5 6)
            {100000000, 0, 100000000}, // N=10^8, min=0, max=10^8 7)
            {100000000, 0, 1000000000000}, // N=10^8, min=0, max=10^12 8)
            {100000000, -1000000000000, 1000000000000}, // N=10^8, min=-10^12, max=10^12 9)
            {100000000, 0, 10000000000000000}, // N=10^8, min=0, max=10^16 10)
            {100000000, -10000000000000000, 10000000000000000}, // N=10^8, min=-10^16, max=10^16 11)
    };
    const std::vector<std::string> testInfo = {
            "N=10^3, min=0, max=10^6", // 0
            "N=10^4, min=-10^6, max=10^6", // 1
            "N=10^5, min=0, max=10^4", // 2
            "N=10^6, min=-10^6, max=10^6", // 3
            "N=10^7, min=0, max=10^7", // 4
            "N=10^8, min=0, max=10^3", // 5
            "N=10^8, min=-10^5, max=10^5", // 6
            "N=10^8, min=0, max=10^8", // 7
            "N=10^8, min=0, max=10^12", // 8
            "N=10^8, min=-10^12, max=10^12", // 9
            "N=10^8, min=0, max=10^16", // 10
            "N=10^8, min=-10^16, max=10^16", // 11
    };

    int numberOfTests = (int) tests.size();

    for(int test = 0; test < numberOfTests; test++) {
        long long int n = tests[test][0];
        long long int lowerBound = tests[test][1];
        long long int upperBound = tests[test][2];

        std::vector<long long int>nums(n);

        std::cout<<"Creating test #" << test << " input\n";

        for(long long int p = 0; p < n; p++) {
            nums[p] = effolkronium::random_static::get(lowerBound, upperBound);
        }

        std::cout<<"Done.\n\n";

        std::cout<<"############################################\n";
        std::cout<<"Test #"<<test<< " (" << testInfo[test] << ") benchmarks:\n\n";

        // Aici punem algoritmii de sortare

        QuickSort *quickSort = new QuickSort{nums};
        quickSort->begin_benchmark();
        delete quickSort;

        std::cout<<"\n\n";

        NativeSort *nativeSort = new NativeSort{nums};
        nativeSort->begin_benchmark();
        delete nativeSort;

        std::cout<<"\n\n";

        ShellSort *shellSort = new ShellSort{nums};
        shellSort->begin_benchmark();
        delete shellSort;

        ///////////////

        std::cout<<"\n\n";

        HeapSort *heapsort = new HeapSort{nums};
        heapsort->begin_benchmark();
        delete heapsort;

        std::cout<<"\n\n";

        Radix_Int_Sort *radixintsort = new Radix_Int_Sort{nums};
        radixintsort->begin_benchmark();
        delete radixintsort;

        std::cout<<"\n\n";

        ////////////////

        MergeSort *mergesort = new MergeSort{nums};
        mergesort->begin_benchmark();
        delete mergesort;

        std::cout<<"\n\n";

        BottomUpMergeSort *bottomupmergesort = new BottomUpMergeSort{nums};
        bottomupmergesort->begin_benchmark();
        delete bottomupmergesort;

        std::cout<<"\n\n";

        BottomUpMergeSortAlternateVectors *bottomupmergesortalternatevectors = new BottomUpMergeSortAlternateVectors{nums};
        bottomupmergesortalternatevectors->begin_benchmark();
        delete bottomupmergesortalternatevectors;

        std::cout<<"\n\n";

        MergeSortIfState *mergesortifstate = new MergeSortIfState{nums};
        mergesortifstate->begin_benchmark();
        delete mergesortifstate;

        std::cout<<"\n\n";

        MergeSortMirror *mergesortmirror = new MergeSortMirror{nums};
        mergesortmirror->begin_benchmark();
        delete mergesortmirror;

        std::cout<<"\n\n";

        TimSort *timsort = new TimSort{nums};
        timsort->begin_benchmark();
        delete timsort;

        std::cout<<"\n\n";

        std::cout<<"############################################";
        std::cout<<"\n\n";
    }

    return 0;
}
