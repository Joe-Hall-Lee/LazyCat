#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

#define NO_LENGTH  20
#define NAME_LENGTH 110000

int flag1 = 0;
/* ����ѧ���ṹ������ݽṹ */
typedef struct Student
{
	char studentNo[20];
	char studentName[11];
};

/* ����ÿ����¼��������ݽṹ */
typedef struct node
{
	struct Student data; // ������
	struct node* next; // ָ����
}Node, * Link; // Node Ϊ node ���͵ı�����LinkΪ node ���͵�ָ�����

// ������ʾ�˵�
void myMenu()
{
	printf(" * * * * * * * * * ��     �� * * * * * * * * *\n");
	printf("     1 ����ѧ����¼           2 ɾ��ѧ����¼                    \n");
	printf("     3 ��ѯѧ����¼           4 �޸�ѧ����¼                    \n");
	printf("     5 ͳ��ѧ������           6 ��ʾѧ����¼                    \n");
	printf("     7 �˳�ϵͳ                                   \n");
	printf(" * * * * * * * * * * * * * * * * * * * * * * *\n");
}

void inputStudent(Link l)
{
	printf("�������µ�ѧ��ѧ�ţ�");
	scanf("%s", l->data.studentNo);
	printf("�������µ�ѧ��������");
	scanf("%s", l->data.studentName);

	// ÿ���´����Ľ��� next �򶼳�ʼ��Ϊ NULL
	l->next = NULL;
}

void inputStudentNo(char s[], char no[])
{
	printf("������Ҫ%s��ѧ��ѧ��:", s);
	scanf("%s", no);
}

void displayNode(Link head)
{
	// ��д���룬���ݴ�������� head ͷָ�룬ɨ��������ʾ���нڵ����Ϣ
	Link p = head->next;
	while (p != NULL)
	{
		printf("������%s ѧ�ţ�%s\n", p->data.studentName, p->data.studentNo);
		p = p->next;
	}
}

/* ����ѧ����¼ */
bool addNode(Link head)
{
	Link p, q;  // p��q �������һǰһ��
	Link node; // node ָ��ָ���´����Ľ��
	node = (Link)malloc(sizeof(Node));
	inputStudent(node);

	q = head;
	p = head->next; // pָ��head����ĵ�һ����Ч���
	if (head->next == NULL)
		// ����Ϊ��ʱ
		head->next = node;
	else
	{
		// ѭ�����������е����н��
		while (p != NULL) {
			if (atoi(node->data.studentNo) < atoi(p->data.studentNo))
			{
				// ���node����ѧ�ű�p����ѧ��С�������p��ǰ�棬��ɲ������ǰ�˳��ӳ���
				q->next = node;
				node->next = p;
				return true;
			}
			else
			{
				// ���node����ѧ�ű�p�ڵ��ѧ�Ŵ󣬼�������ƶ�ָ�루��Ȼ����p��qһǰһ��
				q = p;
				p = p->next;
			}
		}
		// ���û����ǰ�˳�ѭ������˵��֮ǰû�в��룬��ô��ǰnode����ѧ�������ֵ����ʱ��������������
		q->next = node;
	}
	return true;
}

bool deleteNode(Link head)
{
	// ���ո�����ѧ��ɾ��ѧ����¼�����ɾ���ɹ����� true�����û�ҵ�ѧ�ŷ��� false

	// ����Ҫ�����ѧ��
	char no[NO_LENGTH];
	if (!flag1)
		inputStudentNo("ɾ��", no);
	else
		inputStudentNo("�޸�", no);

	if (head == NULL || head->next == NULL) // ������û������
		return false;
	Link p = head->next; // ��ʼ����p��q ����ָ��һǰһ��
	Link q = head;
	while (p != NULL)
	{
		if (atoi(p->data.studentNo) == atoi(no)) // �ҵ�ѧ��Ϊ no �Ľ�㣬ɾ�������㣬����ǰ����
		{
			q->next = p->next;
			free(p);
			return true;
		}
		else // q ��ѧ�Ų����� no������������
		{
			q = p;
			p = p->next;
		}
	}
	// ���ѭ�������ˣ�˵��û���ҵ�ѧ�ź� no ��ȵĽ��
	return false;
}

bool queryNode(Link head)
{
	// ���ո�����ѧ�Ų�ѯѧ����¼�������ѯ�ɹ����� true�����û�ҵ�ѧ�ŷ��� false

	// ����Ҫ�����ѧ��
	char no[NO_LENGTH];
	inputStudentNo("��ѯ", no);

	Link p = head->next;
	while (p != NULL)
	{
		if (atoi(p->data.studentNo) == atoi(no))
			return true; // �ҵ�����ǰ���� true
		p = p->next;
	}

	// ���ѭ�������ˣ�˵��û���ҵ�
	return false;
}

bool modifyNode(Link head)
{
	// ���ո�����ѧ���ҵ�ѧ����¼�ڵ㣬����޸ĳɹ����� true�����û�ҵ�ѧ�ŷ��� false
	flag1 = 1;
	// ����Ҫ�����ѧ��
	bool flag = deleteNode(head);
	if (flag == 0)
	{
		flag1 = 0;
		return false;
	}
	else
	{
		flag1 = 0;
		addNode(head);
	}
}

int countNode(Link head)
{
	//ͳ��ѧ��������ɨ������ͳ�ƽڵ���������ؽڵ���
	Link p;
	int count = 0;
	p = head->next;

	while (p != NULL)
	{
		p = p->next;
		count++;
	}
	return count; // ע�� count �ĳ�ʼ���ͷ���ֵ֮��Ĺ�ϵ

}

void clearLink(Link head)
{
	Link q, p;
	// ���������� free ���ɾ���������� malloc ����������еĽڵ�
	while (head)
	{
		Link q = head;
		head = head->next;
		free(q);
	}
}

int main()
{
	int select;
	int count;
	Link head; // ��������

	// ���� head ͷ��㣬����������� head ָ��ͷ��㣬ͷ��� data ����û�����ݣ����������������������
	head = (Link)malloc(sizeof(Node));
	head->next = NULL;

	while (1)
	{
		myMenu();
		printf("\n���������ѡ��(1-7):"); // ��ʾ��ʾ��Ϣ
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			// ����ѧ����¼
			if (addNode(head))
				printf("�ɹ�����һ��ѧ����¼��\n\n");
			break;
		case 2:
			// ɾ��ѧ����¼
			if (deleteNode(head))
				printf("�ɹ�ɾ��һ��ѧ����¼��\n\n");
			else
				printf("û���ҵ�Ҫɾ����ѧ����㡣\n\n");
			break;
		case 3:
			// ��ѯѧ����¼
			if (queryNode(head))
				printf("�ɹ��ҵ�ѧ����¼��\n\n");
			else
				printf("û���ҵ�Ҫ��ѯ��ѧ����㡣\n\n");
			break;
		case 4:
			// �޸�ѧ����¼
			if (modifyNode(head))
				printf("�ɹ��޸�һ��ѧ����¼��\n\n");
			else
				printf("û���ҵ�Ҫ�޸ĵ�ѧ����㡣\n\n");
			break;
		case 5:
			// ͳ��ѧ������
			count = countNode(head);
			printf("ѧ������Ϊ��%d\n\n", count);
			break;
		case 6:
			// ��ʾѧ����¼
			displayNode(head);
			break;
		case 7:
			// �˳�ǰ��������е����н��
			clearLink(head);
			return 0;
		default:
			printf("���벻��ȷ��Ӧ������ 1-7 ֮�������\n\n");
			break;
		}
	}
	return 0;
}
