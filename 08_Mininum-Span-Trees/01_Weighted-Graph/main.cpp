#include <iostream>
#include <ctime>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"
#include "Path.h"
#include "ShortestPath.h"

using namespace std;

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

    return 0;
}