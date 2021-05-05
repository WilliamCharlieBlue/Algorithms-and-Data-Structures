#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <iostream>
#include <vector>
#include "MinHeap.h"
#include "UnionFind.h"
#include "Edge.h"

using namespace std;

template <typename Graph, typename Weight>
class KruskalMST{

private:
    vector<Edge<Weight>> mst;
    Weight mstWeight;

public:
    // 没有辅助函数，类中不用存一份引用
    KruskalMST(Graph &graph){
        // 选用堆排序的方法，而且最小堆可以将最小的边一个个拿出来
        // pq的空间是边数的大小
        MinHeap<Edge<Weight>> pq(graph.E());
        for(int i=0; i<graph.V(); i++){
            typename Graph::adjIterator adj(graph,i);
            for(Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()){
                // 最小生成树是针对无向图来做的，对于双向的边只取一条就可以了
                // 例如 1和2 ,只放1->2；不放1<-2
                if(e->v() < e->w())
                    pq.insert(*e);
            }
        }

        // 使用并查集来判断是否成环
        // uf的空间是顶点数的大小
        UnionFind uf(graph.V());
        // 如果最小堆不为空 或者 最小生成树的边数已经等n-1条边了(说明已经生成完成了)
        while(!pq.isEmpty() && mst.size() < graph.V()-1){
            // 从最小堆中依次取出最小权重的边
            Edge<Weight> e = pq.extractMin();
            // 如果这条边的两个点已经是一个集合里了，跳过，去看下一条边
            if(uf.isConnected(e.v(), e.w()))
                continue;
            // 否则，这条边是横切边，需要压入最小生成树中，然后把两个顶点放入一个集合中
            mst.push_back(e);
            uf.unionElements(e.v(), e.w());
        }
    }

    ~KruskalMST(){

    }

    vector<Edge<Weight>> mstEdges(){
        return mst;
    }

    Weight result(){
        return mstWeight;
    }
};
#endif