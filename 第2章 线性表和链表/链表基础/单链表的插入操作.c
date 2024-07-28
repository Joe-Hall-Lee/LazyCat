#include <stdio.h>
#define false 0
typedef int DataType;

typedef struct node
{
	DataType data; // 数据域
	struct node* next; //指针域
}Node, * Link;

int insertNode(Link head, int i, DataType x)
{
	Link p = head; // 工作指针p指向头结点
	int count = 0;
	while (p != NULL && count < i - 1) // 查找第 i - 1 个结点
	{
		p = p->next;
		count++;
	}
	if (p == NULL)
		return false; // 没有找到第 i - 1 个结点
	else
	{
		Link node = (Link)malloc(sizeof(Node)); // 申请一个结点 node
		node->data = x;
		node->next = p->next; // 结点 node 插入结点 p 之后
		p->next = node;
	}
}
