#include <stdio.h>
typedef int DataType;

typedef struct node
{
	DataType data; // ������
	struct node* next; // ָ����
}Node, * Link;

int length(Link head)
{
	Link p = head->next;
	int count = 0;
	while (p != NULL)
	{
		p = p->next;
		count++;
	}
	return count; // ע�� count �ĳ�ʼ���ͷ���ֵ֮��Ĺ�ϵ
}
