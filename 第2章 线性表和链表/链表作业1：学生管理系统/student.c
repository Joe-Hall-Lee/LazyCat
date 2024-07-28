#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

#define NO_LENGTH  20
#define NAME_LENGTH 110000

int flag1 = 0;
/* 定义学生结构体的数据结构 */
typedef struct Student
{
	char studentNo[20];
	char studentName[11];
};

/* 定义每条记录或结点的数据结构 */
typedef struct node
{
	struct Student data; // 数据域
	struct node* next; // 指针域
}Node, * Link; // Node 为 node 类型的别名，Link为 node 类型的指针别名

// 定义提示菜单
void myMenu()
{
	printf(" * * * * * * * * * 菜     单 * * * * * * * * *\n");
	printf("     1 增加学生记录           2 删除学生记录                    \n");
	printf("     3 查询学生记录           4 修改学生记录                    \n");
	printf("     5 统计学生人数           6 显示学生记录                    \n");
	printf("     7 退出系统                                   \n");
	printf(" * * * * * * * * * * * * * * * * * * * * * * *\n");
}

void inputStudent(Link l)
{
	printf("请输入新的学生学号：");
	scanf("%s", l->data.studentNo);
	printf("请输入新的学生姓名：");
	scanf("%s", l->data.studentName);

	// 每个新创建的结点的 next 域都初始化为 NULL
	l->next = NULL;
}

void inputStudentNo(char s[], char no[])
{
	printf("请输入要%s的学生学号:", s);
	scanf("%s", no);
}

void displayNode(Link head)
{
	// 填写代码，根据传入的链表 head 头指针，扫描链表显示所有节点的信息
	Link p = head->next;
	while (p != NULL)
	{
		printf("姓名：%s 学号：%s\n", p->data.studentName, p->data.studentNo);
		p = p->next;
	}
}

/* 增加学生记录 */
bool addNode(Link head)
{
	Link p, q;  // p、q 两个结点一前一后
	Link node; // node 指针指向新创建的结点
	node = (Link)malloc(sizeof(Node));
	inputStudent(node);

	q = head;
	p = head->next; // p指向head后面的第一个有效结点
	if (head->next == NULL)
		// 链表为空时
		head->next = node;
	else
	{
		// 循环访问链表中的所有结点
		while (p != NULL) {
			if (atoi(node->data.studentNo) < atoi(p->data.studentNo))
			{
				// 如果node结点的学号比p结点的学号小，则插在p的前面，完成插入后，提前退出子程序
				q->next = node;
				node->next = p;
				return true;
			}
			else
			{
				// 如果node结点的学号比p节点的学号大，继续向后移动指针（依然保持p、q一前一后）
				q = p;
				p = p->next;
			}
		}
		// 如果没能提前退出循环，则说明之前没有插入，那么当前node结点的学号是最大值，此时插在链表的最后面
		q->next = node;
	}
	return true;
}

bool deleteNode(Link head)
{
	// 按照给定的学号删除学生记录，如果删除成功返回 true，如果没找到学号返回 false

	// 输入要处理的学号
	char no[NO_LENGTH];
	if (!flag1)
		inputStudentNo("删除", no);
	else
		inputStudentNo("修改", no);

	if (head == NULL || head->next == NULL) // 若链表没有数据
		return false;
	Link p = head->next; // 初始化。p、q 两个指针一前一后
	Link q = head;
	while (p != NULL)
	{
		if (atoi(p->data.studentNo) == atoi(no)) // 找到学号为 no 的结点，删除这个结点，并提前返回
		{
			q->next = p->next;
			free(p);
			return true;
		}
		else // q 的学号不等于 no，则继续向后找
		{
			q = p;
			p = p->next;
		}
	}
	// 如果循环结束了，说明没有找到学号和 no 相等的结点
	return false;
}

bool queryNode(Link head)
{
	// 按照给定的学号查询学生记录，如果查询成功返回 true，如果没找到学号返回 false

	// 输入要处理的学号
	char no[NO_LENGTH];
	inputStudentNo("查询", no);

	Link p = head->next;
	while (p != NULL)
	{
		if (atoi(p->data.studentNo) == atoi(no))
			return true; // 找到则提前返回 true
		p = p->next;
	}

	// 如果循环结束了，说明没有找到
	return false;
}

bool modifyNode(Link head)
{
	// 按照给定的学号找到学生记录节点，如果修改成功返回 true，如果没找到学号返回 false
	flag1 = 1;
	// 输入要处理的学号
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
	//统计学生人数，扫描链表统计节点个数，返回节点数
	Link p;
	int count = 0;
	p = head->next;

	while (p != NULL)
	{
		p = p->next;
		count++;
	}
	return count; // 注意 count 的初始化和返回值之间的关系

}

void clearLink(Link head)
{
	Link q, p;
	// 遍历链表，用 free 语句删除链表中用 malloc 建立起的所有的节点
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
	Link head; // 定义链表

	// 建立 head 头结点，在这个程序中 head 指向头结点，头结点 data 部分没有内容，其后续结点才有真正的数据
	head = (Link)malloc(sizeof(Node));
	head->next = NULL;

	while (1)
	{
		myMenu();
		printf("\n请输入你的选择(1-7):"); // 显示提示信息
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			// 增加学生记录
			if (addNode(head))
				printf("成功插入一个学生记录。\n\n");
			break;
		case 2:
			// 删除学生记录
			if (deleteNode(head))
				printf("成功删除一个学生记录。\n\n");
			else
				printf("没有找到要删除的学生结点。\n\n");
			break;
		case 3:
			// 查询学生记录
			if (queryNode(head))
				printf("成功找到学生记录。\n\n");
			else
				printf("没有找到要查询的学生结点。\n\n");
			break;
		case 4:
			// 修改学生记录
			if (modifyNode(head))
				printf("成功修改一个学生记录。\n\n");
			else
				printf("没有找到要修改的学生结点。\n\n");
			break;
		case 5:
			// 统计学生人数
			count = countNode(head);
			printf("学生人数为：%d\n\n", count);
			break;
		case 6:
			// 显示学生记录
			displayNode(head);
			break;
		case 7:
			// 退出前清除链表中的所有结点
			clearLink(head);
			return 0;
		default:
			printf("输入不正确，应该输入 1-7 之间的数。\n\n");
			break;
		}
	}
	return 0;
}
