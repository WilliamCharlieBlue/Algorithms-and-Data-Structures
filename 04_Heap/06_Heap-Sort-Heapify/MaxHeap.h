#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;


template<typename Item>
class MaxHeap{
private:
    Item* data;
    int count;
    int capacity;

//   // shiftUp中使用swap来进行交换
//    void shiftUp(int k) {
//        while (k > 1 && data[k/2] < data[k]) {
//            swap(data[k/2], data[k]);
//            k /= 2;
//        }
//    }
    // shiftUp中使用赋值来进行交换
    void shiftUp(int k) {
        Item e = data[k];
        while (k > 1 && data[k/2] < e) {
            //swap(data[k/2], data[k]);
            data[k] = data[k/2];
            k /= 2;
        }
        data[k] = e;
    }

//    // shiftDown中使用swap来进行交换
//    void shiftDown(int k){
//        // 有右子节点的话，已经有左子节点
//        while(2*k <= count){
//            int j = 2*k; // 在此轮循环中，data[k]和data[j]交换位置
//            if(j+1 <= count && data[j+1] > data[j])  // 如果有右子节点，而且比左子节点大，就那关注右子节点
//                j += 1;
//
//            if(data[k] > data[j]) // 父节点比子节点大，则不需要交换
//                break;
//
//            swap(data[k], data[j]);
//            k = j;
//        }
//    }
    // shiftDown中使用赋值来进行交换
    void shiftDown(int k){
        Item e = data[k];
        // 有右子节点的话，已经有左子节点
        while(2*k <= count){
            int j = 2*k; // 在此轮循环中，data[k]和data[j]交换位置
            if(j+1 <= count && data[j+1] > data[j])  // 如果有右子节点，而且比左子节点大，就那关注右子节点
                j += 1;

            if(e > data[j]) // 父节点比子节点大，则不需要交换
                break;

            //swap(data[k], data[j]);
            data[k] = data[j];
            k = j;
        }
        data[k] = e;
    }

public:
    MaxHeap(int capacity){
        // 索引0不适用，从索引1开始
        data = new Item[capacity + 1];
        count = 0;
        this->capacity = capacity;
    }
    // 用于Heapify的构造函数
    MaxHeap(Item arr[], int n){
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

    ~MaxHeap(){
        delete []data;
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        return count==0;
    }

    void insert(Item item){

        assert(count+1 <= capacity);
        data[count+1] = item;
        count++;
        shiftUp(count);
    }

    Item extractMax(){
        assert(count > 0);
        Item ret = data[1];
        swap(data[1], data[count]);
        count --;
        shiftDown(1);
        return ret;
    }

public:
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

#endif