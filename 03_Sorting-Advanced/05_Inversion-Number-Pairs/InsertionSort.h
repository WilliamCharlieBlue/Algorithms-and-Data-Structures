#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <iostream>
#include <algorithm>

using namespace std;

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

    // 通过赋值操作实现Insertion Sort，效率大大提高，在解决近乎有序的数组时，逼近O(n)
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

// 在其他排序算法的尾声（即比较小的区间内的排序）时，对arr[l...r]调用end_insertionSort
template<typename T>
void insertionSort(T arr[], int l, int r) {
    for(int i=l+1; i<=r; i++){
        T e = arr[i];
        int j;
        for(j=i; j>l && arr[j-1] > e; j--){
            arr[j] = arr[j-1];
        }
        arr[j] = e;
    }
    return;
}

#endif