#ifndef UNINON_FIND_H
#define UNINON_FIND_H

#include <iostream>
#include <cassert>

using namespace std;

// Quick Union + rank + path compression without Recursion
class UnionFind{
private:
    // rank[i]表示以i为根的集合所表示的树的层数
    // 在后续的代码中, 我们并不会维护rank的语意, 也就是rank的值在路径压缩的过程中, 有可能不在是树的层数值
    // 这也是我们的rank不叫height或者depth的原因, 他只是作为比较的一个标准
    int *rank;
    int *parent; // parent[i]表示第i个元素所指向的父节点
//    int *sz; // sz[i]表示以i为根的集合中元素个数
    int count;

public:
    UnionFind(int count){
        parent = new int[count];
        rank = new int[count];
        this->count = count;
        // 初始化, 每一个id[i]指向自己, 没有合并的元素
        for(int i=0; i<count; i++){
            parent[i] = i;
            rank[i] = 1;
//            sz[i] = 1;
        }
    }

    ~UnionFind(){
//        delete []sz;
        delete []rank;
        delete []parent;
    }

    int find(int p){
        assert(p >=0 && p < count);

        // path compression without Recursion 两步一跳
        while(p != parent[p]){
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;

//        // path compression with Recursion 完全递归，理论更优，但加上递归开销，实际效果并不好
//        if(p != parent[p])
//            // 利用递归将所有子节点都平行地指向根节点
//            parent[p] = find(parent[p]);
//        // 由于操作的是parent[p]，所以最终的根节点是parent[p]
//        return parent[p];
    }

    // 查看元素p和元素q是否所属一个集合
    // O(h)复杂度, h为树的高度
    bool isConnected(int p, int q){
        return find(p) == find(q);
    }

    // 合并元素p和元素q所属的集合
    // O(h)复杂度，h为数的高度
    void unionElememts(int p, int q){
        int pRoot = find(p);
        int qRoot = find(q);
        if(pRoot == qRoot)
            return;

//        // Optimize by Size
//        // 根据两个元素所在树的元素个数不同判断合并方向
//        // 将元素个数少的集合合并到元素个数多的集合上
//        if(sz[pRoot] < sz[qRoot]){
//            parent[pRoot] = qRoot;
//            sz[qRoot] += sz[pRoot];
//        }
//        else{
//            parent[qRoot] = pRoot;
//            sz[pRoot] += sz[qRoot];
//        }

        // Optimize by Rank
        // 将层数越少的集合合并到层数越多的集合上
        if(rank[pRoot] < rank[qRoot]){
            parent[pRoot] = qRoot;
        }
        else if(rank[pRoot] > rank[qRoot]){
            parent[qRoot] = pRoot;
        }
        else{
            // rank[pRoot] == rank[qRoot]
            parent[pRoot] = qRoot;
            rank[qRoot] += 1;  // 此时需要维护rank的值
        }

    }
};

#endif