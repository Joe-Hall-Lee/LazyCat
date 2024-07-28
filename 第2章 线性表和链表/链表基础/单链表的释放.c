typedef int DataType;

typedef struct node
{
	DataType data; // ������
	struct node* next; // ָ����
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
