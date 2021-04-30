#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>
#include "MaxHeap.h"
#include "SortTestHelper.h"

using namespace std;


template<typename Item>
class IndexHeap{
private:
    Item* data;
    int* indexes;
    int count;
    int capacity;

    // shiftUp中使用赋值来进行交换
    void shiftUp(int k) {
        Item e = data[indexes[k]];
        int srck = indexes[k];
        while (k > 1 && data[indexes[k/2]] < e) {
            //swap(indexes[k/2], indexes[k]);
            indexes[k] = indexes[k/2];
            k /= 2;
        }
        indexes[k] = srck;
    }

    // shiftDown中使用赋值来进行交换
    void shiftDown(int k){
        Item e = data[indexes[k]];
        int srck = indexes[k];
        // 有右子节点的话，已经有左子节点
        while(2*k <= count){
            int j = 2*k; // 在此轮循环中，data[k]和data[j]交换位置
            if(j+1 <= count && data[indexes[j+1]] > data[indexes[j]])  // 如果有右子节点，而且比左子节点大，就那关注右子节点
                j += 1;

            if(e > data[indexes[j]]) // 父节点比子节点大，则不需要交换
                break;

            indexes[k] = indexes[j];
            k = j;
        }
       indexes[k] = srck;
    }

public:
    IndexHeap(int capacity){
        // 索引0不适用，从索引1开始
        data = new Item[capacity + 1];
        indexes = new Item[capacity + 1];
        count = 0;
        this->capacity = capacity;
    }
    // 用于Heapify的构造函数
    IndexHeap(Item arr[], int n){
        data = new Item[n+1];
        capacity = n;
        for(int i=0; i<n; i++)
            data[i+1] = arr[i];
        count = n;
        // 第一个非末端子节点为  堆内元素数量/2
        // 从第一个非末端子节点开始，进行shiftdown，使得整个堆符合最大堆性质
        for(int i= count/2; i>=1; i--)
            shiftDown(i);
    }

    ~IndexHeap(){
        delete []data;
        delete []indexes;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count==0;
    }
    // 传入的i对用户而言，是从0索引的
    void insert(int i, Item item){

        assert(count+1 <= capacity);
        assert(i+1>=1 && i+1 <= capacity);
        // 内部转化为从1开始索引
        i +=1;
        //
        data[i] = item;
        indexes[count+1] = i;

        count++;
        shiftUp(count);
    }

    Item extractMax(){
        assert(count > 0);
        Item ret = data[indexes[1]];
        swap(indexes[1], indexes[count]);
        count --;
        shiftDown(1);
        return ret;
    }

    int extractMaxIndex(){
        assert(count > 0);
        // 我们目前的索引堆是从1开始的；而用户期望的返回值是从0开始
        int ret = indexes[1] - 1;
        swap(indexes[1], indexes[count]);
        count --;
        shiftDown(1);
        return ret;
    }

    // 通过索引来获取数据
    Item getItem(int i){
        return data[i+1];
    }

    void change(int i, Item newItem){
        i += 1;
        data[i] = newItem;

        // 找到indexes[j] = i, j表示data[i]在堆中的位置
        // 之后shiftUp(j), 再shifDown(j)

        // 方法一：遍历堆，遍历O(n)，shiftUp/shiftDown最差为O(logn),整体最差可能达到O(n^2)
        for(int j=1; j<=count; j++)
            if(indexes[j] == i){
                shiftUp(j);
                shiftDown(j);
                return;
            }
    }

public:
    // 测试索引堆中的索引数组index
    // 注意:这个测试在向堆中插入元素以后, 不进行extract操作有效
    bool testIndexes(){
        int *copyIndexes = new int[count+1];
        for(int i=0; i<=count; i++)
            copyIndexes[i] = indexes[i];

        copyIndexes[0] = 0;
        sort(copyIndexes, copyIndexes+count+1);
        // 在对索引堆中的索引进行排序后, 应该正好是1...count这count个索引
        bool res = true;
        for(int i=1; i<=count; i++)
            if(copyIndexes[i-1] + 1 != copyIndexes[i]){
                res = false;
                break;
            }
        delete []copyIndexes;
        if(!res){
            cout<<"Error!"<<endl;
            return false;
        }
        return true;
    }


    void testPrint(){
        if( size() >= 100 ){
            cout << "Fancy print can only work for less than 100 int" << endl;
            return;
        }

        if( typeid(Item) != typeid(int)){
            cout << "Fancy print can only work for int item" << endl;
        }

        cout << "The Heap size is: " << size() << endl;
        cout << "data in heap: " << endl;
        for(int i=1; i<=size(); i++)
            cout << data[i] << " ";
        cout << endl << endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while(n>0){
            max_level += 1;
            n -= number_per_level;
            number_per_level *=2;
        }
        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for(int level=0; level < max_level; level++){
            string line1 = string(max_level_number*3-1, ' ');

            int cur_level_number = min(count - int(pow(2,level))+1, int(pow(2,level)));
            bool isLeft = true;
            for(int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++){
                putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number*3-1, isLeft);
                isLeft = !isLeft;
            }
            cout << line1 << endl;

            if(level == max_level -1)
                break;

            string line2 = string(max_level_number*3-1, ' ');
            for(int index_cur_level=0; index_cur_level < cur_level_number; index_cur_level++)
                putBranchInLine(line2, index_cur_level, cur_tree_max_level_number*3-1);
            cout << line2 << endl;

            cur_tree_max_level_number /= 2;
        }

    }

private:
    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }
};

template<typename T>
void heapSort_insert(T arr[], int n){
    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for(int i=0; i<n; i++)
        maxheap.insert(arr[i]);

    // 从小到大地取出
    for(int i=n-1; i>=0; i--)
        arr[i] = maxheap.extractMax();
}

template<typename T>
void heapSort_heapify(T arr[], int n) {
    MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
    // 从小到大地取出
    for(int i=n-1; i>=0; i--)
        arr[i] = maxheap.extractMax();
}

template<typename T>
void __shiftDown(T arr[], int n, int k){
    T e = arr[k];
    while(2*k+1 <= n){
        int j = 2*k+1; // 在此循环中，data[k]和data[j]交换位置
        if(j+1 < n && arr[j+1] > arr[j])
            j += 1;

        if(arr[k] >= arr[j])
            break;

        // swap(arr[k], arr[j]);
        arr[k] = arr[j];
        k = j;
    }
    arr[k] = e;
}

template<typename T>
void heapSort(T arr[], int n){
    // 索引开始0开始
    // 先进行heapify过程
    for(int i= (n-1)/2; i>=0; i--)
        __shiftDown(arr, n, i);

    for(int i=n-1; i>0; i--){
        swap(arr[0], arr[i]);
        __shiftDown(arr, i, 0);
    }

}




template<typename T>
void heapSortIndexHeap(T arr[], int n){
    IndexHeap<T> indexHeap = IndexHeap<T>(n);
    for(int i=0; i<n; i++)
        indexHeap.insert(i, arr[i]);
    assert(indexHeap.testIndexes());

    for(int i=n-1; i>=0; i--)
        arr[i] = indexHeap.extractMax();
}


int main(){

    int n = 10000000;

    int* arr = SortTestHelper::generateRandomArray(n, 0, n);
    SortTestHelper::testSort("Heap Sort Using Index-Max-Heap", heapSortIndexHeap, arr, n);
    delete[] arr;

    return 0;
}