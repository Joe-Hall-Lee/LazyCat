/* 方法一：用循环链表实现 */
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
	int n, m; // n 猴子个数，报数数到 m 退出
	int i;
	int answer[100]; // answer 保存每次的答案，最后同意输出
	int count = 0; // count 用来控制题目答案的下标
	struct node* head, * tail, * p, * q; // p 指向当前处理的结点，q 总是指向在 p 指针指向的前一个结点。

	// 创建头结点，为方便 debug 跟踪，数据域设置为 -1
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
				// 采用尾插法构建循环链表，用 tail 指针指向最后一个结点
				p = (struct node*)malloc(sizeof(struct node));
				p->data = i + 1; // 填写猴子序号
				tail->next = p; // 插到尾部
				p->next = head->next; // 最后结点的 next 域指向第一个有效结点，形成循环链表
				tail = p; // tail 移动到最后一个结点，为下一次插入做准备
			}
			p = head->next;
			q = tail; // p 在最前面时，最后一个结点是它的前继结点
			i = 1;
			while (p != q) // p、q 总是一前一后，一旦它们相遇，则说明只剩一个结点了
			{
				if (i == m)
				{
					// 把当前结点从链表中删除
					q->next = q->next->next;
					free(p);
					// 将p移动到下一个有效的结点上，i = 1 重新开始报数
					p = q->next;
					i = 1;
				}
				else
				{
					// q、q 各自向后移动一个结点，其中 q 总在 p 的前面
					q = p;
					p = p->next;
					// 报数加 1
					i++;
				}
			}
			// head->next = q; // 前面删除结点时，当最后只剩两个结点的时候，有可能造成链表不完整，在这道题目中这条语句可以不要
			answer[count] = p->data;
			count++;
			free(p);
			head->next = NULL; // 链表已经清空，只有头结点了，将头结点的 next 域赋值为 NULL，虽然不是必需的，却是一个好习惯
		}
	}
	for (i = 0; i < count; i++)
		printf("%d\n", answer[i]);
	return 0;
}
