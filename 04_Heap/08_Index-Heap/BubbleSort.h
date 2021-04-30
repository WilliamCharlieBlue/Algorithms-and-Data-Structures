#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <iostream>
#include <algorithm>

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

#endif