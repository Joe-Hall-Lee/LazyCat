#include <stdio.h>
#include <iostream>
typedef int DataType;

typedef struct node
{
	DataType data; // 数据域
	struct node* next; //指针域
}Node, * Link;

Link newList(DataType a[], int n)
{
	// 创建头结点
	Link head = (Link)malloc(sizeof(Node));
	head->next = NULL;
	// 创建后续结点
	for (int i = 0; i < n; i++)
	{
		Link node = (Link)malloc(sizeof(Node));
		node->data = a[i];
		node->next = head->next;
		head->next = node;
	}
	return head;
}
