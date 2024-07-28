#include <iostream>
using namespace std;
typedef int DataType;
struct BiNode
{
	DataType data;
	BiNode* lchild, * rchild;
};
BiNode* root; // ָ�������ͷָ��

// ����������ɾ��һ������㷨
void deleteNode(BiNode*& bt)
{
	BiNode* p;
	if (bt->lchild == NULL && bt->rchild == NULL) // Ҷ�ӽ��
	{
		p = bt;
		bt = NULL;
		delete p;
	}
	else if (bt->rchild == NULL) // ������Ϊ��
	{
		p = bt;
		bt = bt->lchild;
		delete p;
	}
	else if (bt->lchild == NULL) // ������Ϊ��
	{
		p = bt;
		bt = bt->rchild;
		delete p;
	}
	else // ������������Ϊ��
	{
		BiNode* parent = bt;
		BiNode* pre = bt->lchild;
		// ת��Ȼ�����ҵ���ͷ���ҵ�������������㣩
		while (pre->rchild)
		{
			parent = pre;
			pre = pre->rchild;
		}
		bt->data = pre->data; // pre ָ��Ҫɾ����ǰ�����滻 bt ����
		if (parent != bt) // �ж��Ƿ�ִ�������� while ѭ��
			parent->rchild = pre->lchild; // ִ���� while ѭ�����ؽ� pre ������
		else
			parent->lchild = pre->lchild; // δִ�� while ѭ�����ؽ� pre ������
		delete pre;
	}
}
