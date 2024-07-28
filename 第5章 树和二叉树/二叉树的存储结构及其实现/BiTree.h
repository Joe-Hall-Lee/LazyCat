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
	BiNode* root; // ָ�������ͷָ��
public:
	BiTree() // ���캯��������һ�Ŷ�����
	{
		root = create(root);
	}
	~BiTree() // ��������
	{
		release(root);
	}
	void preOrder() // ǰ�����������
	{
		preOrder(root);
	}
	void inOrder() // �������������
	{
		inOrder(root);
	}
	void postOrder()
	{
		postOrder(root); // �������������
	}
	void leverOrder() // �������������
	{
		leverOrder(root);
	}
private:
	BiNode* create(BiNode* bt); // ���캯������
	void release(BiNode* bt); // ������������
	void preOrder(BiNode* bt); // ǰ�������������
	void inOrder(BiNode* bt); // ���������������
	void postOrder(BiNode* bt); // ���������������
	void leverOrder(BiNode* bt); // ���������������
};
