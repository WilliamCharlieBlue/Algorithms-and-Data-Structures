#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
//#include "SelectionSort.h"
#include "InsertionSort.h"
//#include "BubbleSort.h"
//#include "ShellSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std;




int main(){

    int n = 1000000;
    // 完全随机的数组
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
    int *arr4 = SortTestHelper::copyIntArray(arr, n);
    int *arr5 = SortTestHelper::copyIntArray(arr, n);
    int *arr6 = SortTestHelper::copyIntArray(arr, n);

    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;

//    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
//    SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);
//    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
//    SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
    SortTestHelper::testSort("Merge Sort BU", mergeSortBU, arr3, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr4, n);
    SortTestHelper::testSort("Quick Sort Two Ways", quickSort2Ways, arr5, n);
    SortTestHelper::testSort("Quick Sort Three Ways", quickSort3Ways, arr6, n);

    delete []arr;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    delete []arr5;
    delete []arr6;

    int swapTimes = 25;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    // 近乎有序的数组
    arr = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);
    arr6 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
    SortTestHelper::testSort("Merge Sort BU", mergeSortBU, arr3, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr4, n);
    SortTestHelper::testSort("Quick Sort Two Ways", quickSort2Ways, arr5, n);
    SortTestHelper::testSort("Quick Sort Three Ways", quickSort3Ways, arr6, n);

    delete []arr;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    delete []arr5;
    delete []arr6;

    cout<<"Test for random array, size = "<<n<<", random range [0,10]"<<endl;
    arr = SortTestHelper::generateRandomArray(n, 0, 10);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);
    arr4 = SortTestHelper::copyIntArray(arr, n);
    arr5 = SortTestHelper::copyIntArray(arr, n);
    arr6 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
    SortTestHelper::testSort("Merge Sort BU", mergeSortBU, arr3, n);
//    SortTestHelper::testSort("Quick Sort", quickSort, arr4, n); // 运行崩溃了
    SortTestHelper::testSort("Quick Sort Two Ways", quickSort2Ways, arr5, n);
    SortTestHelper::testSort("Quick Sort Three Ways", quickSort3Ways, arr6, n);

    delete []arr;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    delete []arr5;
    delete []arr6;

    return 0;
}