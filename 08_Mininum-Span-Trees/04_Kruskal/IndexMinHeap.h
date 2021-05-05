#ifndef INDEX_MIN_HEAP_H
#define INDEX_MIN_HEAP_H

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

// 最小索引堆
template<typename Item>
class IndexMinHeap{

private:
    Item *data;
    int *indexes;
    int *reverse;

    int count;
    int capacity;

    // 索引堆中, 自下而上, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
    void shiftUp(int k){
        while(k>1 && data[indexes[k/2]] > data[indexes[k]]){
            swap(indexes[k/2], indexes[k]);
            reverse[indexes[k/2]] = k/2;
            reverse[indexes[k]] = k;
            k /= 2;
        }
    }

    // 索引堆中, 自上而下, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
    void shiftDown(int k){
        while(2*k <= count){
            // 默认使用左子节点
            int j = 2*k;
            // 如果右子节点比左子节点更小，换右子节点
            if(j+1 <= count && data[indexes[j]] > data[indexes[j+1]])
                j += 1;

            // 如果需要比较的节点不比子节点大，说明最小堆的性质已经维护好了
            if(data[indexes[k]] <= data[indexes[j]])
                break;

            // 否则仍需要交换
            swap(indexes[k], indexes[j]);
            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;
            k = j;
        }
    }


public:
    // 构造函数，构造一个空得索引堆，可容纳capacity个元素
    IndexMinHeap(int capacity){
        data = new Item[capacity+1];
        indexes = new int[capacity+1];
        reverse = new int[capacity+1];
        for(int i=0; i<capacity; i++){
            reverse[i] = 0;
        }
        count = 0;
        this->capacity = capacity;
    }

    ~IndexMinHeap(){
        delete []data;
        delete []indexes;
        delete []reverse;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    // 向最小索引堆中插入一个新的元素，新元素的索引为i，元素为item
    // 客户传入的i是从0开始索引的，而堆内部的是从1开始索引的
    void insert(int index, Item item){
        assert(count+1 <= capacity);
        assert(index+1 >= 1 && index+1 <= capacity);
        // 堆内部的索引是从1开始的
        index += 1;
        data[index] = item;
        // 在索引堆的最末端插入这个元素
        indexes[count+1] = index;
        // 同时更具indexes和reverse的性质维护reverse
        reverse[index] = count+1;
        count++;
        shiftUp(count);
    }

    // 从最小索引堆中取出堆顶元素，即取出索引堆中所存储的最小数据
    Item extractMin(){
        assert(count > 0);
        // 取出数据
        Item ret = data[indexes[1]];
        // 交换索引
        swap(indexes[1], indexes[count]);
        // 即把最末位的值删除，而reverse里只需要赋值为0即可
        reverse[indexes[count]] = 0;
        count--;
        // 以防只有一个元素的时候出bug
        if(count){
            reverse[indexes[1]] = 1;
            shiftDown(1);
        }
        return ret;
    }

    // 从最小索引堆中取出堆顶元素的索引
    int extractMinIndex(){
        assert(count > 0);
        // 客户传入的i是从0开始索引的，而堆内部的是从1开始索引的
        int ret = indexes[1] - 1;
        swap(indexes[1], indexes[count]);
        // 即把最末位的值删除，而reverse里只需要赋值为0即可
        reverse[indexes[count]] = 0;
        count--;
        // 以防只有一个元素的时候出bug
        if(count){
            reverse[indexes[1]] = 1;
            shiftDown(1);
        }
        return ret;

    }


    Item getMin(){
        assert(count > 0);
        return data[indexes[1]];
    }

    // 客户传入的i是从0开始索引的，而堆内部的是从1开始索引的
    int getMinIndex(){
        assert(count > 0);
        return indexes[1]-1;
    }

    // reverse里维护了，indexes是否有效
    bool contain(int index){
        return reverse[index+1] != 0;
    }

    // 获取用户索引为i的元素
    Item getItem(int index){
        assert(contain(index));
        return data[index+1];
    }

    // 将最小索引堆索引为i的元素修改为newItem
    void change(int index, Item newItem){
        assert(contain(index));
        index += 1;
        data[index] = newItem;

        // 利用reverse数组，直接找到indexes[j] = index; j = reverse[index].
        shiftUp(reverse[index]);
        shiftDown(reverse[index]);
    }
};

#endif