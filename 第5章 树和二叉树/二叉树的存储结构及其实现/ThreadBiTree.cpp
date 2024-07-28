#include "ThreadBiTree.h"

void visit(DataType c)
{
	cout << c << endl;
}

void ThreadBiTree::inThread(ThreadNode* p)
{
	if (p == NULL)
		return;
	inThread(p->lchild); // ������������
	if (p->lchild == NULL) // ���� p ��ǰ������
	{
		p->ltag = 1;
		p->lchild = pre;
	}
	if (pre != NULL && pre->rchild == NULL) // ���� pre �ĺ������
	{
		pre->rtag = 1;
		pre->rchild = p;
	}
	pre = p;
	inThread(p->rchild); // ������������
}

ThreadNode* ThreadBiTree::next(ThreadNode* p)
{
	ThreadNode* q;
	if (p->rtag == 1) // �ұ�־Ϊ 1����ֱ�ӵõ���̽��
		q = p->rchild;
	else // �ұ�־Ϊ 0����Ҫ�ҵ������������½ǵĽ��
	{
		q = p->rchild;
		while (q->ltag == 0) // ���������½��λ��
			q = q->lchild;
	}
	return q;
}

void ThreadBiTree::inOrder()
{
	ThreadNode* p;
	if (root == NULL)
		return;
	p = root;
	while (p->ltag == 0) // ������������ĵ�һ����� p
		p = p->lchild;
	visit(p->data); // ���ʵ�һ�����
	while (p->rchild != NULL) // �� p ���ں�̣����η��ʺ�̽��
	{
		p = next(p);
		visit(p->data);
	}
}