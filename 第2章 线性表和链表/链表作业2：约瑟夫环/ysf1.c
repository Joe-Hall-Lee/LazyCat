/* ����һ����ѭ������ʵ�� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
struct node
{
	int data;
	struct node* next;
};
int main1()
{
	int n, m; // n ���Ӹ������������� m �˳�
	int i;
	int answer[100]; // answer ����ÿ�εĴ𰸣����ͬ�����
	int count = 0; // count ����������Ŀ�𰸵��±�
	struct node* head, * tail, * p, * q; // p ָ��ǰ����Ľ�㣬q ����ָ���� p ָ��ָ���ǰһ����㡣

	// ����ͷ��㣬Ϊ���� debug ���٣�����������Ϊ -1
	head = (struct node*)malloc(sizeof(struct node));
	head->data = -1;
	head->next = NULL;

	while (1)
	{
		scanf("%d%d", &n, &m);
		if (n == 0 || m == 0)
		{
			free(head);
			break;
		}
		else
		{
			tail = head;
			for (i = 0; i < n; i++)
			{
				// ����β�巨����ѭ�������� tail ָ��ָ�����һ�����
				p = (struct node*)malloc(sizeof(struct node));
				p->data = i + 1; // ��д�������
				tail->next = p; // �嵽β��
				p->next = head->next; // ������ next ��ָ���һ����Ч��㣬�γ�ѭ������
				tail = p; // tail �ƶ������һ����㣬Ϊ��һ�β�����׼��
			}
			p = head->next;
			q = tail; // p ����ǰ��ʱ�����һ�����������ǰ�̽��
			i = 1;
			while (p != q) // p��q ����һǰһ��һ��������������˵��ֻʣһ�������
			{
				if (i == m)
				{
					// �ѵ�ǰ����������ɾ��
					q->next = q->next->next;
					free(p);
					// ��p�ƶ�����һ����Ч�Ľ���ϣ�i = 1 ���¿�ʼ����
					p = q->next;
					i = 1;
				}
				else
				{
					// q��q ��������ƶ�һ����㣬���� q ���� p ��ǰ��
					q = p;
					p = p->next;
					// ������ 1
					i++;
				}
			}
			// head->next = q; // ǰ��ɾ�����ʱ�������ֻʣ��������ʱ���п�����������������������Ŀ�����������Բ�Ҫ
			answer[count] = p->data;
			count++;
			free(p);
			head->next = NULL; // �����Ѿ���գ�ֻ��ͷ����ˣ���ͷ���� next ��ֵΪ NULL����Ȼ���Ǳ���ģ�ȴ��һ����ϰ��
		}
	}
	for (i = 0; i < count; i++)
		printf("%d\n", answer[i]);
	return 0;
}
