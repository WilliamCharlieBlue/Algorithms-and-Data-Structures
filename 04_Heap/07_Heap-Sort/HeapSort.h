#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "MaxHeap.h"


template<typename T>
void heapSort_insert(T arr[], int n){
    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for(int i=0; i<n; i++)
        maxheap.insert(arr[i]);

    // 从小到大地取出
    for(int i=n-1; i>=0; i--)
        arr[i] = maxheap.extractMax();
}

template<typename T>
void heapSort_heapify(T arr[], int n) {
    MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
    // 从小到大地取出
    for(int i=n-1; i>=0; i--)
        arr[i] = maxheap.extractMax();
}

template<typename T>
void __shiftDown(T arr[], int n, int k){
    T e = arr[k];
    while(2*k+1 <= n){
        int j = 2*k+1; // 在此循环中，data[k]和data[j]交换位置
        if(j+1 < n && arr[j+1] > arr[j])
            j += 1;

        if(arr[k] >= arr[j])
            break;

        // swap(arr[k], arr[j]);
        arr[k] = arr[j];
        k = j;
    }
    arr[k] = e;
}

template<typename T>
void heapSort(T arr[], int n){
    // 索引开始0开始
    // 先进行heapify过程
    for(int i= (n-1)/2; i>=0; i--)
        __shiftDown(arr, n, i);

    for(int i=n-1; i>0; i--){
        swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0);
    }
}

#endif