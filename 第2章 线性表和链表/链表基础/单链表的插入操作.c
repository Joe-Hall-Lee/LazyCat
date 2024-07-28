#include <stdio.h>
#define false 0
typedef int DataType;

typedef struct node
{
	DataType data; // ������
	struct node* next; //ָ����
}Node, * Link;

int insertNode(Link head, int i, DataType x)
{
	Link p = head; // ����ָ��pָ��ͷ���
	int count = 0;
	while (p != NULL && count < i - 1) // ���ҵ� i - 1 �����
	{
		p = p->next;
		count++;
	}
	if (p == NULL)
		return false; // û���ҵ��� i - 1 �����
	else
	{
		Link node = (Link)malloc(sizeof(Node)); // ����һ����� node
		node->data = x;
		node->next = p->next; // ��� node ������ p ֮��
		p->next = node;
	}
}
