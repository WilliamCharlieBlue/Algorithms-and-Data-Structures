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
        // return root == NULL; // 与下行等同
        return count == 0;
    }
    // 向二分搜索树中插入一个新的(key, value)数据对
    void insert(Key key, Value value){
        root = insert(root, key, value);
    }

private:
    // 向以node为根的二叉树中，插入节点(Key, value)
    // 返回插入新节点后的二叉搜索树的根
    Node* insert(Node *node, Key key, Value value){
        // 如果某一个节点为空，则新增一个节点，将key和value传入
        if(node == NULL){
            count++;
            return new Node(key, value);
        }

        if(key == node->key)
            // 如果键相等，value需要覆盖
            node->value = value;
        else if(key < node->key)
            // 小key往左节点插入
            insert(node->left, key, value);
        else
            // 大key往右节点插入
            insert(node->right, key, value);

        return node;
    }

    Node* insert_without_Recursion(Node *node, Key key, Value value) {
        while(node != NULL){
            if(key == node->key) {
                // 如果键相等，value需要覆盖
                node->value = value;
                return node;
            }
            else if(key < node->key)
                // 小key往左节点插入
                node = node->left;
            else
                // 大key往右节点插入
                node = node->right;
        }
        // 初始为空节点，或者要在一个空位上插入新节点
        count++;
        return new Node(key, value);
    }
};

int main(){

    cout << "Hello World" << endl;
    return 0;
}