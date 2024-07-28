#include <stdio.h>
#include <stdbool.h>
typedef int DataType;

typedef struct node
{
	DataType data; // ������
	struct node* next; // ָ����
}Node, * Link;

bool deleteNode(Link head, DataType x)
{
	if (head == NULL || head->next == NULL) // ������û������
		return false;
	Link p = head->next; // ��ʼ����p��q ����ָ��һǰһ��
	Link q = head;
	while (p != NULL)
	{
		if (p->data == x) // �ҵ�x��㣬ɾ�������㣬����ǰ����
		{
			q->next = p->next;
			free(p);
			return true;
		}
		else // q �� data �򲻵��� x������������
		{
			q = p;
			p = p->next;
		}

		// ���ѭ�������ˣ�˵��û���ҵ��� x ��ȵĽ��
		return false;
	}
}
