#ifndef DENSE_GRAPH_H
#define DENSE_GRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 稠密图 - 邻接矩阵
class DenseGraph{

private:
    int n, m;
    bool directed;
    // 二维矩阵 向量套向量的bool
    vector<vector<bool>> g;

public:
    DenseGraph(int n, bool directed){
        this->n = n;
        this->m = 0;
        this->directed = directed;
        for(int i=0; i<n; i++)
            // 将矩阵中所有的值都复制为false
            g.push_back(vector<bool>(n, false));
    }

    ~DenseGraph(){

    }

    int V(){return n;}
    int E(){return m;}

    void addEdge(int v, int w){
        assert(v>=0 && v<n);
        assert(w>=0 && w<n);
        // 如果v和w之间已经有边了，直接跳过
        if(hasEdge(v, w))
            return;

        g[v][w] = true;
        // 如果是无向图，对称一致
        if(!directed)
            g[w][v] = true;

        m++;
    }

    // O(1)的时间复杂度
    bool hasEdge(int v, int w){
        assert(v>=0 && v<n);
        assert(w>=0 && w<n);
        return g[v][w];
    }

    class adjIterator{
    private:
        DenseGraph &G;
        int v;
        int index;
    public:
        adjIterator(DenseGraph &graph, int v): G(graph){
            this->v = v;
            this->index = -1;
        }

        int begin(){
            // 调用时重置index
            index = -1;
            // 第一个为true的才是第一条边，而不是index=0
            return next();
        }

        int next(){
            // G.V()为顶点的个数
            for(index += 1; index < G.V(); index++)
                // 如果边存在，把index返回，即返回w
                if(G.g[v][index])
                    return index;
            return -1;
        }

        int end(){
            return index >= G.V();
        }
    };
};

#endif