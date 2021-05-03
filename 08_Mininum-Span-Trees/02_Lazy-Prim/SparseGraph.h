#ifndef SPARSE_GRAPH_H
#define SPARSE_GRAPH_H

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

// 稀疏图 - 邻接表
template <typename Weight>
class SparseGraph{

private:
    int n, m;
    bool directed;
    // 二维矩阵 向量套向量的int
    //vector<vector<int>> g;
    // 将矩阵中所有的指针赋值为NULL
    vector<vector<Edge<Weight> *>> g;

public:
    SparseGraph(int n, bool directed){
        this->n = n;
        this->m = m;
        this->directed = directed;
        for(int i=0; i<n; i++)
            // 一开始没有任何节点是相连的，是一个空
            g.push_back(vector<Edge<Weight> *>());
    }

    ~SparseGraph(){
        for(int i=0; i<n; i++)
            for(int j=0; j<g[i].size(); j++)
                delete g[i][j];
    }

    int V(){return n;}
    int E(){return m;}

    void addEdge(int v, int w, Weight weight){
        assert(v>=0 && v<n);
        assert(w>=0 && w<n);

        //g[v].push_back(w);
        g[v].push_back(new Edge<Weight>(v, w, weight));
        // 如果是无向图，对称一致
        // if(!directed) // 无法解决自环边
        if(v!= w && !directed)
            g[w].push_back(new Edge<Weight>(w, v, weight));

        m++;
    }

    // 最差的情况下是O(n)级别的
    bool hasEdge(int v, int w){
        assert(v>=0 && v<n);
        assert(w>=0 && w<n);

        for(int i=0; i<g[v].size(); i++)
            // 另一个点是否是w
            if(g[v][i]->other(v) == w)
                return true;
        return false;
    }

    void show(){
        for(int i=0; i<n; i++){
            cout<<"vertex "<<i<<":\t";
            for(int j=0; j<g[i].size(); j++)
                //cout<<g[i][j]<<"\t";
                cout<<"( to:"<<g[i][j]->w()<<",wt:"<<g[i][j]->wt()<<")\t";
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

        Edge<Weight> * begin(){
            // 用户可能多次调用begin，最好在开始是都重置一下index
            index = 0;
            // 如果节点v有边的话，返回第0个元素
            if(G.g[v].size())
                return G.g[v][index];
            return NULL;
        }

        Edge<Weight> * next(){
            index++;
            // 如果不越界，返回
            if(index < G.g[v].size())
                return G.g[v][index];
            return NULL;
        }

        bool end(){
            // 如果index越界了，说明迭代完成了
            return index >= G.g[v].size();
        }
    };

};

#endif
