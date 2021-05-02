#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

// 二分查找法，在有序的数组arr中，查找target
template<typename T>
int binarySearch(T arr[], int n, T target){
    // 在arr[l...r]之中查找target
    int l = 0, r = n-1;
    while(l <= r){
        //int mid = (l+r)/2;
        // int型 l + r 容易溢出，而如果使用减法就可避免
        int mid = l + (r-l)/2;
        if(arr[mid] == target)
            return mid;

        if(target < arr[mid])
            // 在arr[l...mid-1]之中查找target
            r = mid - 1;
        else
            // 在arr[mid+1...r]之中查找target
            l = mid + 1;
    }
    return -1;
}

// 二分查找法递归实现，在有序的数组arr中，查找target
template<typename T>
int _binarySearch_Recursion(T arr[], int l, int r, T target){
    // 在arr[l...r]之中查找target
    if(l > r)
        return -1;
    //int mid = (l+r)/2;
    // int型 l + r 容易溢出，而如果使用减法就可避免
    int mid = l + (r-l)/2;
    if(arr[mid] == target)
        return mid;
    else if(target < arr[mid])
        // 在arr[l...mid-1]之中查找target
        _binarySearch_Recursion(arr, l, mid-1, target);
    else
        // 在arr[mid+1...r]之中查找target
        _binarySearch_Recursion(arr, mid+1, r, target);
}

template<typename T>
int binarySearch_Recursion(T arr[], int n, T target){
    _binarySearch_Recursion(arr, 0, n-1, target);
}


// 测试我们用迭代和递归实现的二分查找法
int main(){
    int n = 1000000;
    int* a = new int[n];
    for(int i=0; i<n; i++)
        a[i] = i;

    // 测试非递归二分查找法
    clock_t startTime = clock();
    // 对于我们的待查找数组[0...N)
    // 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
    // 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
    for(int i=0; i<2*n; i++){
        int v = binarySearch(a, n, i);
        if(i < n)
            assert( v == i);
        else
            assert( v == -1);
    }
    clock_t endTime = clock();
    cout << "Binary Search (without Recursion): " << double(endTime -startTime)/CLOCKS_PER_SEC << " s"<< endl;

// 测试递归二分查找法
    startTime = clock();
    // 对于我们的待查找数组[0...N)
    // 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
    // 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
    for(int i=0; i<2*n; i++){
        int v = binarySearch_Recursion(a, n, i);
        if(i < n)
            assert( v == i);
        else
            assert( v == -1);
    }
    endTime = clock();
    cout << "Binary Search (with Recursion): " << double(endTime -startTime)/CLOCKS_PER_SEC << " s"<< endl;

    return 0;
}