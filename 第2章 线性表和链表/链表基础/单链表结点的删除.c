#include <stdio.h>
#include <stdbool.h>
typedef int DataType;

typedef struct node
{
	DataType data; // 数据域
	struct node* next; // 指针域
}Node, * Link;

bool deleteNode(Link head, DataType x)
{
	if (head == NULL || head->next == NULL) // 若链表没有数据
		return false;
	Link p = head->next; // 初始化。p、q 两个指针一前一后
	Link q = head;
	while (p != NULL)
	{
		if (p->data == x) // 找到x结点，删除这个结点，并提前返回
		{
			q->next = p->next;
			free(p);
			return true;
		}
		else // q 的 data 域不等于 x，则继续向后找
		{
			q = p;
			p = p->next;
		}

		// 如果循环结束了，说明没有找到和 x 相等的结点
		return false;
	}
}
