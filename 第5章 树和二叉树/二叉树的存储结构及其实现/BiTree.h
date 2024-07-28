#pragma once
#include "CirQueue.h"
#include <iostream>
using namespace std;

struct BiNode
{
	DataType data;
	BiNode* lchild, * rchild;
};

class BiTree
{
private:
	BiNode* root; // 指向根结点的头指针
public:
	BiTree() // 构造函数，建立一颗二叉树
	{
		root = create(root);
	}
	~BiTree() // 析构函数
	{
		release(root);
	}
	void preOrder() // 前序遍历二叉树
	{
		preOrder(root);
	}
	void inOrder() // 中序遍历二叉树
	{
		inOrder(root);
	}
	void postOrder()
	{
		postOrder(root); // 后序遍历二叉树
	}
	void leverOrder() // 层序遍历二叉树
	{
		leverOrder(root);
	}
private:
	BiNode* create(BiNode* bt); // 构造函数调用
	void release(BiNode* bt); // 析构函数调用
	void preOrder(BiNode* bt); // 前序遍历函数调用
	void inOrder(BiNode* bt); // 中序遍历函数调用
	void postOrder(BiNode* bt); // 后序遍历函数调用
	void leverOrder(BiNode* bt); // 层序遍历函数调用
};
