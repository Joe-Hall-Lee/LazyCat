#include <iostream>
using namespace std;
typedef int DataType;
struct BiNode
{
	DataType data;
	BiNode* lchild, * rchild;
};
BiNode* root; // 指向根结点的头指针

BiNode* searchBST(BiNode* bt, DataType key)
{
	if (bt == NULL)
		return NULL;
	else
	{
		if (key == bt->data)
			return bt;
		else if (key < bt->data)
			return searchBST(bt->lchild, key);
		else
			return searchBST(bt->rchild, key);
	}
}
