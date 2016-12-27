//
//  main.cpp
//  search2
//
//  Created by Jep Xia on 2016/12/27.
//  Copyright © 2016年 Jep Xia. All rights reserved.
//
#include <iostream>
using namespace std;

typedef struct binaryTreeNode {
    int data;
    struct binaryTreeNode *leftChild,*rightChild;
}binaryTreeNode, *binaryTree;

bool binaryTreeInsert(binaryTree &p, int element){
    if(NULL == p) // 空树
    {
        p = new binaryTreeNode;
        p->data = element;
        p->leftChild = p->rightChild = NULL;
        return true;
    }
    
    if(element == p->data) // BST中不能有相等的值
        return false;
    
    if(element < p->data)  // 递归
        return binaryTreeInsert(p->leftChild, element);
    
    return binaryTreeInsert(p->rightChild, element); // 递归
    
}

//根据数组建立二叉树二叉树
void createBinaryTree(binaryTree &T, int a[], int number) {
    
    T = NULL;
    for(int i = 0; i < number; i++)
    {
        binaryTreeInsert(T, a[i]);
    }
}


bool Delete (binaryTree &p) {
    if (!p->rightChild) {
        p = p-> leftChild;
    } else if (!p->leftChild) {
        p = p->rightChild;
    } else {
        binaryTree f = p;
        f = f->leftChild;
        while (f->rightChild) {
            f = f->rightChild;
        }
        binaryTree node = p -> leftChild;
        delete p->leftChild;
        f->rightChild = p ->rightChild;
        p->data = node->data;
        p->leftChild = node->leftChild;
        p->rightChild = f;
    }
    return true;
}

bool deleteBinaryTree (binaryTree &T, int data) {
    if (!T) {
        return false;
    } else {
        if (T->data == data) {
            return Delete(T);
        } else if (T->data > data) {
            return deleteBinaryTree(T->leftChild, data);
        } else {
            return deleteBinaryTree(T->rightChild, data);
        }
    }
}



bool searchBinaryTree(binaryTree T, binaryTree parents, int data, binaryTree &res) {
    if (!T)
    {
        binaryTreeInsert(T, data);
        return false;
    } else {
        if (data == T->data)
        {
            res = T;
            return true;
        } else if (data < T->data) {
            return searchBinaryTree(T -> leftChild, T, data, res);
        } else {
            return searchBinaryTree(T -> rightChild, T, data, res);
        }
    }
}

//MARK: 递归方法遍历二叉树
//先序遍历二叉树
void preOrderTraverse(binaryTree T){
    if(T){
        cout << T -> data;
        preOrderTraverse(T->leftChild);
        preOrderTraverse(T->rightChild);
    }
}

//中序遍历二叉树
void inOrderTraverse(binaryTree T){
    if (T) {
        inOrderTraverse(T -> leftChild);
        cout << T -> data << " ";
        inOrderTraverse(T -> rightChild);
        
    }
}

//后序遍历二叉树
void postOrderTraverse (binaryTree T) {
    if (T) {
        postOrderTraverse(T -> leftChild);
        postOrderTraverse(T -> rightChild);
        cout << T -> data;
        
    }
}


int main(int argc, char const *argv[])
{
    cout << "请输入元素集合的数量" << endl;
    int number = 0;
    cin >> number;
    int* a = (int *) malloc ( sizeof(int) * number );
    cout << "请输入元素" << endl;
    for (int i = 0; i < number; ++i)
    {
        cin >> a[i];
    }
    cout << "请确认刚刚输入的元素集合：" << endl;


    for (int i = 0; i < number; ++i)
    {
        cout << a[i] << " ";
    }
    cout << "正在创建动态表..." << endl;
    binaryTree Tree;
    createBinaryTree(Tree, a, number);
    cout << "创建成功" << endl << "以下是中序遍历的结果" << endl;
    inOrderTraverse(Tree);
    cout << endl;
    while (true) {
        cout << "请输入要查询的数值" << endl;
        int x;
        cin >> x;
        binaryTree searchTree;
        if (!searchBinaryTree(Tree, NULL, x, searchTree)) {
            cout << "动态表中没有该数值 ..." << endl << "成功添加该数值！" << endl;
            binaryTreeInsert(Tree, x);
            cout << "输入1可重新遍历该表 \nor press any number to pass" << endl;
            int d;
            cin >> d;
            if (d == 1) {
                inOrderTraverse(Tree); cout << endl;
            }
            
        } else {
            cout << "查找成功！\n" << "如果要删除该数值请输入1 \nor press any number to pass " << endl;
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    if (deleteBinaryTree(Tree, x))
                        cout << "删除成功" << endl;
                    else
                        cout << "删除失败" << endl;
                    break;
                    
                default:
                    break;
            }
            cout << "输入1可重新遍历该表 \nor press any number to pass" << endl;
            int d;
            cin >> d;
            if (d == 1) {
                inOrderTraverse(Tree); cout << endl;
            }
        }
    }
    return 0;
}
