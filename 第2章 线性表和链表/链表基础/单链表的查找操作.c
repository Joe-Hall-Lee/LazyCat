#include <stdio.h>
#include <stdbool.h>
typedef int DataType;

typedef struct node
{
	DataType data; // 数据域
	struct node* next; // 指针域
}Node, * Link;

bool queryNode(Link head, DataType x)
{
	Link p = head->next;
	while (p != NULL)
	{
		if (p->data == x)
		{
			printf("%d", p->data); // 找到则调用输出函数，并提前返回 true
			return true;
		}
		p = p->next;
	}

	// 如果循环结束了，说明没有找到
	return false;
}
