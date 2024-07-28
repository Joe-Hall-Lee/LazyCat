#include <iostream>
using namespace std;
typedef int DataType;
struct BiNode
{
	DataType data;
	BiNode* lchild, * rchild;
};
BiNode* root; // 指向根结点的头指针

// 二叉排序树删除一个结点算法
void deleteNode(BiNode*& bt)
{
	BiNode* p;
	if (bt->lchild == NULL && bt->rchild == NULL) // 叶子结点
	{
		p = bt;
		bt = NULL;
		delete p;
	}
	else if (bt->rchild == NULL) // 右子树为空
	{
		p = bt;
		bt = bt->lchild;
		delete p;
	}
	else if (bt->lchild == NULL) // 左子树为空
	{
		p = bt;
		bt = bt->rchild;
		delete p;
	}
	else // 左右子树均不为空
	{
		BiNode* parent = bt;
		BiNode* pre = bt->lchild;
		// 转左，然后向右到尽头（找到左子树中最大结点）
		while (pre->rchild)
		{
			parent = pre;
			pre = pre->rchild;
		}
		bt->data = pre->data; // pre 指向要删结点的前驱，替换 bt 数据
		if (parent != bt) // 判断是否执行了上述 while 循环
			parent->rchild = pre->lchild; // 执行了 while 循环，重接 pre 右子树
		else
			parent->lchild = pre->lchild; // 未执行 while 循环，重接 pre 左子树
		delete pre;
	}
}
