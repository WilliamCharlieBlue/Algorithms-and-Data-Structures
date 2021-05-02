#include <iostream>

using namespace std;

template <typename Key, typename Value>
class BST{
private:
    struct Node{
        Key key;
        Value value;
        // 定义节点的左右两个节点
        Node *left;
        Node *right;
        // 节点的构造函数
        Node(Key key, Value value){
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        }
    };

    Node *root;
    int count;

public:
    BST(){
        root = NULL;
        count = 0;
    }

    ~BST(){
        // ToDo: ~BST()
    }

    int size(){
        return count;
    }

    bool isEmpty(){
        // return root == NULL; // 等同
        return count == 0;
    }

};

int main(){

    cout << "Hello World" << endl;
    return 0;
}