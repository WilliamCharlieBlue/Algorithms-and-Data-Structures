#ifndef PRIM_MST_H
#define PRIM_MST_H

#include <vector>
#include "Edge.h"
//#include "MinHeap.h"
#include "IndexMinHeap.h"

using namespace std;

template<typename Graph, typename Weight>
class PrimMST{

private:
    Graph &G;
    IndexMinHeap<Weight> ipq; // 使用最小s索引堆构建一个优先队列 priority queue
    vector<Edge<Weight>*> edgeTo; // 指向最小权值的横切边的指针
    bool *marked; // 标记节点已加入最小生成树中
    vector<Edge<Weight>> mst; // 存放最终的最小生成树
    Weight mstWeight; // 存放最终的最小生成树的总权重

    void visit_Lazy_Prim(int v){
        assert(!marked[v]);
        marked[v] = true;

        typename Graph::adjIterator adj(G, v);
        for(Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()){
            // 遍历这个节点的每一条边，如果另一端还没被访问到，说明是横切边
            // 将所有横切边压入堆中
            if(!marked[e->other(v)])
                ipq.insert(*e);
        }
    }

    void visit(int v){
        assert(!marked[v]);
        marked[v] = true;

        typename Graph::adjIterator adj(G, v);
        for(Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()){
            int w = e->other(v);
            // 关心的是w没被标记的情况
            if(!marked[w]){
               if(!edgeTo[w]){
                   // 如果之前没有找到这个点的横切边，需要直接压入堆中
                   ipq.insert(w, e->wt());
                   edgeTo[w] = e;
               }
               else if(e->wt() < edgeTo[w]->wt()){
                   // 如果新的横切边比之前的横切边的权值更小，则需要把之前的覆盖
                   ipq.change(w, e->wt());
                   edgeTo[w] = e;
               }
            }
        }
    }

public:
    // 把图的边数传递给最小堆
    PrimMST(Graph &graph): G(graph), ipq(IndexMinHeap<Weight>(graph.V())) {
        assert(graph.E() >= 1);
        marked = new bool[G.V()];
        for (int i = 0; i < G.V(); i++) {
            marked[i] = false;
            // 所有最小横切边的指针全设置为空
            edgeTo.push_back(NULL);
        }

        mst.clear();

        // Prim
        visit(0);
        while(!ipq.isEmpty()){
            int v = ipq.extractMinIndex();
            assert(edgeTo[v]);
            // 将到这个点的权值压入最小生产树中
            mst.push_back(*edgeTo[v]);
            visit(v);
        }

        // 最后将最小生成树的权值加和
        mstWeight = mst[0].wt();
        // 注意mst[0]已经赋值给了mstWeight，所以int i从1开始
        for(int i=1; i<mst.size(); i++)
            mstWeight += mst[i].wt();
    }

//        // Lazy Prim
//        // 从0这个节点开始切分
//        visit(0);
//        // 扩展生成树的阵容
//        while(!ipq.isEmpty()){
//            Edge<Weight> e = ipq.extractMin();
//            // 一条边的两个点是属于统一阵容，则不是横切边，需要弃掉，继续下个循环
//            if(marked[e.v()] == marked[e.w()])
//                continue;
//            // 分属不同阵容,则这个权重值e可以压入 mst中
//            mst.push_back(e);
//            // 确定这条边未被标记的点，用visit把这个未标记的点标记，且把临边压入堆中。
//            if(!marked[e.v()])
//                visit(e.v());
//            else
//                visit(e.w());
//        }
//
//        // 最后将最小生成树的权值加和
//        mstWeight = mst[0].wt();
//        // 注意mst[0]已经赋值给了mstWeight，所以int i从1开始
//        for(int i=1; i<mst.size(); i++){
//            mstWeight += mst[i].wt();
//        }
//    }

    ~PrimMST(){
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