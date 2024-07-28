#include <stdio.h>
typedef int DataType;

typedef struct node
{
	DataType data; // 数据域
	struct node* next; // 指针域
}Node, * Link;

int length(Link head)
{
	Link p = head->next;
	int count = 0;
	while (p != NULL)
	{
		p = p->next;
		count++;
	}
	return count; // 注意 count 的初始化和返回值之间的关系
}
