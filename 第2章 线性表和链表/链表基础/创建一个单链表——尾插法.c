#include <stdio.h>
typedef int DataType;

typedef struct node
{
	DataType data; // ������
	struct node* next; //ָ����
}Node, * Link;

Link newList(DataType a[], int n)
{
	Link head = (Link)malloc(sizeof(Node)); // ����ͷ���
	head->next = NULL;
	Link rear = head; // βָ���ʼ��
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
