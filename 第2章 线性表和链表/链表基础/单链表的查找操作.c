#include <stdio.h>
#include <stdbool.h>
typedef int DataType;

typedef struct node
{
	DataType data; // ������
	struct node* next; // ָ����
}Node, * Link;

bool queryNode(Link head, DataType x)
{
	Link p = head->next;
	while (p != NULL)
	{
		if (p->data == x)
		{
			printf("%d", p->data); // �ҵ�������������������ǰ���� true
			return true;
		}
		p = p->next;
	}

	// ���ѭ�������ˣ�˵��û���ҵ�
	return false;
}
