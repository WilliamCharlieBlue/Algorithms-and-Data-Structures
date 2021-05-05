#ifndef LAZY_PRIM_MST_H
#define LAZY_PRIM_MST_H

#include <vector>
#include "Edge.h"
#include "MinHeap.h"

using namespace std;

template<typename Graph, typename Weight>
class LazyPrimMST{

private:
    Graph &G;
    MinHeap<Edge<Weight>> pq; // 使用最小堆构建一个优先队列 priority queue
    bool *marked; // 标记节点已加入最小生成树中
    vector<Edge<Weight>> mst; // 存放最终的最小生成树
    Weight mstWeight; // 存放最终的最小生成树的总权重

    void visit(int v){
        assert(!marked[v]);
        marked[v] = true;

        typename Graph::adjIterator adj(G, v);
        for(Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()){
            // 遍历这个节点的每一条边，如果另一端还没被访问到，说明是横切边
            // 将所有横切边压入堆中
            if(!marked[e->other(v)])
                pq.insert(*e);
        }
    }

public:
    // 把图的边数传递给最小堆
    LazyPrimMST(Graph &graph): G(graph), pq(MinHeap<Edge<Weight>>(graph.E())){
        marked = new bool[G.V()];
        for(int i=0; i<G.V(); i++)
            marked[i] = false;

        mst.clear();

        // Lazy Prim
        // 从0这个节点开始切分
        visit(0);
        // 扩展生成树的阵容
        while(!pq.isEmpty()){
            Edge<Weight> e = pq.extractMin();
            // 一条边的两个点是属于统一阵容，则不是横切边，需要弃掉，继续下个循环
            if(marked[e.v()] == marked[e.w()])
                continue;
            // 分属不同阵容,则这个权重值e可以压入 mst中
            mst.push_back(e);
            // 确定这条边未被标记的点，用visit把这个未标记的点标记，且把临边压入堆中。
            if(!marked[e.v()])
                visit(e.v());
            else
                visit(e.w());
        }

        // 最后将最小生成树的权值加和
        mstWeight = mst[0].wt();
        // 注意mst[0]已经赋值给了mstWeight，所以int i从1开始
        for(int i=1; i<mst.size(); i++){
            mstWeight += mst[i].wt();
        }
    }

    ~LazyPrimMST(){
        delete []marked;
    }

    vector<Edge<Weight>> mstEdges(){
        return mst;
    }

    Weight result(){
        return mstWeight;
    }

};

#endif