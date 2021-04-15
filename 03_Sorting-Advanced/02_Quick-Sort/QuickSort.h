#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

// 对arr[l...r]部分进行partition操作
// 返回p，使得arr[l...p-1] < arr[p]; arr[p+1...r] > arr[p]
template<typename T>
int __partition(T arr[], int l, int r) {


    // 优化2：随机选取标定点,与最左侧的元素交换
    swap(arr[l], arr[rand()%(r-l+1) + l]);

    T v = arr[l];

    // arr[l+1...j] < v; arr[j+1...i) > v
    // 利用j=l，i=l+1的定义使得初始的结果为空，也符合上面的性质
    int j = l;
    for(int i=l+1; i<=r; i++){
        if(arr[i] < v){
            // swap(arr[++j], arr[i]); 等价于下面两行
            swap(arr[j+1], arr[i]);
            j++;
        }
    }

    // 最后把设定的pivot点和分界点交换位置
    swap(arr[l], arr[j]);
    // 把标定点最后的索引传出来
    return j;
}

// 对arr[l...r]部分进行快速排序
template<typename T>
void __quickSort(T arr[], int l, int r){
    // 优化2：在递归到比较小的区间时改用Insertion Sort
//    if(l>=r)
//        return;
    if(r-l <= 15){
        insertionSort(arr, l, r);
        return;
    }

    int p = __partition(arr, l, r);
    __quickSort(arr, l, p-1);
    __quickSort(arr, p+1, r);

}

template<typename T>
void quickSort(T arr[], int n){
    srand(time(NULL));
    __quickSort(arr, 0, n-1);
}

#endif