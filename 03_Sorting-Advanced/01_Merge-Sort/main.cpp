#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
//#include "SelectionSort.h"
#include "InsertionSort.h"
//#include "BubbleSort.h"
//#include "ShellSort.h"
#include "MergeSort.h"

using namespace std;


int main(){

    int n = 60000;
    // 完全随机的数组
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
//    int *arr4 = SortTestHelper::copyIntArray(arr, n);

    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;

    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
//    SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);
//    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
//    SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
    SortTestHelper::testSort("Merge Sort BU", mergeSortBU, arr3, n);

    delete []arr;
    delete []arr2;
    delete []arr3;
//    delete []arr4;

    int swapTimes = 25;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    // 近乎有序的数组
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
//    arr4 = SortTestHelper::copyIntArray(arr, n);




    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
//    SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);
//    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
//    SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
    SortTestHelper::testSort("Merge Sort BU", mergeSortBU, arr3, n);

    delete []arr;
    delete []arr2;
    delete []arr3;
//    delete []arr4;
    arr = NULL;
    arr2 = NULL;
    arr3 = NULL;
//    arr4 = NULL;

    return 0;
}