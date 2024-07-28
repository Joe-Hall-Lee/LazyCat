#include "BiTree.h"

void visit(DataType c)
{
	cout << c << endl;
}

void BiTree::preOrder(BiNode* bt)
{
	if (bt == NULL) // �ݹ���õĽ�������
		return;
	else
	{
		visit(bt->data); // ���ʸ����bt��������
		preOrder(bt->lchild); // ǰ��ݹ���� bt ��������
		preOrder(bt->rchild); // ǰ������ݹ� bt ��������
	}
}

void BiTree::inOrder(BiNode* bt)
{
	if (bt == NULL) // �ݹ���õĽ�������
		return;
	else
	{
		inOrder(bt->lchild); // ����ݹ���� bt ��������
		visit(bt->data); // ���ʸ���� bt ��������
		inOrder(bt->rchild); // ����ݹ���� bt ��������
	}
}

void BiTree::postOrder(BiNode* bt)
{
	if (bt == NULL) // �ݹ���õĽ�������
		return;
	else
	{
		postOrder(bt->lchild); // ����ݹ���� bt ��������
		postOrder(bt->rchild); // ����ݹ���� bt ��������
		visit(bt->data); // ���ʸ���� bt ��������
	}
}

void BiTree::leverOrder(BiNode* bt)
{
	if (root == NULL) // ������Ϊ�գ��㷨����
		return;
	CirQueue queue;
	queue.enQueue(bt->data); // ��ָ�����
	BiNode* q;
	while (!queue.isEmpty()) // ������Ϊ��ʱ
	{
		queue.deQueue(&(q->data)); // ����
		visit(q->data);
		if (q->lchild != NULL) // �������
			queue.enQueue(q->lchild->data);
		if (q->rchild != NULL) // �Һ������
			queue.enQueue(q->rchild->data);
	}
}

BiNode* BiTree::create(BiNode* bt)
{
	char ch;
	cin >> ch; // �������������Ϣ������Ϊ�ַ�
	if (ch == '#') // ����һ�ÿ���
		bt = NULL;
	else
	{
		bt = new BiNode;
		bt->data = ch; // ����һ����㣬������Ϊ ch
		bt->lchild = create(bt->lchild);
		bt->rchild = create(bt->rchild);
	}
	return bt;
}