#include "BiTree.h"
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

struct element
{
	BiNode* ptr;
	int flag; // 1 表示第 1 次出栈，2表示第 2 次出栈
};
void visit(DataType c)
{
	cout << c << endl;
}

typedef int Status;
typedef struct
{
	SElemType* base; // 栈底指针
	SElemType* top; // 栈顶指针
	int stacksize; // 栈可用最大容量
}SqStack;

Status InitStack(SqStack& S) // 构造一个空栈
{
	S.base = new SElemType[MAXSIZE];
	if (!S.base)
		exit(OVERFLOW); // 存储分配失败
	S.top = S.base; // 栈顶指针等于栈底指针
	S.stacksize = MAXSIZE;
	return OK;
}
Status StackEmpty(SqStack S) // 若栈为空，返回TRUE；否则返回FALSE
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

Status Push(SqStack& S, SElemType e)
{
	if (S.top - S.base == S.stacksize) // 栈满
		return ERROR;
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack& S, SElemType& e) // 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR
{
	if (S.top == S.base) // 等价于if (StackEmpty(S))
		return ERROR;
	e = *--S.top;
	return OK;
}

typedef BiNode* SElemType;

void BiTree::preOrder()
{
	SqStack s;
	InitStack(s);
	BiNode* p = root;
	while (p != NULL || !StackEmpty(s)) // 当p为空且栈也为空时退出循环
	{
		while (p != NULL)
		{
			visit(p->data); // 访问根结点
			Push(s, p); // 将指针 p 的结点压入栈中
			p = p->lchild; // 遍历左子树
		}
		if (!StackEmpty(s)) // 栈不为空
		{
			Pop(s, p); // 根结点出栈
			p = p->rchild; // 遍历右子树
		}
	}
}

void BiTree::inOrder()
{
	SqStack s;
	InitStack(s);
	BiNode* p = root;
	while (p != NULL || !StackEmpty(s)) // 当 p 为空且栈也为空时退出循环
	{
		while (p != NULL)
		{
			Push(s, p); // 将指针 p 的结点压入栈中
			p = p->lchild; // 遍历左子树
		}
		if (!StackEmpty(s)) // 栈不为空
		{
			Pop(s, p); // 根结点出栈
			visit(p->data); // 访问根结点
			p = p->rchild; // 遍历右子树
		}
	}
}

typedef element SElemType;
void BiTree::postOrder()
{
	SqStack s;
	InitStack(s);
	element elem;
	BiNode* p = root;
	while (p != NULL || !StackEmpty(s)) // 仅当 p 为空且栈也为空时退出循环
	{
		if (p != NULL) // 第一次入栈，访问左子树
		{
			elem.ptr = p;
			elem.flag = 1; // 标记 flag 为 1，表示即将第一次入栈
			Push(s, elem); // 第一次入栈
			p = p->lchild; // 访问左孩子
		}
		else
		{
			Pop(s, elem); // 出栈
			p = elem.ptr; // p 指向当前要处理的结点
			if (elem.flag == 1) // flag == 1 的情形，说明只访问过左子树，还需要继续访问右子树
			{
				elem.flag = 2; // 表明 flag 为 2，表示即将第二次入栈
				Push(s, elem); // 第二次入栈
				p = p->rchild; // 访问右孩子
			}
			else // flag == 2 的情形，表示左右子树均访问过了
			{
				visit(p->data); // 访问该结点数据域值
				p = NULL; // 访问后，p 赋为空，确保下次循环时继续出栈（回退到上一级）
			}
		}
	}
}