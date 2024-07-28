#include "ThreadBiTree.h"

void visit(DataType c)
{
	cout << c << endl;
}

void ThreadBiTree::inThread(ThreadNode* p)
{
	if (p == NULL)
		return;
	inThread(p->lchild); // 左子树线索化
	if (p->lchild == NULL) // 建立 p 的前驱线索
	{
		p->ltag = 1;
		p->lchild = pre;
	}
	if (pre != NULL && pre->rchild == NULL) // 建立 pre 的后继线索
	{
		pre->rtag = 1;
		pre->rchild = p;
	}
	pre = p;
	inThread(p->rchild); // 右子树线索化
}

ThreadNode* ThreadBiTree::next(ThreadNode* p)
{
	ThreadNode* q;
	if (p->rtag == 1) // 右标志为 1，可直接得到后继结点
		q = p->rchild;
	else // 右标志为 0，则要找到右子树最左下角的结点
	{
		q = p->rchild;
		while (q->ltag == 0) // 查找最左下结点位置
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
	while (p->ltag == 0) // 查找中序遍历的第一个结点 p
		p = p->lchild;
	visit(p->data); // 访问第一个结点
	while (p->rchild != NULL) // 当 p 存在后继，依次访问后继结点
	{
		p = next(p);
		visit(p->data);
	}
}