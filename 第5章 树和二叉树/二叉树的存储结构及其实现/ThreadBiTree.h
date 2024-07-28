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
	ThreadNode* root; // ָ�����������ͷָ��
	ThreadNode* pre;
public:
	ThreadBiTree() // ���캯��������������������
	{
		pre = NULL;
		root = create(root);
		inThread(root);
	}

	~ThreadBiTree(); // �����������ͷŸ����Ĵ洢�ռ�
	ThreadNode* next(ThreadNode* p); // ���� p �ĺ��
	void inOrder(); // ���������������
private:
	ThreadNode* create(ThreadNode* bt);
	void inThread(ThreadNode* p); // ������������
};
