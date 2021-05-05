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

    // LazyPrim 和 Prim 性能比较
    main_performance();

    return 0;

}