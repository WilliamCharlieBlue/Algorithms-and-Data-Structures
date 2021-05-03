#ifndef SPARSE_GRAPH_H
#define SPARSE_GRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 稀疏图 - 邻接表
class SparseGraph{

private:
    int n, m;
    bool directed;
    // 二维矩阵 向量套向量的int
    vector<vector<int>> g;

public:
    SparseGraph(int n, bool directed){
        this->n = n;
        this->m = m;
        this->directed = directed;
        for(int i=0; i<n; i++)
            // 一开始没有任何节点是相连的，是一个空
            g.push_back(vector<int>());
    }

    ~SparseGraph(){

    }

    int V(){return n;}
    int E(){return m;}

    void addEdge(int v, int w){
        assert(v>=0 && v<n);
        assert(w>=0 && w<n);

        g[v].push_back(w);
        // 如果是无向图，对称一致
        // if(!directed) // 无法解决自环边
        if(v!= w && !directed)
            g[w].push_back(v);

        m++;
    }

    // 最差的情况下是O(n)级别的
    bool hasEdge(int v, int w){
        assert(v>=0 && v<n);
        assert(w>=0 && w<n);

        for(int i=0; i<g[v].size(); i++)
            if(g[v][i] == w)
                return true;
        return false;
    }


};

#endif
