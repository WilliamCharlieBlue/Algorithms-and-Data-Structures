#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "InsertionSort.h"


using namespace std;


//    // 完全遍历N轮，每一轮都进行一次冒泡
//template<typename T>
//void bubbleSort(T arr[], int n){
//    for(int i=0; i<n; i++){
//        for(int j=1; j<n; j++){
//            if(arr[j-1] > arr[j]){
//                swap(arr[j-1], arr[j]);
//            }
//        }
//    }
//}

//    // 设置一个排序完成的标志, 并且每次循环n的大小在递减
//template<typename T>
//void bubbleSort(T arr[], int n) {
//
//    bool swapped; //使用swapped记录是否进行了交换
//    do {
//        // 初始化为fasle，用于后续判断
//        swapped = false;
//        for (int i = 1; i < n; i++) {
//            // 如果进行了交换操作，说明还在排序中，swapped会返回true，while循环继续。
//            // 如果没有交换，说明已经时完全有序了，swapped会返回false，结束while循环。
//            if(arr[i-1] > arr[i]){
//                swap(arr[i-1], arr[i]);
//                swapped = true;
//            }
//        }
//        // 每一轮Bubble Sort都会把最大的元素放在最后
//        // 所以下一次排序的时候，后面的元素就可以不再考虑了
//        n--;
//    // 当某一轮不再排序时，结束循环
//    }while (swapped);
//}

// 设置一个排序完成的标志(利用这个标志记录这一轮最后交换的位置，这位置之后的元素不再考虑), 并且每次循环n的大小可以锐减
template<typename T>
void bubbleSort(T arr[], int n) {

    int newn; // 使用newn记录最后交换的位置
    do {
        // 初始化为0，用于后续判断
        newn = 0;
        for (int i = 1; i < n; i++) {
            // 如果进行了交换操作，说明还在排序中，swapped会返回true，while循环继续。
            // 如果没有交换，说明已经时完全有序了，swapped会返回false，结束while循环。
            if(arr[i-1] > arr[i]){
                swap(arr[i-1], arr[i]);
                newn = i;
            }
        }
        // 每一轮Bubble Sort最后一次的交换位置记录下来
        // 这位置之后的元素之后将不再考虑
        n = newn;
        // 当某一轮不再排序时，结束循环
    }while (newn > 0);
}

int main(){

    int n = 20000;
    // 完全随机的数组
//    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    // 近乎有序的数组
    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 100);
//    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 10);

    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);

    cout << "NearlyOrderedArray(n, 100): " << endl;
    SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);

    delete []arr;
    delete []arr2;
    delete []arr3;

    cout << "OrderedArray(n, 0): " << endl;
    arr = SortTestHelper::generateNearlyOrderedArray(n, 0);
    arr2 = SortTestHelper::copyIntArray(arr, n);
    arr3 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);
    SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);


    delete []arr;
    delete []arr2;
    delete []arr3;
    arr = NULL;
    arr2 = NULL;
    arr3 = NULL;

    return 0;
}