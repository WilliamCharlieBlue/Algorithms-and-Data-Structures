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

// Two Ways Quick Sort
// 对arr[l...r]部分进行partition操作
// 返回p，使得arr[l...p-1] < arr[p]; arr[p+1...r] > arr[p]
template<typename T>
int __partition2Ways(T arr[], int l, int r) {

    // 优化2：随机选取标定点,与最左侧的元素交换
    swap(arr[l], arr[rand()%(r-l+1) + l]);

    T v = arr[l];

    // arr[l+1...i) < v; arr(j...r] > v
    // 利用j=l，i=l+1的定义使得初始的结果为空，也符合上面的性质
    // 优化3：使用双路快排partition
    int i = l+1, j = r;
    while (true){
        while(i <= r && arr[i] < v) i++;
        while(j >= l+1 && arr[j] > v) j--;
        if( i > j) break;
        swap(arr[i], arr[j]);
        i++; j--;
    }
    // 最后把设定的pivot点和分界点交换位置
    swap(arr[l], arr[j]);
    // 把标定点最后的索引传出来
    return j;

}

// 对arr[l...r]部分进行快速排序
template<typename T>
void __quickSort2Ways(T arr[], int l, int r){
    // 优化2：在递归到比较小的区间时改用Insertion Sort
//    if(l>=r)
//        return;
    if(r-l <= 15){
        insertionSort(arr, l, r);
        return;
    }

    int p = __partition2Ways(arr, l, r);
    __quickSort2Ways(arr, l, p-1);
    __quickSort2Ways(arr, p+1, r);

}

template<typename T>
void quickSort2Ways(T arr[], int n){
    srand(time(NULL));
    __quickSort2Ways(arr, 0, n-1);
}

// Three Ways Quick Sort
// 三路快速排序处理对arr[l...r]
// 将arr[l...r]分为 <v; =v; >v; 三部分
// 之后递归对 <v; >v 两部分继续进行三路快速排序
template<typename T>
void __quickSort3Ways(T arr[], int l, int r){
    // 优化2：在递归到比较小的区间时改用Insertion Sort
//    if(l>=r)
//        return;
    if(r-l <= 15){
        insertionSort(arr, l, r);
        return;
    }
    // 优化4：partition不在是返回一个坐标了，写进排序里
    // partition
    swap(arr[l], arr[rand()%(r-l+1) + l]);
    T v = arr[l];

    int lt = l; // arr[l+1...lt] < v
    int gt = r+1; // arr[gt...r] > v
    int i = l+1; // arr[lt+1...i) == v
    while(i < gt){
        if(arr[i] < v){
            swap(arr[lt+1], arr[i]);
            lt++; i++;
        }
        else if(arr[i] > v){
            swap(arr[i], arr[gt-1]);
            gt--; // 此时i位置的元素还未考察，i的位置不用动
        }
        else{ //arr[i] == v
            i++;
        }
    }
    swap(arr[l], arr[lt]);
    // 由于swap(arr[l], arr[lt])，lt的位置其实是=v的,需减一下
    lt--;

    __quickSort3Ways(arr, l, lt);
    __quickSort3Ways(arr, gt, r);
}

template<typename T>
void quickSort3Ways(T arr[], int n){
    srand(time(NULL));
    __quickSort3Ways(arr, 0, n-1);
}

#endif