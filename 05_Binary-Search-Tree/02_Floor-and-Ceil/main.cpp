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


// 如果找到target, 返回第一个target相应的索引index
// 如果没有找到target, 返回比target小的最大值相应的索引, 如果这个最大值有多个, 返回最大索引
// 如果这个target比整个数组的最小元素值还要小, 则不存在这个target的floor值, 返回-1
template<typename T>
int floor(T arr[], int n, T target) {
    assert(n >= 0);

    // 寻找比target小的最大索引
    int l = -1, r = n-1;
    while( l < r){
        // 使用向上取整(r-l+1)/2避免死循环
        int mid = l + (r-l+1)/2;
        if(arr[mid] >= target)
            r = mid - 1;
        else
            // 由于mid和右侧的关系不明确，不能直接排除mid
            l = mid;
    }

    assert(l == r);

    if(l+1 < n && arr[l+1] == target)
        // 如果该索引+1就是target本身, 即找到target，该索引+1即为返回值
        return l+1;
    else
        // 否则没找到target,返回比target小的最大Index, 该索引即为返回值
        return l;
}

// 如果找到target, 返回最后一个target相应的索引index
// 如果没有找到target, 返回比target大的最小值相应的索引, 如果这个最小值有多个, 返回最小的索引
// 如果这个target比整个数组的最大元素值还要大, 则不存在这个target的ceil值, 返回整个数组元素个数n
template<typename T>
int ceil(T arr[], int n, T target) {
    assert(n >= 0);

    // 寻找比target大的最小索引
    int l = 0, r = n;
    while(l < r){
        // 使用普通的向下取整(r-l)/2避免死循环
        int mid = l + (r-l)/2;
        if(arr[mid] <= target)
            l = mid + 1;
        else
            // 由于mid和左侧的关系不明确，不能直接排除mid
            r = mid;
    }

    assert(l ==r);
    if(r-1>=0 && arr[r-1] == target)
        // 如果该索引-1就是target本身, 即找到target,该索引-1即为返回值
        return r-1;
    else
        // 否则没找到target,返回比target大的最小Index,该索引即为返回值
        return r;
}


// 测试我们用二分查找法实现的floor和ceil两个函数
int main() {

    int a[] = {1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 5, 5, 5, 6, 6, 6};
    int n = sizeof(a) / sizeof(int);
    for (int i = 0; i <= 8; i++) {

        int floorIndex = floor(a, n, i);
        cout << "the floor index of " << i << " is " << floorIndex << ".";
        if (floorIndex >= 0 && floorIndex < n)
            cout << "The value is " << a[floorIndex] << ".";
        cout << endl;

        int ceilIndex = ceil(a, sizeof(a) / sizeof(int), i);
        cout << "the ceil index of " << i << " is " << ceilIndex << ".";
        if (ceilIndex >= 0 && ceilIndex < n)
            cout << "The value is " << a[ceilIndex] << ".";
        cout << endl;

        cout << endl;
    }
}

// 测试我们用迭代和递归实现的二分查找法
//int main(){
//    int n = 1000000;
//    int* a = new int[n];
//    for(int i=0; i<n; i++)
//        a[i] = i;
//
//    // 测试非递归二分查找法
//    clock_t startTime = clock();
//    // 对于我们的待查找数组[0...N)
//    // 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
//    // 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
//    for(int i=0; i<2*n; i++){
//        int v = binarySearch(a, n, i);
//        if(i < n)
//            assert( v == i);
//        else
//            assert( v == -1);
//    }
//    clock_t endTime = clock();
//    cout << "Binary Search (without Recursion): " << double(endTime -startTime)/CLOCKS_PER_SEC << " s"<< endl;
//
//// 测试递归二分查找法
//    startTime = clock();
//    // 对于我们的待查找数组[0...N)
//    // 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
//    // 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
//    for(int i=0; i<2*n; i++){
//        int v = binarySearch_Recursion(a, n, i);
//        if(i < n)
//            assert( v == i);
//        else
//            assert( v == -1);
//    }
//    endTime = clock();
//    cout << "Binary Search (with Recursion): " << double(endTime -startTime)/CLOCKS_PER_SEC << " s"<< endl;
//
//    return 0;
//}