typedef int DataType;

typedef struct node
{
	DataType data; // Êý¾ÝÓò
	struct node* next; // Ö¸ÕëÓò
}Node, * Link;

void clearLink(Link head)
{
	while (head)
	{
		Link q = head;
		head = head->next;
		free(q);
	}
}
