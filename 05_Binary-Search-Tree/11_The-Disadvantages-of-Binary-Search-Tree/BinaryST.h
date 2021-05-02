#ifndef BINARY_SEARCH_TABLE_H
#define BINARY_SEARCH_TABLE_H

#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

// 二分搜索树
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
        // 节点的拷贝
        Node(Node* node){
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
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

    // 层序遍历
    void levelOrder(){

        queue<Node*> q;
        // 先将顶节点压入队列
        q.push(root);
        while(!q.empty()){
            // 取出队首元素
            Node *node = q.front();
            q.pop();
            cout << node->key << endl;
            // 顶节点如果有左/右子节点时，压入队列
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node-right);
        }
    }

    // 寻找最小值
    Key minimum(){
        assert(count != 0);
        Node* minNode = minimum(root);
        return minNode->key;
    }

    // 寻找最大值
    Key maximum(){
        assert(count != 0);
        Node* maxNode =maximum(root);
        return maxNode->key;
    }

    // 从二叉树中删除最小值所在的节点
    void removeMin(){
        if(root)
            root = removeMin(root);
    }

    // 从二叉树中删除最大值所在的节点
    void removeMax(){
        if(root)
            root = removeMax(root);
    }

    // 从二叉树中删除键为key的节点
    void remove(Key key){
        root = remove(root, key);
    }

    // 寻找key的floor，递归算法
    // 如果不存在key的floor值(key比BST的最小值还小)，返回NULL
    Key* floor(Key key){
        if(count == 0 || key < minimum())
            return NULL;

        Node floorNode = floor(root, key);
        return &(floorNode->key);
    }

    // 寻找key的ceil，递归算法
    // 如果不存在key的ceil值(key比BST的最大值还大)，返回NULL
    Key* ceil(Key key){
        if(count == 0 || key > maximum())
            return NULL;

        Node *ceilNode = ceil(root, key);
        return &(ceilNode->key);
    }

    // 查找key的前驱
    // 如果不存在key的前驱(key不存在, 或者key是整棵二叉树中的最小值), 则返回NULL
    Key* predecessor(Key key){
        Node *node = search(root, key);
        // 如果key所在的节点不存在, 则key没有前驱, 返回NULL
        if(node == NULL)
            return NULL;
        // 如果key所在的节点左子树不为空,则其左子树的最大值为key的前驱
        if(node->left != NULL)
            return &(maximum(node->left)->key);
        // 否则，key的前驱在从根节点到key的路径上, 在这个路径上寻找到比key小的最大值, 即为key的前驱
        Node *preNode = predecssorFromAncestor(root, key);
        return preNode == NULL ? NULL: &(preNode->key);
    }

    // 查找key的后继
    // 如果不存在key的后继(key不存在, 或者key是整棵二叉树中的最大值), 则返回NULL
    Key* succcessor(Key key){
        Node *node = search(root, key);
        // 如果key所在的节点不存在, 则key没有后继, 返回NULL
        if(node == NULL)
            return NULL;
        // 如果key所在的节点右子树不为空,则其右子树的最小值为key的后继
        if(node->right != NULL)
            return &(minimum(node->right)->key);
        // 否则，key的后继在从根节点到key的路径上, 在这个路径上寻找到比key大的最小值, 即为key的后继
        Node *sucNode = successorFromAncestor(root, key);
        return sucNode == NULL ? NULL: &(sucNode->key);
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

    // 在以node为根的二叉搜索树中，返回最小键值的节点
    Node* minimum(Node* node){
        if(node->left == NULL)
            return node;
        // 无左子节点时为最小，否则再往左找
        return minimum(node->left);
    }

    // 在以node为根的二叉搜索树中，返回最大键值的节点
    Node* maximum(Node* node){
        if(node->right == NULL)
            return node;
        // 无右子节点时为最大，否则再往右找
        return maximum(node->right);
    }

    // 删除掉以node为根的二分搜索树中的最小节点
    // 返回删除节点后新的二分搜索树的根
    Node* removeMin(Node* node){
        if(node->left == NULL){
            // 及时node->right为NULL也没关系，返回一个NULL就行
            Node* rightNode = node->right;
            delete node;
            count--;
            return rightNode;
        }
        // 如果此节点不是最小的，再往左找
        node->left =  removeMin(node->left);
        return node;
    }

    // 删除掉以node为根的二分搜索树中的最大节点
    // 返回删除节点后新的二分搜索树的根
    Node* removeMax(Node* node){
        if(node->right == NULL){
            // 及时node->left为NULL也没关系，返回一个NULL就行
            Node* leftNode = node->left;
            delete node;
            count--;
            return leftNode;
        }
        // 如果此节点不是最小的，再往左找
        node->right=  removeMin(node->right);
        return node;
    }

    // 删除掉以node为根的二分搜索树中键为key的节点
    // 返回删除节点后新的二分搜索树的根
    Node* remove(Node* node, Key key){
        if(node == NULL)
            return NULL;

        if(node->key > key){
            // 当前node->key较大，往左边找
            node->left = remove(node->left, key);
            return node;
        }
        else if(node->key < key){
            // 当前node-key较小，往右边找
            node->right = remove(node->right, key);
            return node;
        }
        else{
            // node->key == key
            if(node->left == NULL){
                // 左孩子为空，包含了左右孩子都为空的情形
                Node *rightNode = node->right;
                delete node;
                count--;
                return rightNode;
            }
            else if(node->right == NULL){
                // 右孩子为空
                Node *leftNode = node->left;
                delete node;
                count--;
                return leftNode;
            }
//            // 用前驱(左子树最大值)来实现Hubbard Deletion
//            else{
//                // 左孩子和右孩子均不为空
//                // Node *predecessor = maximum(node->left);
//                // 发现陷阱，predecessor指向的最小值，在removeMax中被删除，指针失效了
//                // 解决方法是对该节点进行复制，详情见构造体
//                Node *predecessor = new Node(maximum(node->left));
//                predecessor->left= removeMax(node->left);
//                predecessor->right = node->right;
//
//                delete node;
//                count--;
//                return predecessor;
//            }
                // 用后继(右子树最小值)来实现Hubbard Deletion
            else{
                // 左孩子和右孩子均不为空
                // Node *successor = minimum(node->right);
                // 发现陷阱，successor指向的最小值，在removeMin中被删除，指针失效了
                // 解决方法是对该节点进行复制，详情见构造体
                Node *successor = new Node(minimum(node->right));
                successor->right = removeMin(node->right);
                successor->left = node->left;

                delete node;
                count--;
                return successor;
            }
        }
    }

    //  在以node为根的二叉搜索树中, 寻找key的floor值所处的节点, 递归算法
    Node* floor(Node* node, Key key){
        if(node == NULL)
            return NULL;
        // 找到本身，直接返回
        if(node->key == key)
            return node;
        // 当前node->key较大，继续往左找
        if(node->key > key)
            return floor(node->left, key);
        // 当前node->key 比 key要小
        // node有可能是key的floor节点, 也有可能不是(存在比node->key大但是小于key的其余节点)
        // 先看看右边还有没有符合要求的
        Node* tempNode = floor(node->right, key);
        if(tempNode != NULL)
            return tempNode;
        // 如果没有符合的，此节点就是floor
        return node;
    }

    //  在以node为根的二叉搜索树中, 寻找key的ceil值所处的节点, 递归算法
    Node* ceil(Node* node, Key key){
        if(node == NULL)
            return NULL;
        // 找到本身，直接返回
        if(node->key == key)
            return node;
        // 当前node->key较小，继续往右找
        if(node->key < key)
            return ceil(node->right, key);
        // 当前node->key 比 key要大
        // node有可能是key的ceil节点, 也有可能不是(存在比node->key小但是大于key的其余节点)
        // 先看看左边还有没有符合要求的
        Node* tempNode = ceil(node->lef, key);
        if(tempNode != NULL)
            return tempNode;
        // 如果没有符合的，此节点就是ceil
        return node;
    }

    // 在以node为根的二叉搜索树中, 寻找key的祖先中,比key小的最大值所在节点, 递归算法
    // 算法调用前已保证key存在在以node为根的二叉树中
    Node* predecessorFromAncestor(Node* node, Key key){
        if(node->key == key)
            return NULL;

        if(node->key > key)
            // 如果当前节点大于key, 则当前节点不可能是比key小的最大值
            // 向下搜索到的结果直接返回
            return predecessorFromAncestor(node->left, key);
        else{
            assert(node->key < key);
            // 如果当前节点小于key, 则当前节点有可能是比key小的最大值
            // 向右继续搜索, 将结果存储到tempNode中
            Node* tempNode = predecessorFromAncestor(node->right, key);
            if(tempNode != NULL)
                return tempNode;
            else
                // 如果tempNode为空, 则当前节点即为先驱
                return node;
        }
    }

    // 在以node为根的二叉搜索树中, 寻找key的祖先中,比key大的最小值所在节点, 递归算法
    // 算法调用前已保证key存在在以node为根的二叉树中
    Node* successorFromAncestor(Node* node, Key key){
        if(node->key == key)
            return NULL;

        if(node->key < key)
            // 如果当前节点小于key, 则当前节点不可能是比key大的最小值
            // 向下搜索到的结果直接返回
            return successorFromAncestor(node->right, key);
        else{
            assert(node->key > key);
            // 如果当前节点大于key, 则当前节点有可能是比key大的最小值
            // 向左继续搜索, 将结果存储到tempNode中
            Node* tempNode = successorFromAncestor(node->left, key);
            if(tempNode != NULL)
                return tempNode;
            else
                // 如果tempNode为空, 则当前节点即为结果
                return node;
        }
    }

};

#endif