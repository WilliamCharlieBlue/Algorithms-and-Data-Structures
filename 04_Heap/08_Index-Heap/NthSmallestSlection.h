#ifndef NTH_SMALLEST_SELECTION_H
#define NTH_SMALLEST_SELECTION_H

#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;

// partition 过程和 快排的partion一样
// 思考：双路快排和三路快排的思想能不能用在selection算法中？
template<typename T>
int __partition(T arr[], int l, int r){
    int p = rand()%(r-l+1) + l;
    swap(arr[l], arr[p]);

    int j = l; // [l+1...j] < p; [lt+1...i) > p
    for(int i=l+1; i<=r; i++)
        if(arr[i] < arr[l]){
            swap(arr[i], arr[++j]); //与下面两句等价
//            swap(arr[i], arr[j]);
//            j++;
        }

    swap(arr[l], arr[j]);
    return j;
}

// 求出arr[l...r]范围里第k小的数
template<typename T>
T __selection(T arr[], int l, int r, int k){

    if(l == r)
        return arr[l];

    // partition之后，arr[p]的正确位置就在索引p上
    int p = __partition(arr, l, r);

    if(k == p) // 如果k == p, 直接返回arr[p]
        return arr[p];
    else if( k < p)  // 如果k < p , 只需要在arr[l...p-1]中找第k小元素即可
        return __selection(arr, l, p-1, k);
    else    // 如果k > p, 则需要在arr[p+1...r]中找第k-p-1小的元素
        // 由于__selection传入的依然是arr，而不是arr[p+1...r]
        // 所以，最后一个参数依然是k，而不是k-p-1
        return __selection(arr, p+1, r, k);
}

// 寻找arr数组中第k小的元素
// 注意，在我们的算法中，k是从0开始索引的，即最小的元素是第0小的元素，以此类推
// 如果希望我们的算法中k的语义是从1开始的，只需要在整个逻辑开始进行k-1即可，例如selection2
template<typename T>
T selection0(T arr[], int n, int k){
    assert(k >=0 && k < n);

    srand(time(NULL));
    return __selection(arr, 0, n-1, k);
}

// 寻找arr数组中第k小的元素，k从1开始索引，即最小元素是第1小元素，以此类推
template<typename T>
T selection(T arr[], int n, int k){

    return selection0(arr, n, k-1);
}

#endif