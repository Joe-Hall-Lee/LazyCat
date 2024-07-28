#include <iostream>
using namespace std;
typedef int DataType;
struct BiNode
{
	DataType data;
	BiNode* lchild, * rchild;
};
BiNode* root; // ָ�������ͷָ��

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
