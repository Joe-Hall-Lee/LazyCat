#include "BiTree.h"

void visit(DataType c)
{
	cout << c << endl;
}

void BiTree::preOrder(BiNode* bt)
{
	if (bt == NULL) // 递归调用的结束条件
		return;
	else
	{
		visit(bt->data); // 访问根结点bt的数据域
		preOrder(bt->lchild); // 前序递归遍历 bt 的左子树
		preOrder(bt->rchild); // 前序遍历递归 bt 的右子树
	}
}

void BiTree::inOrder(BiNode* bt)
{
	if (bt == NULL) // 递归调用的结束条件
		return;
	else
	{
		inOrder(bt->lchild); // 中序递归遍历 bt 的左子树
		visit(bt->data); // 访问根结点 bt 的数据域
		inOrder(bt->rchild); // 中序递归遍历 bt 的右子树
	}
}

void BiTree::postOrder(BiNode* bt)
{
	if (bt == NULL) // 递归调用的结束条件
		return;
	else
	{
		postOrder(bt->lchild); // 后序递归遍历 bt 的左子树
		postOrder(bt->rchild); // 后序递归遍历 bt 的右子树
		visit(bt->data); // 访问根结点 bt 的数据域
	}
}

void BiTree::leverOrder(BiNode* bt)
{
	if (root == NULL) // 二叉树为空，算法结束
		return;
	CirQueue queue;
	queue.enQueue(bt->data); // 根指针入队
	BiNode* q;
	while (!queue.isEmpty()) // 当队列为空时
	{
		queue.deQueue(&(q->data)); // 出队
		visit(q->data);
		if (q->lchild != NULL) // 左孩子入队
			queue.enQueue(q->lchild->data);
		if (q->rchild != NULL) // 右孩子入队
			queue.enQueue(q->rchild->data);
	}
}

BiNode* BiTree::create(BiNode* bt)
{
	char ch;
	cin >> ch; // 输入结点的数据信息，假设为字符
	if (ch == '#') // 建立一棵空树
		bt = NULL;
	else
	{
		bt = new BiNode;
		bt->data = ch; // 生成一个结点，数据域为 ch
		bt->lchild = create(bt->lchild);
		bt->rchild = create(bt->rchild);
	}
	return bt;
}