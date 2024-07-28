#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct polynomial
{
	int coefficient; // 系数
	int exp; // 指数
	struct polynomial* next;
}*Link, Node;

void inputPoly(Link head); // 用于从控制台读入链表的函数
void print(Link head); // 打印链表用的函数
bool insert(Link head, int coefficient, int exp); // 向链表插入一个元素的函数
void combin2List(Link heada, Link headb, Link headab); // 合并两个链表
void clearLink(Link head);

int main()
{
	Link headA, headB; // 两个多项式的头指针
	Link headAB; // 合并后的多项式的头指针

	/* 链表的初始化 */
	headA = (Link)malloc(sizeof(Node));
	headA->next = NULL;
	headB = (Link)malloc(sizeof(Node));
	headB->next = NULL;
	headAB = (Link)malloc(sizeof(Node));
	headAB->next = NULL;

	printf("请输入第一个多项式的系数和指数，以 (0 0) 结束：\n");
	inputPoly(headA);
	printf("第一个");
	print(headA);
	printf("请输入第二个多项式的系数和指数，以 (0 0) 结束：\n");
	inputPoly(headB);
	printf("第二个");
	print(headB);

	combin2List(headA, headB, headAB);
	printf("合并后");
	print(headAB);
	clearLink(headA);
	clearLink(headB);
	clearLink(headAB);

	return 0;
}

/* 输入二项式数据的函数 */
/*
	这个函数用来输入二项式，给用户合理的提示，读入用户输入的系数和指数。
	调用函数 insert，将用户输入的二项式的一项插入到链表中。、
*/
void inputPoly(Link head)
{
	int coefficient, exp; // 系数和指数
	printf("请输入系数和指数（如：\"2 3\"表示2x^3）：");
	scanf("%d %d", &coefficient, &exp);
	while (coefficient != 0 || exp != 0) // 连续输入多个系数和指数
	{
		insert(head, coefficient, exp); // 调函数输入多项式
		printf("请输入系数和指数：");
		scanf("%d %d", &coefficient, &exp);
	}
}

/*
	向多项式链表中插入元素的函数
	int coefficient  一个多项式项的系数
	int exp  一个多项式项的幂
*/
bool insert(Link head, int coefficient, int exp)
{
	Link node; // node 指针指向新创建的结点
	Link q, p; // q、p 两个结点一前一后
	p = head->next;
	q = head;
	// 创建一个新结点

	node = (Link)malloc(sizeof(Node));
	node->coefficient = coefficient;
	node->exp = exp;
	node->next = NULL;

	if (head->next == NULL) // 空表，插第 1 个
	{
		head->next = node;
		node->next = NULL;
		return true;
	}
	else
	{
		while (p != NULL) // 循环访问链表中的所有结点
		{
			// 如果 node 结点的指数比 p 结点的指数大，则插在 p 的前面，完成插入后，提前退出
			if (exp > p->exp)
			{
				q->next = node;
				node->next = p;
				return true;
			}

			// 如果 node 结点的指数和 p 结点的指数相等，则合并这个多项式结点，提前退出
			else if (exp == p->exp)
			{
				p->coefficient += coefficient;
				free(node);
				return true;
			}

			// 如果 node 结点的指数比 p 结点的指数小，继续向后移动指针（依然保持 p、q 一前一后）
			else
			{
				q = p;
				p = p->next;
			}
		}

		// 如果退出循环是当前指针 p 移动到链表结尾，则说明之前没有插入，那么当前 node 结点的指数值是最大值，此时插在链表的最后面
		q->next = node;
		node->next = NULL;
		return true;
	}
	return true;
}

/**
	打印多项式链表的函数
*/
/*
	① 通过指针访问链表
	② 多重条件语句嵌套
	③ 数字转换为字符串函数 itoa
	④ 标志是否为第一个结点的 flag 设置
	⑤ 字符串连接函数 strcat
	⑥ 字符串清空函数 memset。memset(item, 0, 20); 清空长 20 的字符串 item
*/
void print(Link head)
{
	Link p; // 指向链表要输出的结点
	printf("多项式如下：\n");
	p = head->next;

	if (p == NULL)
	{
		printf("多项式为空\n");
		return;
	}

	// 不是空表
	char item[20] = ""; // 要打印的当前多项式的一项
	char number[7] = ""; // 暂时存放系数转换成的字符串

	bool isFirstItem = true; // 标志是否为第一个结点的 flag

	// 打印结点
	do
	{
		memset(item, 0, 20); // 清空字符串item
		// 如果是第一项，不要打加号

		itoa(p->coefficient, number, 10);
		if (p->coefficient == 0)
		{
			p = p->next;
			continue;
		}
		else
		{
			// 如果不是第一项，且系数为正数，要打加号
			if (isFirstItem != true && p->coefficient > 0)
				strcat(item, "+");

			// 如果系数为1，不用打系数
			if (p->coefficient == 1) {}
			// 系数为-1，打印负号
			else if (p->coefficient == -1)
				strcat(item, "-");
			// 如果系数不为 1 或 -1，打印系数
			else if (p->coefficient != 0)
				strcat(item, number);
			// 如果指数为 1，不打指数，否则打指数
			if (p->exp == 1)
				strcat(item, "x");
			// 如果指数为 0，直接打系数不用打 x^ 和指数
			else if (p->exp == 0)
			{
				// 如果指数是-1或1，需要打1出来，不能只打符号
				if (p->coefficient == 1 || p->coefficient == -1)
					strcat(item, "1");
			}

			// 指数不为0
			else
			{
				strcat(item, "x^");
				strcat(item, itoa(p->exp, number, 10));
			}
		}
		printf("%s", item);// 打印当前结点代表的项
		p = p->next; // 指向下个结点
		isFirstItem = false; // 标志不是第一项了
	} while (p != NULL);
	printf("\n");
	return;
}

/**
	合并两个有序链表 a、b 到链表 ab
	heada、headb、headab 分别为链表 a、b、ab 的头指针
*/
void combin2List(Link heada, Link headb, Link headab)
{
	Link pa, pb; // 指向 a、b 链表的指针
	pa = heada->next;
	pb = headb->next;

	while (pa != NULL && pb != NULL)
	{
		// 如果指数 a > 指数 b，a 结点插入 ab 链表，a 指针后移
		if (pa->exp > pb->exp)
		{
			insert(headab, pa->coefficient, pa->exp);
			pa = pa->next;
		}
		// 如果指数 a < 指数 b，b 结点插入 ab 链表，b 指针后移
		else if (pa->exp < pb->exp)
		{
			insert(headab, pb->coefficient, pb->exp);
			pb = pb->next;
		}
		// 如果指数 a == 指数b，a、b 系数相加，插入 ab 链表，a、b 指针后移
		else if (pa->exp == pb->exp)
		{
			int coefficient = pa->coefficient + pb->coefficient;
			insert(headab, coefficient, pa->exp);
			pa = pa->next;
			pb = pb->next;
		}


		// 如果 a、b 链表还有尾巴，将它加到 ab 链表后面
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

/* 将链表中所有的结点删除 */
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
