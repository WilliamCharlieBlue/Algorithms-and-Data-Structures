#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "FileOps.h"
#include "SequenceST.h"

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
        destroy(root);
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

    bool contain(Key key){
        return contain(root, key);
    }

    // 使用Value指针，可以将未找到的结果以NULL的形式表示
    Value* search(Key key){
        return search(root, key);
    }

    // 前序遍历
    void preOrder(){
        preOrder(root);
    }

    // 前序遍历
    void inOrder(){
        inOrder(root);
    }

    // 后序遍历
    void postOrder(){
        postOrder(root);
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
            node->left = insert(node->left, key, value);
        else
            // 大key往右节点插入
            node->right = insert(node->right, key, value);

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

    // 查看以node为根的二叉搜索树中是否包含键为key的节点
    bool contain(Node* node, Key key){
        if(node == NULL)
            return false;

        if(key == node->key)
            return true;
        else if(key < node->key)
            return contain(node->left, key);
        else
            return contain(node->right, key);
    }

    // 在以node为根的二叉搜索树中查找key所对应的value
    Value* search(Node *node, Key key){
        if(node == NULL)
            return NULL;

        if(key == node->key)
            return &(node->value);
        else if(key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    // 对以node为根的二叉搜索树进行前序遍历
    void preOrder(Node* node){
        if(node != NULL){
            cout << node->key << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    // 对以node为根的二叉搜索树进行中序遍历；可用于从小到大的排序
    void inOrder(Node* node){
        if(node != NULL){
            inOrder(node->left);
            cout << node->key << endl;
            inOrder(node->right);
        }
    }

    // 对以node为根的二叉搜索树进行后序遍历
    void postOrder(Node* node){
        if(node != NULL){
            postOrder(node->left);
            postOrder(node->right);
            cout << node->key << endl;
        }
    }

    // 与后续遍历的思想一致，对整个二叉树进行空间释放
    void destroy(Node* node){
        if(node != NULL){
            destroy(node->left);
            destroy(node->right);

            delete node;
            count--;
        }
    }
};

int main(){

    // string filename = "bible.txt";
    string filename = "Origin_of_Species_Charles_Darwin.txt";
    vector<string> words;
    if(FileOps::readFile(filename, words)){
        cout << "There are totally " << words.size() << " words in " << filename << endl;
        cout << endl;

        // 测试BST
        time_t startTime = clock();
        // 统计所有词的词频
        // 注: 这个词频统计法相对简陋, 没有考虑很多文本处理中的特殊问题
        // 在这里只做性能测试用
        BST<string, int> bst = BST<string, int>();
        for(vector<string>::iterator iter=words.begin(); iter != words.end(); iter++){
            int *res = bst.search(*iter);
            if(res == NULL)
                bst.insert(*iter, 1);
            else
                (*res)++;
        }

        // 输出life一词出现的频率
        if(bst.contain("life"))
            cout << "'life' : " << *bst.search("life") << endl;
        else
            cout << " No word 'life' in " << filename << endl;

        time_t endTime = clock();

        cout << "BST , time: " << double(endTime - startTime)/ CLOCKS_PER_SEC << " s." << endl;
        cout << endl;


        // 测试SST  基于链表
        startTime = clock();
        SequenceST<string, int> sst = SequenceST<string, int>();
        for(vector<string>::iterator iter = words.begin(); iter != words.end(); iter++){
            int *res = sst.search(*iter);
            if(res == NULL)
                sst.insert(*iter, 1);
            else
                (*res)++;
        }

        if(sst.contain("life"))
            cout << "'life' : " << *sst.search("life") << endl;
        else
            cout << " No word 'life' in " << filename << endl;

        endTime = clock();

        cout << "SST , time: " << double(endTime - startTime)/ CLOCKS_PER_SEC << " s." << endl;
        cout << endl;
    }

    return 0;
}