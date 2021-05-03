#include <iostream>
#include <ctime>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"

using namespace std;

int main() {
    // testG1.txt
    string filename = "testG1.txt";
    SparseGraph g1(13, false);
    ReadGraph<SparseGraph> readGraph1(g1, filename);
    Component<SparseGraph> component1(g1);
    cout << "Sparse Graph: " << endl;
    g1.show();
    cout << "testG1.txt, Component Count: "<< component1.count() << endl;
    cout << endl;

    // testG2.txt
    filename = "testG2.txt";
    SparseGraph g2(7, false);
    ReadGraph<SparseGraph> readGraph2(g2, filename);
    Component<SparseGraph> component2(g2);
    cout << "Sparse Graph: " << endl;
    g2.show();
    cout << "testG2.txt, Component Count: "<< component2.count() << endl;
    cout << endl;

    return 0;
}