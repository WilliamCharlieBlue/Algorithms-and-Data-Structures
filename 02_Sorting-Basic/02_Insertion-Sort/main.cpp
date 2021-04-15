#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "SelectionSort.h"

using namespace std;

void selectionSort(int arr[], int n){
    for(int i=0; i<n; i++){
        // 寻找[i,n)区间里的最小值
        int minIndex = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }

        swap(arr[i], arr[minIndex]);
    }
}

//    // 通过交换操作实现Insertion Sort，效率要低于Selection Sort，因为交换操作很耗时，需要三次赋值
//template<typename T>
//void insertionSort(T arr[], int n){
//    for(int i=0; i<n; i++){
//        // 寻找元素arr[i]合适的插入位置
//        // 第二轮循环时可以提前终止的arr[j]<arr[j-1]
//        for(int j=i; j>0 && arr[j] < arr[j-1]; j--){
//            swap(arr[j], arr[j-1]);
//        }
//    }
//}

template<typename T>
void insertionSort(T arr[], int n){
    for(int i=0; i<n; i++){
        // 寻找元素arr[i]合适的插入位置
        // 第二轮循环时可以提前终止的arr[j]<arr[j-1]
        T e = arr[i];
        int j; // j保存元素e应该插入的位置
        // 第二轮循环时可以提前终止条件，找到了合适的位置，arr[j-1] >e
        for(j=i; j>0 && arr[j-1] >e ; j--){
            // 如果j之前的元素比当前元素还要大，把j之前的元素往后挪一位
            arr[j] = arr[j-1];
        }
        // 最后把第一轮循环里的比较对象赋值给正确的位置
        arr[j] = e;
    }
}

int main(){

    int n = 10000;
    // 完全随机的数组
//    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    // 近乎有序的数组
    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 100);
//    int *arr = SortTestHelper::generateNearlyOrderedArrary(n, 10);

    int *arr2 = SortTestHelper::copyIntArray(arr, n);


    //Selection Sort:0.167 s
    SortTestHelper::testSort("Selection Sort", selectionSort, arr2, n);
    //Insertion Sort:0.334 s , 此时显示的Insertion Sort更慢，是因为暂时没优化
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr, n);


    delete []arr;
    delete []arr2;
    arr = NULL;
    arr2 = NULL;

    return 0;
}