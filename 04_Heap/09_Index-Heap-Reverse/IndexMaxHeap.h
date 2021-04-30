#ifndef INDEX_MAX_HEAP_H
#define INDEX_MAX_HEAP_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;


template<typename Item>
class IndexMaxHeap {
private:
    Item *data;
    int *indexes;
    int *reverse;
    int count;
    int capacity;

    // shiftUp中使用赋值来进行交换
    void shiftUp(int k) {
        Item e = data[indexes[k]];
        int srck = indexes[k];
        while (k > 1 && data[indexes[k / 2]] < e) {
            //swap(indexes[k/2], indexes[k]);
            indexes[k] = indexes[k / 2];
            reverse[indexes[k / 2]] = k / 2;
            reverse[indexes[k]] = k;
            k /= 2;
        }
        indexes[k] = srck;
        reverse[indexes[k]] = k;
    }

    // shiftDown中使用赋值来进行交换
    void shiftDown(int k) {
        Item e = data[indexes[k]];
        int srck = indexes[k];
        // 有右子节点的话，已经有左子节点
        while (2 * k <= count) {
            int j = 2 * k; // 在此轮循环中，data[k]和data[j]交换位置
            if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]])  // 如果有右子节点，而且比左子节点大，就那关注右子节点
                j += 1;

            if (e > data[indexes[j]]) // 父节点比子节点大，则不需要交换
                break;

            indexes[k] = indexes[j];
            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;
            k = j;
        }
        indexes[k] = srck;
        reverse[indexes[k]] = k;
    }

public:
    IndexMaxHeap(int capacity) {
        // 索引0不适用，从索引1开始
        data = new Item[capacity + 1];
        indexes = new Item[capacity + 1];
        reverse = new Item[capacity + 1];
        // reverse初始化为0，这里表示还均不存在
        for (int i = 0; i <= capacity; i++)
            reverse[i] = 0;
        count = 0;
        this->capacity = capacity;
    }

    // 用于Heapify的构造函数
    IndexMaxHeap(Item arr[], int n) {
        data = new Item[n + 1];
        capacity = n;
        for (int i = 0; i < n; i++)
            data[i + 1] = arr[i];
        count = n;
        // 第一个非末端子节点为  堆内元素数量/2
        // 从第一个非末端子节点开始，进行shiftdown，使得整个堆符合最大堆性质
        for (int i = count / 2; i >= 1; i--)
            shiftDown(i);
    }

    ~IndexMaxHeap() {
        delete[]data;
        delete[]indexes;
        delete[]reverse;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    // 传入的i对用户而言，是从0索引的
    void insert(int i, Item item) {

        assert(count + 1 <= capacity);
        assert(i + 1 >= 1 && i + 1 <= capacity);
        // 内部转化为从1开始索引
        i += 1;
        //
        data[i] = item;
        indexes[count + 1] = i;
        // indexes 和 reverse的性质
        reverse[i] = count + 1;

        count++;
        shiftUp(count);
    }

    Item extractMax() {
        assert(count > 0);
        Item ret = data[indexes[1]];
        swap(indexes[1], indexes[count]);
        // 即把最末位的值删除，而reverse里只需要赋值为0即可
        reverse[indexes[count]] = 0;
        count--;
        // 在从堆顶往下开始shiftDown
        if (count) {
            reverse[indexes[1]] = 1;
            shiftDown(1);
        }

        return ret;
    }

    int extractMaxIndex() {
        assert(count > 0);
        // 我们目前的索引堆是从1开始的；而用户期望的返回值是从0开始
        int ret = indexes[1] - 1;
        swap(indexes[1], indexes[count]);
        // 即把最末位的值删除，而reverse里只需要赋值为0即可
        reverse[indexes[count]] = 0;
        count--;
        // 在从堆顶往下开始shiftDown
        if (count) {
            reverse[indexes[1]] = 1;
            shiftDown(1);
        }
        return ret;
    }

    bool contain(int i) {
        assert(i + 1 >= 1 && i + 1 <= capacity);
        // 如果所选的位置的reverse值不是0，即存在相应的index值的话，说明是包含的
        return reverse[i + 1] != 0;
    }

    // 通过索引来获取数据
    Item getItem(int i) {
        assert(contain(i));
        return data[i + 1];
    }

    void change(int i, Item newItem) {
        assert(contain(i));
        i += 1;
        data[i] = newItem;

        // 找到indexes[j] = i, j表示data[i]在堆中的位置
        // 之后shiftUp(j), 再shifDown(j)

        // 方法一：遍历堆，遍历O(n)，shiftUp/shiftDown最差为O(logn),整体最差可能达到O(n^2)
        for (int j = 1; j <= count; j++)
            if (indexes[j] == i) {
                shiftUp(j);
                shiftDown(j);
                return;
            }

        // 方法二：利用reverse数组，直接找到indexes[j] = i; 查找j为O(1),shiftUp/shiftDown最差为O(logn)，整体最差可能达到O(logn)
        int j = reverse[i];
        shiftUp(j);
        shiftDown(j);
    }

public:
    // 测试索引堆中的索引数组index
    // 注意:这个测试在向堆中插入元素以后, 不进行extract操作有效
    bool testIndexes() {
        int *copyIndexes = new int[count + 1];
        for (int i = 0; i <= count; i++)
            copyIndexes[i] = indexes[i];

        copyIndexes[0] = 0;
        sort(copyIndexes, copyIndexes + count + 1);
        // 在对索引堆中的索引进行排序后, 应该正好是1...count这count个索引
        bool res = true;
        for (int i = 1; i <= count; i++)
            if (copyIndexes[i - 1] + 1 != copyIndexes[i]) {
                res = false;
                break;
            }
        delete[]copyIndexes;
        if (!res) {
            cout << "Error!" << endl;
            return false;
        }
        return true;
    }
};

#endif