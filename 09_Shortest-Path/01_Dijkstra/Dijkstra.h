#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <vector>
#include <stack>
#include "Edge.h"
#include "IndexMinHeap.h"

using namespace std;

template <typename Graph, typename Weight>
class Dijkstra{

private:
    Graph &G;
    int s;

    Weight *distTo; // distTo[i]存储从起始点s到i的最短路径长度
    bool *marked; // 标记数组, 在算法运行过程中标记节点i是否被访问
    vector<Edge<Weight>*> from; // from[i]记录最短路径中, 到达i点的边是哪一条, 恢复最短路径

public:
    Dijkstra(Graph &graph, int s): G(graph){
        assert(s>=0 && s<G.V());
        this->s = s;
        // distTo数组的元素类型还不知道，所以用模板Weight替代，例如double
        distTo = new Weight[G.V()];
        marked = new bool[G.V()];
        for(int i=0; i<G.V(); i++){
            distTo[i] = Weight(); // 模板函数的初始值，例如 int() 或者 double()
            marked[i] = false;
            from.push_back(NULL);
        }

        // 使用索引堆记录当前找到的到达每个顶点的最短距离
        IndexMinHeap<Weight> ipq(G.V());
        // Dijkstra
        // distTo数组的元素类型还不知道，所以用模板Weight替代，例如double
        distTo[s] = Weight();
        // 起始点的边自连，并标记已访问，在shortestPath函数中用来终止while循环
        from[s] = new Edge<Weight>(s, s, Weight());
        marked[s] = true;
        // 首先将顶点压入最小索引堆中
        ipq.insert(s, distTo[s]);

        // 索引堆循环
        while (!ipq.isEmpty()){
            int v = ipq.extractMinIndex();

            // distTo[v]就是s到v的最短距离
            marked[v] = true;
            // 尝试进行松弛操作
            typename Graph::adjIterator adj(G, v);
            for(Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next()){
                int w = e->other(v);
                // 如果另一个点没被访问过，需要进行松弛操作
                if(!marked[w]){
                    // 对于还没有连接到w点的边，或者松弛的边的权值更小时，需要更新路径
                    if(from[w] == NULL || distTo[v] + e->wt() < distTo[w]){
                        distTo[w] = distTo[v] + e->wt();
                        from[w] = e;
                        // 一旦有路径更新，需要维护一下最小索引堆
                        if(ipq.contain(w))
                            ipq.change(w, distTo[w]);
                        else
                            ipq.insert(w, distTo[w]);
                    }
                }
            }
        }


    }

    ~Dijkstra(){
        delete []distTo;
        delete []marked;
    }

    // 从顶点到w的最短路径
    Weight shortestPathTo(int w){
        return distTo[w];
    }

    // 从顶点到w是否有路径
    bool hasPath(int w){
        return marked[w];
    }


    void shortestPath(int w, vector<Edge<Weight>> &vec){
        // 倒序将最短路径的压入栈中 9->0
        stack<Edge<Weight>*> s;
        Edge<Weight> *e = from[w];
        while(e->v() != e->w()){
            s.push(e);
            e = from[e->v()];
        }
        // 再正序地压入向量中 0->9
        while(!s.empty()){
            e = s.top();
            vec.push_back(*e);
            s.pop();
        }
    }

    void showPath(int w){
        assert(w >= 0 && w < G.V());
        vector<Edge<Weight>> vec;
        shortestPath(w, vec);
        for(int i=0; i<vec.size(); i++){
            cout<<vec[i].v()<<" -> ";
            if(i == vec.size()-1)
                cout<<vec[i].w()<<endl;
        }
    }

};



#endif