#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

template <typename Graph>
class ShortestPath{

private:
    Graph &G;
    int s;
    bool *visited;
    int *from;
    int *ord; // 从s到每一个节点的最短路径

    void dfs(int v){
        visited[v] = true;
        // 声明adjIterator是一种类型，而不是成员变量
        typename Graph::adjIterator adj(G, v);
        for(int i = adj.begin(); !adj.end(); i = adj.next()){
            // 如果没有遍历过，递归去遍历
            if(!visited[i]){
                from[i] = v;
                dfs(i);
                // 如果遍历过则是跳过
            }
        }
    }

public:
    ShortestPath(Graph &graph, int s): G(graph){
        // 算法初始化
        assert(s >= 0 && s < G.V());

        this->s = s;
        visited = new bool[G.V()];
        from = new int[G.V()];
        ord = new int[G.V()];
        for(int i=0; i<G.V(); i++){
            visited[i] = false;
            from[i] = -1;
            ord[i] = -1;
        }

//        // 寻路算法
//        // 从s开始，进行一次深度优先遍历
//        dfs(s);

        // 无向图最短路径算法 BFS
        queue<int> q;
        // 先处理队首的节点
        q.push(s);
        visited[s] = true;
        ord[s] = 0;
        while(!q.empty()){
            int v = q.front();
            q.pop();

            typename Graph::adjIterator adj(G, v);
            for(int i=adj.begin(); !adj.end(); i = adj.next()){
                if(!visited[i]){
                    q.push(i);
                    visited[i] = true;
                    from[i] = v;
                    ord[i] = ord[v] + 1;
                }
            }
        }

    }
    ~ShortestPath(){
        delete []visited;
        delete []from;
        delete []ord;
    }

    bool hasPath(int w){
        assert(w>=0 && w < G.V());
        // 有访问过说明，从s开始访问到了w，说明是有路径
        return visited[w];
    }

    void path(int w, vector<int> &vec){
        // 由于需要倒着推,所有使用stack
        stack<int> s;
        int p = w;
        // from[]的初始值是-1; 从w开始一步一步倒着压入栈中
        while(p != -1){
            s.push(p);
            p = from[p];
        }
        // 把路径从stack取出来，放入vector中
        vec.clear();
        while(!s.empty()){
            // 栈顶取出，压入向量中
            vec.push_back(s.top());
            s.pop();
        }
    }

    void showPath(int w){
        vector<int> vec;
        path(w, vec);
        for(int i=0; i<vec.size(); i++){
            cout << vec[i];
            if(i == vec.size()-1)
                cout << endl;
            else
                cout << "->";
        }
    }

    // 从s到w的最短路径
    int length(int w){
        assert(w>=0 && w<G.V());
        return ord[w];
    }
};

#endif