#include <stdio.h>
typedef int DataType;

typedef struct node
{
	DataType data; // 数据域
	struct node* next; //指针域
}Node, * Link;

Link newList(DataType a[], int n)
{
	Link head = (Link)malloc(sizeof(Node)); // 生成头结点
	head->next = NULL;
	Link rear = head; // 尾指针初始化
	for (int i = 0; i < n; i++)
	{
		Link node = (Link)malloc(sizeof(Node));
		node->data = a[i];
		rear->next = node;
		rear = node;
	}
	rear->next = NULL;
	return head;
}
