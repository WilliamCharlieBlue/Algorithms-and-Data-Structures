#ifndef UNION_FIND_2_H
#define UNION_FIND_2_H

#include <iostream>
#include <cassert>
using namespace std;

namespace UF2 {

    class UnionFind {

    private:
        int *parent;
        int count;  // 数据个数

    public:
        // 构造函数
        UnionFind(int count) {
            parent = new int[count];
            this->count = count;
            // 初始化, 每一个id[i]指向自己, 没有合并的元素
            for (int i = 0; i < count; i++)
                parent[i] = i;
        }
        // 析构函数
        ~UnionFind() {
            delete []parent;
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
            // 如果根节点不一致，简单地把一个根节点接到另一个根节点上
            parent[pRoot] = qRoot;
        }
    };
}

#endif