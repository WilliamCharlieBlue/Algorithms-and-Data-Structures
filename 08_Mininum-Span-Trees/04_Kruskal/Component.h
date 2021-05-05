#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <cassert>

using namespace std;

template <typename Graph>
class Component{
private:
    Graph &G;
    bool *visited;
    int *id; // 记录是哪个连通分量，相连的节点id相同，不相连的节点id不同
    int ccount;

    void dfs(int v){
        visited[v] = true;
        // id初始值是-1；而ccount初始值为0；id将有0开始递增
        id[v] = ccount;
        // 声明adjIterator是一种类型，而不是成员变量
        typename Graph::adjIterator adj(G, v);
        for(int i = adj.begin(); !adj.end(); i = adj.next()){
            // 如果没有遍历过，递归去遍历
            if(!visited[i])
                dfs(i);
            // 如果遍历过则是跳过
        }
    }

public:
    Component(Graph &graph): G(graph){
        visited = new bool[G.V()];
        id = new int[G.V()];
        ccount = 0;
        for(int i=0; i<G.V(); i++){
            visited[i] = false;
            id[i] = -1;
        }

        for(int i=0; i<G.V(); i++)
            if(!visited[i]){
                // 如果之前没访问过，说明在另一个连通分量中
                dfs(i);
                ccount++;
            }
    }

    ~Component(){
        delete []visited;
        delete []id;
    }

    int count(){
        return ccount;
    }

    bool isConnected(int v, int w){
        assert(v>=0 && v<G.V());
        assert(w>=0 && w<G.V());
        return id[v] == id[w];
    }
};


#endif