#include <iostream>
#include <ctime>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"
#include "Path.h"

using namespace std;

int main() {

    // testG2.txt
    string filename = "testG2.txt";
    SparseGraph g(7, false);
    ReadGraph<SparseGraph> readGraph(g, filename);
    Component<SparseGraph> component2(g);
    cout << "Sparse Graph: " << endl;
    g.show();
    cout << "testG2.txt, Component Count: "<< component2.count() << endl;
    Path<SparseGraph> dfs(g, 0);
    cout << "DFS : ";
    dfs.showPath(6);
    cout << endl;

    return 0;
}