#ifndef UNION_FIND_3_H
#define UNION_FIND_3_H

#include <iostream>
#include <cassert>
using namespace std;

namespace UF3 {

    class UnionFind {

    private:
        int *parent;
        int *sz; // sz[i]表示以i为根地集合中元素个数
        int count;  // 数据个数

    public:
        // 构造函数
        UnionFind(int count) {
            parent = new int[count];
            sz = new int[count];
            this->count = count;
            // 初始化, 每一个id[i]指向自己, 没有合并的元素
            for (int i = 0; i < count; i++){
                parent[i] = i;
                sz[i] = 1;
            }
        }
        // 析构函数
        ~UnionFind() {
            delete []parent;
            delete []sz;
        }
        // 查找过程, 查找元素p所对应的集合编号
        int find(int p) {
            assert(p >= 0 && p < count);
            while(p != parent[p])
                // 向上找到自己的根节点
                p = parent[p];
            return p;
        }
        // 查看元素p和元素q是否所属一个集合
        // O(1)复杂度
        bool isConnected(int p, int q) {
            return find(p) == find(q);
        }

        // 合并元素p和元素q所属的集合
        // O(n) 复杂度
        void unionElements(int p, int q) {
            int pRoot = find(p);
            int qRoot = find(q);
            if (pRoot == qRoot)
                return;

            // 根据两个元素所在树的元素个数不同判断合并方向
            // 将元素个数少的集合合并到元素个数多的集合上
            if(sz[pRoot] < sz[qRoot]){
                parent[pRoot] = qRoot;
                sz[qRoot] += sz[pRoot];
            }
            else{
                parent[qRoot] = pRoot;
                sz[pRoot] += sz[qRoot];
            }
        }
    };
}

#endif