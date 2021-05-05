#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <iostream>
#include <vector>
#include <stack>
#include "Edge.h"
#include "IndexMinHeap.h"

using namespace std;

template <typename Graph, typename Weight>
class BellmanFord{

private:
    Graph &G;
    int s;

    Weight *distTo; // distTo[i]存储从起始点s到i的最短路径长度
//    bool *marked; // 标记数组, 在算法运行过程中标记节点i是否被访问
    vector<Edge<Weight>*> from; // from[i]记录最短路径中, 到达i点的边是哪一条, 恢复最短路径
    bool hasNegativeCycle; // 标记是否包含负权环

    // 在所有点都进行了松弛操作后；再对所有点进行一次松弛操作，如果还可以更新，说明有负权环。
    bool detectNegativeCycle(){
        for(int i=0; i<G.V(); i++){
            typename Graph::adjIterator adj(G, i);
            for(Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
                if(from[e->w()] && distTo[e->v()] + e->wt() < distTo[e->w()])
                    return true;
        }
        return false;
    }

public:
    BellmanFord(Graph &graph, int s): G(graph){
        assert(s>=0 && s<G.V());
        this->s = s;
        // distTo数组的元素类型还不知道，所以用模板Weight替代，例如double
        distTo = new Weight[G.V()];
//        marked = new bool[G.V()];
        for(int i=0; i<G.V(); i++){
//            distTo[i] = Weight(); // 模板函数的初始值，例如 int() 或者 double()
//            marked[i] = false;
            from.push_back(NULL);
        }

//        // Dijkstra
//        // 使用索引堆记录当前找到的到达每个顶点的最短距离
//        IndexMinHeap<Weight> ipq(G.V());
//        // distTo数组的元素类型还不知道，所以用模板Weight替代，例如double
//        distTo[s] = Weight();
//        // 起始点的边自连，并标记已访问，在shortestPath函数中用来终止while循环
//        from[s] = new Edge<Weight>(s, s, Weight());
//        marked[s] = true;
//        // 首先将顶点压入最小索引堆中
//        ipq.insert(s, distTo[s]);
//
//        // 索引堆循环
//        while (!ipq.isEmpty()){
//            int v = ipq.extractMinIndex();
//
//            // distTo[v]就是s到v的最短距离
//            marked[v] = true;
//            // 尝试进行松弛操作
//            typename Graph::adjIterator adj(G, v);
//            for(Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next()){
//                int w = e->other(v);
//                // 如果另一个点没被访问过，需要进行松弛操作
//                if(!marked[w]){
//                    // 对于还没有连接到w点的边，或者松弛的边的权值更小时，需要更新路径
//                    if(from[w] == NULL || distTo[v] + e->wt() < distTo[w]){
//                        distTo[w] = distTo[v] + e->wt();
//                        from[w] = e;
//                        // 一旦有路径更新，需要维护一下最小索引堆
//                        if(ipq.contain(w))
//                            ipq.change(w, distTo[w]);
//                        else
//                            ipq.insert(w, distTo[w]);
//                    }
//                }
//            }
//        }

        // Bellman-Ford  设置distTo[s] = 0, 并且让from[s]不为NULL, 表示初始s节点可达且距离为0
        distTo[s] = Weight();
        from[s] = new Edge<Weight>(s, s, Weight()); // 这里我们from[s]的内容是new出来的, 注意要在析构函数里delete掉
        // 对所有的点进行松弛操作
        for(int pass=1; pass<G.V(); pass++){
            // 每个点都要进行v-1次松弛操作
            for(int i=0; i<G.V(); i++){
                typename Graph::adjIterator adj(G, i);
                for(Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next()){
                    // 如果对面的点没有到达过，或者到达过却有更短的路径时，需要更新
                    if(!from[e->w()] || distTo[e->v()] + e->wt() < distTo[e->w()])
                        distTo[e->w()] = distTo[e->v()] + e->wt();
                        from[e->w()] = e;
                }
            }
        }

        // 最后还要判断有没有负权环，其实是对所有点再做一轮松弛操作
        // 如果没有负权环，再做松弛时不会有更新；而如果出现了要更新的情况，说明有负权环
        hasNegativeCycle = detectNegativeCycle();


    }

    ~BellmanFord(){
        delete []distTo;
//        delete []marked;
        delete from[s];
    }

    // 是否包含负权环
    bool negativeCycle(){
        return hasNegativeCycle;
    }

    // 从顶点到w的最短路径
    Weight shortestPathTo(int w){
        assert(w>=0 && w<G.V());
        assert(!hasNegativeCycle);
        return distTo[w];
    }


    // 从顶点到w是否有路径
    bool hasPathTo(int w){
        assert(w>=0 && w<G.V());
//        return marked[w];
        return from[w] != NULL;
    }

    void shortestPath(int w, vector<Edge<Weight>> &vec){
        assert(w>=0 && w<G.V());
        assert(!hasNegativeCycle);
        // 倒序将最短路径的压入栈中 9->0
        stack<Edge<Weight>*> s;
        Edge<Weight> *e = from[w];
        while(e->v() != e->w()){
            s.push(e);
            e = from[e->v()];
        }
//        s.push(e);

        // 再正序地压入向量中 0->9
        while(!s.empty()){
            e = s.top();
            vec.push_back(*e);
            s.pop();
        }
    }

    void showPath(int w){
        assert(w >= 0 && w < G.V());
        assert(!hasNegativeCycle);

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