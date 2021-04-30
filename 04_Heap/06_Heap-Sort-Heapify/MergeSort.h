#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <iostream>
#include <algorithm>

using namespace std;

// 将arr[l...mid]和arr[mid+1...r]两部分进程归并
template<typename T>
void __merge(T arr[], int l, int mid, int r){
    // 创建一个临时空间
    T *aux = new T[r-l+1];
    for(int i=l; i<=r; i++){
        aux[i-l] = arr[i];
    }

    int i = l, j = mid+1;
    for(int k=l; k<=r; k++){
        // 先判断索引是否越界
        // 如果i越界了，说明右边还没归并完；反之，j越界了，说明左边还没归并完
        if(i>mid){
            arr[k] = aux[j-l];
            j++;
        }
        else if(j>r){
            arr[k] = aux[i-l];
            i++;
        }
            // 如果i和j都合法，看两边哪个小就放哪个，左边的优先放
        else if(aux[i-l] <= aux[j-l]){
            arr[k] = aux[i-l];
            i++;
        }
        else{
            arr[k] = aux[j-l];
            j++;
        }
    }

    delete []aux;
}

// 递归使用归并排序，对arr[l...r]的范围进行排序
template<typename T>
void __mergeSort(T arr[], int l, int r){
    // 元素只有1个元素或1个元素都没有
    // 也是直接递归到底的情况
//    if(l >= r)
//        return;
    // 优化1：在递归到比较小的区间时改用Insertion Sort
    if(r-l <= 15){
        insertionSort(arr, l, r);
        return;
    }

    int mid = (l+r)/2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    //无论如何都进行一次归并
//    __merge(arr, l, mid, r);

    // 优化2：如果arr[mid] <= arr[mid+1],则arr整个是有序的
    // 虽然会增加一些开销，但如果有近乎有序数组的情况，加上效率更高
    if(arr[mid] > arr[mid+1])
        __merge(arr, l, mid, r);
}

// 由顶向下地实现 MergeSort，需要递归来实现
template<typename T>
void mergeSort(T arr[], int n){
    __mergeSort(arr, 0, n-1);
}


// 由底向上地实现 MergeSortBU，不需要递归，指用迭代就可以
template<typename T>
void mergeSortBU(T arr[], int n){

    //不进行任何优化的mergeSortBU，区间进行从小到大的归并
    for(int sz=1; sz<n; sz += sz)
        for(int i=0; i+sz < n; i += sz+sz)
            // 对arr[i...i=sz-1] 和 arr[i+sz...i+2*sz+1]进行归并
            __merge(arr, i, i+sz-1, min(i+sz+sz-1, n-1));

    // 优化1：小区域使用insertionSort
    for(int i=0; i<n; i += 16)
        insertionSort(arr, i, min(i+15, n-1));

    for(int sz=16; sz<n; sz += sz)
        for(int i=16; i+sz < n; i += sz+sz)
            // 优化2：对于arr[mid] <= arr[mid+1]的情况,不进行merge
            if(arr[i+sz-1] > arr[i+sz])
                __merge(arr, i, i+sz-1, min(i+sz+sz-1, n-1));
}

#endif