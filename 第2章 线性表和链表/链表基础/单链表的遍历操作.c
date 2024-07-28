#include <stdio.h>
typedef int DataType;

typedef struct node
{
	DataType data; // ������
	struct node* next; // ָ����
}Node, * Link;

void displayNode(Link head)
{
	Link p = head->next;
	while (p != NULL)
	{
		printf("%d", p->data);
		p = p->next;
	}
}
