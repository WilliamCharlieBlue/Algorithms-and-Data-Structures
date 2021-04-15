#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"

using namespace std;

void selectionSort(int arr[], int n){
    for(int i=0; i<n; i++){
        // 寻找[i,n)区间里的最小值
        int minIndex = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }

        swap(arr[i], arr[minIndex]);
    }
}

int main(){
//    int a[10] = {10,9,8,7,6,5,4,3,2,1};
//    selectionSort(a, 10);
//    for(int i=0; i<10; i++){
//        cout << a[i] << " ";
//    }
//    cout << endl;

    int n = 100000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
//    selectionSort(arr, n);
//    SortTestHelper::printArray(arr, n);
    // 将排序算法作为参数传入
    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    // selectionSort 10000->0.165 s; 100000->17.355 s; 数量为10倍，而时间为100倍，因此是O(n2)级别的算法
    delete []arr;

    return 0;
}