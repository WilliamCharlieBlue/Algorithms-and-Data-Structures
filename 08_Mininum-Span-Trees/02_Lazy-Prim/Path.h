#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <stack>

using namespace std;

template <typename Graph>
class Path{
private:
    Graph &G;
    int s;
    bool* visited;
    int* from;

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
    Path(Graph &graph, int s): G(graph){
    // 算法初始化
    assert(s >= 0 && s < G.V());

    this->s = s;
    visited = new bool[G.V()];
    from = new int[G.V()];
    for(int i=0; i<G.V(); i++){
        visited[i] = false;
        from[i] = -1;
    }

    // 寻路算法
    // 从s开始，进行一次深度优先遍历
    dfs(s);

}
    ~Path(){
        delete []visited;
        delete []from;
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
};


#endif