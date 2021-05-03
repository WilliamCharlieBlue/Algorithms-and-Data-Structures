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

    void show(){
        for(int i=0; i<n; i++){
            cout<<"vertex "<<i<<":\t";
            for(int j=0; j<g[i].size(); j++)
                cout<<g[i][j]<<"\t";
            cout<<endl;
        }
    }

    class adjIterator{
    private:
        SparseGraph &G;
        int v;
        int index;
    public:
        // 迭代哪张图，迭代图中哪个顶点相邻的边
        // graph是一个地址，用初始化列表的形式传入
        adjIterator(SparseGraph &graph, int v): G(graph){
            this->v = v;
            this->index = 0;
        }

        int begin(){
            // 用户可能多次调用begin，最好在开始是都重置一下index
            index = 0;
            // 如果节点v有边的话，返回第0个元素
            if(G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        int next(){
            index++;
            // 如果不越界，返回
            if(index < G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        bool end(){
            // 如果index越界了，说明迭代完成了
            return index >= G.g[v].size();
        }
    };

};

#endif
