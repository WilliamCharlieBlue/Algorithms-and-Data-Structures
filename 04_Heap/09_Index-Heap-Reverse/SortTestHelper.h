#ifndef SORTTESTHELPER_H
#define SORTTESTHELPER_H

#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;


namespace SortTestHelper {

    // 生成有n个元素的随机数据，每个元素的随机范围为[rangeL, rangR]
    int *generateRandomArray(int n, int rangeL, int rangeR){
        assert( rangeL <= rangeR);

        int *arr = new int[n];
        srand(time(NULL));
        for(int i=0; i<n; i++){
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }
        return arr;
    }

    int *generateNearlyOrderedArray(int n, int swapTimes){
        int *arr = new int[n];
        for(int i=0; i<n; i++){
            arr[i] = i;
        }
        srand(time(NULL));

        for(int i=0; i<swapTimes; i++){
            // x 和 y 在[0,n)之间
            int posx = rand()%n;
            int posy = rand()%n;
            swap(arr[posx], arr[posy]);
        }
        return arr;
    }

    // 生成一个完全有序的数组
    int *generateOrderedArray(int n){
        return generateNearlyOrderedArray(n, 0);
    }

    // 生成一个完全逆序的数组
    int *generateInversedArray(int n){
        int *arr = generateOrderedArray( n );
        for( int i = n/2 - 1 ; i >= 0 ; i -- )
            swap( arr[i] , arr[n-i-1]);
        return arr;
    }

    int *generateSequentialArray(int n){
        int *arr = new int[n];
        for(int i=0; i<n; i++)
            arr[i] = i;
        return arr;
    }

    template<typename T>
    void printArray(T arr[], int n) {
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        return;
    }

    template<typename T>
    bool isSorted(T arr[], int n){
        for(int i=0; i<n-1; i++){
            if(arr[i] > arr[i+1])
                return false;
        }
        return true;
    }

    template<typename T>
    void testSort(string sortName, void(*sort)(T[], int), T arr[], int n){
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();
        // 先判断是否都已经正确排序
        assert(isSorted(arr, n));
        // CLOCKS_PER_SEC 标准库中的每秒多少个始终周期
        cout << sortName << ":" << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
        return;
    }

    template<typename T>
    void shuffleArray(T arr[], int n){
        srand(time(NULL));
        for(int i=0; i<n; i++){
            int j = rand()%(n-i) + i;
            swap(arr[i], arr[j]);
        }
        return;
    }

    // 暂时只拷贝int Array
    int* copyIntArray(int a[], int n){
        int* arr = new int[n];
        // copy(a头指针，a尾指针，新数组)
        copy(a, a+n, arr);
        return arr;
    }
}
#endif


