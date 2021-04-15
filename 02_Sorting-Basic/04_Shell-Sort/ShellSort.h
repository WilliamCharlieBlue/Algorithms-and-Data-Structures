#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include <iostream>
#include <algorithm>

using namespace std;

//    // 步长使用2，而且使用>>右移运算符
//template<typename T>
//void shellSort(T arr[], int n){
//    // >>n 在C++里是二进制右移运算符，各二进制位全部右移n位，正数左补0，负数左补1，右边丢弃。
//    // >>n 及除以（2^n）倍，即>>1是除以2；>>2是除以4；>>3是除以8
//    // 这里每一次的步长都以缩小2倍
//    for(int gap=n>>1; gap>0; gap>>=1){
//        for(int i=gap; i<n; i++){
//            T temp = arr[i];
//            int j = i - gap;
//        //    while (j>=0 && arr[j] > temp){
//        //        arr[j+gap] = arr[j];
//        //        j -= gap;
//        //    }
//            for(; j>=0 && arr[j] > temp; j-=gap)
//                arr[j+gap] = arr[j];
//            arr[j+gap] = temp;
//        }
//    }
//}

// 使用步长为3
template<typename T>
void shellSort(T arr[], int n){
    // 计算 increment sequence: 1, 4, 13, 40, 121, 364, 1093...
    int h = 1;
    // 如果将最大的步长扩展到超过数组大小的三分之一
    while (h < n/3)
        h = 3*h +1;

    while (h >=1){
        // h-sort the array
        for(int i=h; i<n; i++){
            // 对 arr[i], arr[i-h], arr[i-2*h], arr[i-3*h]... 使用插入排序
            T e = arr[i];
            int j;
            for(j=i; j>=h && e<arr[j-h]; j-=h){
                arr[j] = arr[j-h];
            }
            arr[j] = e;
        }
        h /= 3;
    }
}

#endif