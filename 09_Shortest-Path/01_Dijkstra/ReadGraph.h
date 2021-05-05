#ifndef READ_GRAPH_H
#define READ_GRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

template <typename Graph, typename Weigh>
class ReadGraph{

public:
    ReadGraph(Graph &graph, const string & filename){
        ifstream file(filename);
        string line;
        int V, E;
        // 是否成功打开文件
        assert(file.is_open());
        // 确保第一行读取成功
        assert(getline(file, line));
        // 第一行line的内容放入一个stringstream中
        stringstream ss(line);
        // 解析出V和E两个int变量
        ss>>V>>E;

        // 先确定节点数是否一致
        assert(V == graph.V());
        // 有多少条边就读取多少次
        for(int i=0; i<E; i++){
            assert(getline(file, line));
            stringstream ss(line);
            int a,b;
            Weigh w;
            ss>>a>>b>>w;
            assert(a>=0 && a<V);
            assert(b>=0 && b<V);
            graph.addEdge(a,b,w);
        }
    }
};

#endif