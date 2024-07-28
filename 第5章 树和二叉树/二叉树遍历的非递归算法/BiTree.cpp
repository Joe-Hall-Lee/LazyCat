#include "BiTree.h"
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

struct element
{
	BiNode* ptr;
	int flag; // 1 ��ʾ�� 1 �γ�ջ��2��ʾ�� 2 �γ�ջ
};
void visit(DataType c)
{
	cout << c << endl;
}

typedef int Status;
typedef struct
{
	SElemType* base; // ջ��ָ��
	SElemType* top; // ջ��ָ��
	int stacksize; // ջ�����������
}SqStack;

Status InitStack(SqStack& S) // ����һ����ջ
{
	S.base = new SElemType[MAXSIZE];
	if (!S.base)
		exit(OVERFLOW); // �洢����ʧ��
	S.top = S.base; // ջ��ָ�����ջ��ָ��
	S.stacksize = MAXSIZE;
	return OK;
}
Status StackEmpty(SqStack S) // ��ջΪ�գ�����TRUE�����򷵻�FALSE
{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

Status Push(SqStack& S, SElemType e)
{
	if (S.top - S.base == S.stacksize) // ջ��
		return ERROR;
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack& S, SElemType& e) // ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
{
	if (S.top == S.base) // �ȼ���if (StackEmpty(S))
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
	while (p != NULL || !StackEmpty(s)) // ��pΪ����ջҲΪ��ʱ�˳�ѭ��
	{
		while (p != NULL)
		{
			visit(p->data); // ���ʸ����
			Push(s, p); // ��ָ�� p �Ľ��ѹ��ջ��
			p = p->lchild; // ����������
		}
		if (!StackEmpty(s)) // ջ��Ϊ��
		{
			Pop(s, p); // ������ջ
			p = p->rchild; // ����������
		}
	}
}

void BiTree::inOrder()
{
	SqStack s;
	InitStack(s);
	BiNode* p = root;
	while (p != NULL || !StackEmpty(s)) // �� p Ϊ����ջҲΪ��ʱ�˳�ѭ��
	{
		while (p != NULL)
		{
			Push(s, p); // ��ָ�� p �Ľ��ѹ��ջ��
			p = p->lchild; // ����������
		}
		if (!StackEmpty(s)) // ջ��Ϊ��
		{
			Pop(s, p); // ������ջ
			visit(p->data); // ���ʸ����
			p = p->rchild; // ����������
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
	while (p != NULL || !StackEmpty(s)) // ���� p Ϊ����ջҲΪ��ʱ�˳�ѭ��
	{
		if (p != NULL) // ��һ����ջ������������
		{
			elem.ptr = p;
			elem.flag = 1; // ��� flag Ϊ 1����ʾ������һ����ջ
			Push(s, elem); // ��һ����ջ
			p = p->lchild; // ��������
		}
		else
		{
			Pop(s, elem); // ��ջ
			p = elem.ptr; // p ָ��ǰҪ����Ľ��
			if (elem.flag == 1) // flag == 1 �����Σ�˵��ֻ���ʹ�������������Ҫ��������������
			{
				elem.flag = 2; // ���� flag Ϊ 2����ʾ�����ڶ�����ջ
				Push(s, elem); // �ڶ�����ջ
				p = p->rchild; // �����Һ���
			}
			else // flag == 2 �����Σ���ʾ�������������ʹ���
			{
				visit(p->data); // ���ʸý��������ֵ
				p = NULL; // ���ʺ�p ��Ϊ�գ�ȷ���´�ѭ��ʱ������ջ�����˵���һ����
			}
		}
	}
}