#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct polynomial
{
	int coefficient; // ϵ��
	int exp; // ָ��
	struct polynomial* next;
}*Link, Node;

void inputPoly(Link head); // ���ڴӿ���̨��������ĺ���
void print(Link head); // ��ӡ�����õĺ���
bool insert(Link head, int coefficient, int exp); // ���������һ��Ԫ�صĺ���
void combin2List(Link heada, Link headb, Link headab); // �ϲ���������
void clearLink(Link head);

int main()
{
	Link headA, headB; // ��������ʽ��ͷָ��
	Link headAB; // �ϲ���Ķ���ʽ��ͷָ��

	/* ����ĳ�ʼ�� */
	headA = (Link)malloc(sizeof(Node));
	headA->next = NULL;
	headB = (Link)malloc(sizeof(Node));
	headB->next = NULL;
	headAB = (Link)malloc(sizeof(Node));
	headAB->next = NULL;

	printf("�������һ������ʽ��ϵ����ָ������ (0 0) ������\n");
	inputPoly(headA);
	printf("��һ��");
	print(headA);
	printf("������ڶ�������ʽ��ϵ����ָ������ (0 0) ������\n");
	inputPoly(headB);
	printf("�ڶ���");
	print(headB);

	combin2List(headA, headB, headAB);
	printf("�ϲ���");
	print(headAB);
	clearLink(headA);
	clearLink(headB);
	clearLink(headAB);

	return 0;
}

/* �������ʽ���ݵĺ��� */
/*
	������������������ʽ�����û��������ʾ�������û������ϵ����ָ����
	���ú��� insert�����û�����Ķ���ʽ��һ����뵽�����С���
*/
void inputPoly(Link head)
{
	int coefficient, exp; // ϵ����ָ��
	printf("������ϵ����ָ�����磺\"2 3\"��ʾ2x^3����");
	scanf("%d %d", &coefficient, &exp);
	while (coefficient != 0 || exp != 0) // ����������ϵ����ָ��
	{
		insert(head, coefficient, exp); // �������������ʽ
		printf("������ϵ����ָ����");
		scanf("%d %d", &coefficient, &exp);
	}
}

/*
	�����ʽ�����в���Ԫ�صĺ���
	int coefficient  һ������ʽ���ϵ��
	int exp  һ������ʽ�����
*/
bool insert(Link head, int coefficient, int exp)
{
	Link node; // node ָ��ָ���´����Ľ��
	Link q, p; // q��p �������һǰһ��
	p = head->next;
	q = head;
	// ����һ���½��

	node = (Link)malloc(sizeof(Node));
	node->coefficient = coefficient;
	node->exp = exp;
	node->next = NULL;

	if (head->next == NULL) // �ձ���� 1 ��
	{
		head->next = node;
		node->next = NULL;
		return true;
	}
	else
	{
		while (p != NULL) // ѭ�����������е����н��
		{
			// ��� node ����ָ���� p ����ָ��������� p ��ǰ�棬��ɲ������ǰ�˳�
			if (exp > p->exp)
			{
				q->next = node;
				node->next = p;
				return true;
			}

			// ��� node ����ָ���� p ����ָ����ȣ���ϲ��������ʽ��㣬��ǰ�˳�
			else if (exp == p->exp)
			{
				p->coefficient += coefficient;
				free(node);
				return true;
			}

			// ��� node ����ָ���� p ����ָ��С����������ƶ�ָ�루��Ȼ���� p��q һǰһ��
			else
			{
				q = p;
				p = p->next;
			}
		}

		// ����˳�ѭ���ǵ�ǰָ�� p �ƶ��������β����˵��֮ǰû�в��룬��ô��ǰ node ����ָ��ֵ�����ֵ����ʱ��������������
		q->next = node;
		node->next = NULL;
		return true;
	}
	return true;
}

/**
	��ӡ����ʽ����ĺ���
*/
/*
	�� ͨ��ָ���������
	�� �����������Ƕ��
	�� ����ת��Ϊ�ַ������� itoa
	�� ��־�Ƿ�Ϊ��һ������ flag ����
	�� �ַ������Ӻ��� strcat
	�� �ַ�����պ��� memset��memset(item, 0, 20); ��ճ� 20 ���ַ��� item
*/
void print(Link head)
{
	Link p; // ָ������Ҫ����Ľ��
	printf("����ʽ���£�\n");
	p = head->next;

	if (p == NULL)
	{
		printf("����ʽΪ��\n");
		return;
	}

	// ���ǿձ�
	char item[20] = ""; // Ҫ��ӡ�ĵ�ǰ����ʽ��һ��
	char number[7] = ""; // ��ʱ���ϵ��ת���ɵ��ַ���

	bool isFirstItem = true; // ��־�Ƿ�Ϊ��һ������ flag

	// ��ӡ���
	do
	{
		memset(item, 0, 20); // ����ַ���item
		// ����ǵ�һ���Ҫ��Ӻ�

		itoa(p->coefficient, number, 10);
		if (p->coefficient == 0)
		{
			p = p->next;
			continue;
		}
		else
		{
			// ������ǵ�һ���ϵ��Ϊ������Ҫ��Ӻ�
			if (isFirstItem != true && p->coefficient > 0)
				strcat(item, "+");

			// ���ϵ��Ϊ1�����ô�ϵ��
			if (p->coefficient == 1) {}
			// ϵ��Ϊ-1����ӡ����
			else if (p->coefficient == -1)
				strcat(item, "-");
			// ���ϵ����Ϊ 1 �� -1����ӡϵ��
			else if (p->coefficient != 0)
				strcat(item, number);
			// ���ָ��Ϊ 1������ָ���������ָ��
			if (p->exp == 1)
				strcat(item, "x");
			// ���ָ��Ϊ 0��ֱ�Ӵ�ϵ�����ô� x^ ��ָ��
			else if (p->exp == 0)
			{
				// ���ָ����-1��1����Ҫ��1����������ֻ�����
				if (p->coefficient == 1 || p->coefficient == -1)
					strcat(item, "1");
			}

			// ָ����Ϊ0
			else
			{
				strcat(item, "x^");
				strcat(item, itoa(p->exp, number, 10));
			}
		}
		printf("%s", item);// ��ӡ��ǰ���������
		p = p->next; // ָ���¸����
		isFirstItem = false; // ��־���ǵ�һ����
	} while (p != NULL);
	printf("\n");
	return;
}

/**
	�ϲ������������� a��b ������ ab
	heada��headb��headab �ֱ�Ϊ���� a��b��ab ��ͷָ��
*/
void combin2List(Link heada, Link headb, Link headab)
{
	Link pa, pb; // ָ�� a��b �����ָ��
	pa = heada->next;
	pb = headb->next;

	while (pa != NULL && pb != NULL)
	{
		// ���ָ�� a > ָ�� b��a ������ ab ����a ָ�����
		if (pa->exp > pb->exp)
		{
			insert(headab, pa->coefficient, pa->exp);
			pa = pa->next;
		}
		// ���ָ�� a < ָ�� b��b ������ ab ����b ָ�����
		else if (pa->exp < pb->exp)
		{
			insert(headab, pb->coefficient, pb->exp);
			pb = pb->next;
		}
		// ���ָ�� a == ָ��b��a��b ϵ����ӣ����� ab ����a��b ָ�����
		else if (pa->exp == pb->exp)
		{
			int coefficient = pa->coefficient + pb->coefficient;
			insert(headab, coefficient, pa->exp);
			pa = pa->next;
			pb = pb->next;
		}


		// ��� a��b ������β�ͣ������ӵ� ab �������
		while (pa != NULL)
		{
			insert(headab, pa->coefficient, pa->exp);
			pa = pa->next;
		}
		while (pb != NULL)
		{
			insert(headab, pb->coefficient, pb->exp);
			pb = pb->next;
		}
		return;
	}
}

/* �����������еĽ��ɾ�� */
void clearLink(Link head)
{
	Link p, q;
	if (head == NULL)
		return;
	p = head->next;
	free(head);
	head = NULL;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	return;
}
