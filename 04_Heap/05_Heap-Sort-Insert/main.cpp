#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>
#include "MaxHeap.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "SortTestHelper.h"

using namespace std;

template<typename T>
void heapSort1(T arr[], int n){
    MaxHeap<int> maxheap = MaxHeap<T>(n);
    for(int i=0; i<n; i++)
        maxheap.insert(arr[i]);

    // 从小到大地取出
    for(int i=n-1; i>=0; i--)
        arr[i] = maxheap.extractMax();
}

int main(){

    int n = 1000000;

    // 一般性测试
    cout <<"Test for Random Array, size = " << n << ", random range [0,"<< n << "]" << endl;
    int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyIntArray(arr1,n);
    int* arr3 = SortTestHelper::copyIntArray(arr1,n);
    int* arr4 = SortTestHelper::copyIntArray(arr1,n);
    int* arr5 = SortTestHelper::copyIntArray(arr1,n);
    int* arr6 = SortTestHelper::copyIntArray(arr1,n);
    int* arr7 = SortTestHelper::copyIntArray(arr1,n);


    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 2 ways", quickSort2Ways, arr3, n);
    SortTestHelper::testSort("Quick Sort 3 ways", quickSort3Ways, arr4, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr5, n);

    delete []arr1;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    delete []arr5;
    delete []arr6;
    delete []arr7;

    // 测试近乎有序的数组
    int swapTimes = 100;
    cout <<"Test for Nearly ordered Array, size = " << n << ", swap time = "<< swapTimes <<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1,n);
    arr3 = SortTestHelper::copyIntArray(arr1,n);
    arr4 = SortTestHelper::copyIntArray(arr1,n);
    arr5 = SortTestHelper::copyIntArray(arr1,n);
    arr6 = SortTestHelper::copyIntArray(arr1,n);
    arr7 = SortTestHelper::copyIntArray(arr1,n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 2 ways", quickSort2Ways, arr3, n);
    SortTestHelper::testSort("Quick Sort 3 ways", quickSort3Ways, arr4, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr5, n);

    delete []arr1;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    delete []arr5;
    delete []arr6;
    delete []arr7;

    // 测试存在包含大量相同元素的数组
    cout << "Test for random array, size = "<< n <<", random range [0,10]" << endl;
    arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
    arr2 = SortTestHelper::copyIntArray(arr1,n);
    arr3 = SortTestHelper::copyIntArray(arr1,n);
    arr4 = SortTestHelper::copyIntArray(arr1,n);
    arr5 = SortTestHelper::copyIntArray(arr1,n);
    arr6 = SortTestHelper::copyIntArray(arr1,n);
    arr7 = SortTestHelper::copyIntArray(arr1,n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
//    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n); // 退化为O(n^2)不进行测试
    SortTestHelper::testSort("Quick Sort 2 ways", quickSort2Ways, arr3, n);
    SortTestHelper::testSort("Quick Sort 3 ways", quickSort3Ways, arr4, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr5, n);

    delete []arr1;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    delete []arr5;
    delete []arr6;
    delete []arr7;

    return 0;
}