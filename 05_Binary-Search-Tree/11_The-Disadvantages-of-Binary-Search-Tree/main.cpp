#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <queue>
#include <cassert>
#include <algorithm>
#include "FileOps.h"
#include "SequenceST.h"
#include "BinaryST.h"

using namespace std;


int main(){

    // string filename = "bible.txt";
    string filename = "Origin_of_Species_Charles_Darwin.txt";
    vector<string> words;
    if(FileOps::readFile(filename, words)){
        cout << "There are totally " << words.size() << " words in " << filename << endl;
        cout << endl;

        // 测试BST 基于二叉树
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

    // 测试BST2 测试BST的局限性
    time_t startTime = clock();

    BST<string, int> bst2 = BST<string, int>();
    //插入二叉树前，将words进行排序, 二叉树退化为了链表，而同时又维护了很多指针，比SST都慢很多倍
    sort(words.begin(), words.end());
    for(vector<string>::iterator iter=words.begin(); iter != words.end(); iter++){
        int *res = bst2.search(*iter);
        if(res == NULL)
            bst2.insert(*iter, 1);
        else
            (*res)++;
    }

    // 输出life一词出现的频率
    if(bst2.contain("life"))
        cout << "'life' : " << *bst2.search("life") << endl;
    else
        cout << " No word 'life' in " << filename << endl;

    time_t endTime = clock();

    cout << "BST2 , time: " << double(endTime - startTime)/ CLOCKS_PER_SEC << " s." << endl;
    cout << endl;

    return 0;
}