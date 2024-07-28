#include <stdio.h>
#include <iostream>
typedef int DataType;

typedef struct node
{
	DataType data; // ������
	struct node* next; //ָ����
}Node, * Link;

Link newList(DataType a[], int n)
{
	// ����ͷ���
	Link head = (Link)malloc(sizeof(Node));
	head->next = NULL;
	// �����������
	for (int i = 0; i < n; i++)
	{
		Link node = (Link)malloc(sizeof(Node));
		node->data = a[i];
		node->next = head->next;
		head->next = node;
	}
	return head;
}
