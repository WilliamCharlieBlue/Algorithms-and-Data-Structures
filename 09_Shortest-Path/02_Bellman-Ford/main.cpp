#include <iostream>
#include <ctime>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"
#include "Path.h"
#include "ShortestPath.h"
#include "LazyPrimMST.h"
#include "PrimMST.h"
#include "KruskalMST.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

using namespace std;

int main_performance(){
    string filename3 = "testG3.txt";
    int V3 = 8;
    string filename4 = "testG4.txt";
    int V4 = 250;
    string filename5 = "testG5.txt";
    int V5 = 1000;
    string filename6 = "testG6.txt";
    int V6 = 10000;

    // 文件读取
    SparseGraph<double> g3 = SparseGraph<double>(V3, false);
    ReadGraph<SparseGraph<double>, double> readGraph3(g3, filename3);
    cout<<filename3<<" load successfully."<<endl;

    SparseGraph<double> g4 = SparseGraph<double>(V4, false);
    ReadGraph<SparseGraph<double>, double> readGraph4(g4, filename4);
    cout<<filename4<<" load successfully."<<endl;

    SparseGraph<double> g5 = SparseGraph<double>(V5, false);
    ReadGraph<SparseGraph<double>, double> readGraph5(g5, filename5);
    cout<<filename5<<" load successfully."<<endl;

    SparseGraph<double> g6 = SparseGraph<double>(V6, false);
    ReadGraph<SparseGraph<double>, double> readGraph6(g6, filename6);
    cout<<filename6<<" load successfully."<<endl;

    cout<<endl;

    clock_t startTime, endTime;

    // Test Lazy Prim MST
    cout<<"Test Lazy Prim MST: "<<endl;

    startTime = clock();
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMst3(g3);
    endTime = clock();
    cout<<"TEST for G3: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMst4(g4);
    endTime = clock();
    cout<<"TEST for G4: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMst5(g5);
    endTime = clock();
    cout<<"TEST for G5: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMst6(g6);
    endTime = clock();
    cout<<"TEST for G6: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    cout<<endl;

    // Test Prim MST
    cout<<"Test Prim MST: "<<endl;

    startTime = clock();
    PrimMST<SparseGraph<double>, double> PrimMst3(g3);
    endTime = clock();
    cout<<"TEST for G3: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    PrimMST<SparseGraph<double>, double> PrimMst4(g4);
    endTime = clock();
    cout<<"TEST for G4: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    PrimMST<SparseGraph<double>, double> PrimMst5(g5);
    endTime = clock();
    cout<<"TEST for G5: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    PrimMST<SparseGraph<double>, double> PrimMst6(g6);
    endTime = clock();
    cout<<"TEST for G6: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    cout<<endl;

    // Test Kruskal MST
    cout<<"Test Kruskal MST: "<<endl;

    startTime = clock();
    KruskalMST<SparseGraph<double>, double> KruskalMst3(g3);
    endTime = clock();
    cout<<"TEST for G3: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    KruskalMST<SparseGraph<double>, double> KruskalMst4(g4);
    endTime = clock();
    cout<<"TEST for G4: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    KruskalMST<SparseGraph<double>, double> KruskalMst5(g5);
    endTime = clock();
    cout<<"TEST for G5: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

    startTime = clock();
    KruskalMST<SparseGraph<double>, double> KruskalMst6(g6);
    endTime = clock();
    cout<<"TEST for G6: "<<(double )(endTime-startTime)/CLOCKS_PER_SEC<<" s."<<endl;

}

int main() {

    // testG3.txt
    string filename = "testG3.txt";
    int V =8;

    DenseGraph<double> g1 = DenseGraph<double>(V, false);
    ReadGraph<DenseGraph<double>, double> readGraph1(g1, filename);
    g1.show();
    cout<<endl;

    SparseGraph<double> g2 = SparseGraph<double>(V, false);
    ReadGraph<SparseGraph<double>, double> readGraph2(g2, filename);
    g2.show();
    cout<<endl;

    // Test Lazy Prim MST
    cout<<"Test Lazy Prim MST:"<<endl;
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMst(g2);
    vector<Edge<double>> mst = lazyPrimMst.mstEdges();
    for(int i=0; i<mst.size(); i++)
        cout << mst[i] << endl;
    cout << "The MST weight is: " << lazyPrimMst.result() << endl;
    cout << endl;


    // Test Prim MST
    cout<<"Test Prim MST:"<<endl;
    PrimMST<SparseGraph<double>, double> PrimMst(g2);
    mst = PrimMst.mstEdges();
    for(int i=0; i<mst.size(); i++)
        cout << mst[i] << endl;
    cout << "The MST weight is: " << PrimMst.result() << endl;
    cout << endl;

    // Test Kruskal MST
    cout<<"Test Kruskal MST:"<<endl;
    PrimMST<SparseGraph<double>, double> KruskalMst(g2);
    mst = KruskalMst.mstEdges();
    for(int i=0; i<mst.size(); i++)
        cout << mst[i] << endl;
    cout << "The MST weight is: " << KruskalMst.result() << endl;
    cout << endl;

    // LazyPrim 、Prim 和 Kruskal性能比较
//    main_performance();
    // Prim > Kruskal > LazyPrim ；Kruskal更容易实现，在图比较小的时候可以考虑用Kruskal

    string filename7 = "testG7.txt";
    int V7 = 5;
//    SparseGraph<int> g7 = SparseGraph<int>(V7, false);
    SparseGraph<int> g7 = SparseGraph<int>(V7, true);
    ReadGraph<SparseGraph<int>, int> readGraph7(g7, filename7);

    cout<<"Test Dijkstra: "<<endl<<endl;
    Dijkstra<SparseGraph<int>,int> dij(g7, 0);
    for(int i=1; i<V7; i++){
        cout<<"Shortest Path to "<<i<<" : "<<dij.shortestPathTo(i)<<endl;
        dij.showPath(i);
        cout<<"------------"<<endl;
    }

    cout << endl;

//    string filename8 = "testNegative.txt";
    string filename8 = "testNegativeCycle.txt";
    int V8 = 5;
//    SparseGraph<int> g8 = SparseGraph<int>(V8, false);
    SparseGraph<int> g8 = SparseGraph<int>(V8, true);
    ReadGraph<SparseGraph<int>, int> readGraph8(g8, filename8);

    cout<<"Test BellmanFord: "<<endl<<endl;
    BellmanFord<SparseGraph<int>,int> bellmanFord(g8, 0);
    if(bellmanFord.negativeCycle())
        cout<<"The graph contains negative cycle!"<<endl;
    else
        for(int i=1; i<V8; i++){
            cout<<"Shortest Path to "<<i<<" : "<<bellmanFord.shortestPathTo(i)<<endl;
            bellmanFord.showPath(i);
            cout<<"------------"<<endl;
        }

    return 0;

}