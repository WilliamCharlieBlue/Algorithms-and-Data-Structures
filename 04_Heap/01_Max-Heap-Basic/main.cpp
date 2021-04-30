#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

template<typename Item>
class MaxHeap{
public:
    MaxHeap(int capacity){
        // 索引0不适用，从索引1开始
        data = new Item[capacity + 1];
        count = 0;
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

private:
    Item* data;
    int count;
};


int main(void){

    MaxHeap<int> maxheap = MaxHeap<int>(100);
    cout << maxheap.size() << endl;
    cout << maxheap.isEmpty() << endl;

    return 0;
}