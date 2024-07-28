#include <iostream>
using namespace std;

typedef struct element
{
	int weight;
	int lchild, rchild, parent;
}HTNode;

void huffmanCoding(HTNode huffTree[], char* huffCode[], int n)
{
	char* temp = new char[n]; // 定义工作空间，存储临时产生的编码串
	temp[n - 1] = '\0';
	for (int i = 0; i < n; i++) // 遍历哈夫曼树数组，生成哈夫曼编码
	{
		int start = n - 1;
		int pos = i; // pos 记录正在处理的当前位置
		int parent = huffTree[i].parent; // 找出父结点
		while (parent != -1)
		{
			if (huffTree[parent].lchild == pos) // 判断当前是左孩子还是右孩子
				temp[--start] = '0';
			else
				temp[--start] = '1';
			pos = parent; // 当前位置移动到父结点
			parent = huffTree[parent].parent; // 更新父结点
		}
		huffCode[i] = new char[n - start]; // 建立哈夫曼编码实际需要的内存空间
		strcpy(huffCode[i], &temp[start]); // 临时存储的哈夫曼编码存储到 huffCode 中
	}
	delete[]temp; // 释放工作空间
}
