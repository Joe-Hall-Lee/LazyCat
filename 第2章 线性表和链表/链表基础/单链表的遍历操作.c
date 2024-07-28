#include <stdio.h>
typedef int DataType;

typedef struct node
{
	DataType data; // Êý¾ÝÓò
	struct node* next; // Ö¸ÕëÓò
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
