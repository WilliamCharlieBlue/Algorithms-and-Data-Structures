#include <iostream>
#include "UnionFindTestHelper.h"

using namespace std;

int main() {
    int n = 10000;

    UnionFindTestHelper::testUF1(n);
    cout<<endl;
    n = 100000;
    UnionFindTestHelper::testUF1(n);
    cout<<endl;
    UnionFindTestHelper::testUF2(n);
    cout<<endl;
    UnionFindTestHelper::testUF3(n);
    cout<<endl;
    UnionFindTestHelper::testUF4(n);
    cout<<endl;
    UnionFindTestHelper::testUF5(n);
    cout<<endl;
}