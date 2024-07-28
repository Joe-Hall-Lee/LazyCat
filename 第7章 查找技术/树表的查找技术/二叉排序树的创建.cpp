#include <iostream>
using namespace std;
typedef int DataType;
struct BiNode
{
	DataType data;
	BiNode* lchild, * rchild;
};
BiNode* root; // 指向根结点的头指针

// 二叉排序树的插入算法
void insertBST(BiNode* bt, DataType key)
{
	if (bt == NULL)
	{
		bt = new BiNode;
		bt->data = key;
		bt->lchild = NULL;
		bt->rchild = NULL;
	}
	else
	{
		if (key < bt->data)
			insertBST(bt->lchild, key);
		else
			insertBST(bt->rchild, key);
	}
}

void CreateBST(DataType array[], int length)
{
	root = NULL;
	for (int i = 0; i < length; i++)
		insertBST(root, array[i]);
}
