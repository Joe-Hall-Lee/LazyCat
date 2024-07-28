#pragma once
#include <iostream>
using namespace std;
typedef char DataType;
struct ThreadNode
{
	DataType data;
	ThreadNode* lchild, * rchild;
	int ltag, rtag;
};

class ThreadBiTree
{
private:
	ThreadNode* root; // 指向线索链表的头指针
	ThreadNode* pre;
public:
	ThreadBiTree() // 构造函数，建立中序线索链表
	{
		pre = NULL;
		root = create(root);
		inThread(root);
	}

	~ThreadBiTree(); // 析构函数，释放各结点的存储空间
	ThreadNode* next(ThreadNode* p); // 查找 p 的后继
	void inOrder(); // 中序遍历线索链表
private:
	ThreadNode* create(ThreadNode* bt);
	void inThread(ThreadNode* p); // 线索化二叉树
};
