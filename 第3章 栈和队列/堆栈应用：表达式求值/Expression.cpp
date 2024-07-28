#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
typedef char SElemType;
typedef struct
{
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

Status InitStack(SqStack& S) // 初始化
{
	S.base = (SElemType*)malloc(sizeof(SElemType) * MAXSIZE);
	if (!S.base)
		exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}

Status Push(SqStack& S, SElemType e) // 入栈
{
	if (S.top - S.base == S.stacksize)
		return ERROR; // 栈满
	*S.top++ = e; // 元素 e 压入栈顶，栈顶指针加 1
	return OK;
}
Status Pop(SqStack& S, SElemType& e) // 出栈
{
	if (S.top == S.base) // 栈空
		return ERROR;
	e = *--S.top; // 栈顶指针减 1，将栈顶元素赋给 e
	return OK;
}
SElemType GetTop(SqStack S) // 取栈顶元素
{
	if (S.top != S.base) // 栈非空
		return *(S.top - 1); // 返回栈顶元素的值，栈顶指针不变
}
int In(SElemType e) // 判断读入字符是否为运算符
{
	if (e == '+' || e == '-' || e == '*' || e == '/' || e == '(' || e == ')' || e == '#')
		return 1; // 是
	else
		return 0; // 不是
}
SElemType Precede(SElemType a, SElemType b) // 比较运算符的优先级
{
	SElemType f;
	if (a == '+' || a == '-')
	{
		if (b == '+' || b == '-' || b == ')' || b == '#')
			f = '>';
		else if (b == '*' || b == '/' || b == '(')
			f = '<';
	}
	else if (a == '*' || a == '/')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#')
			f = '>';
		else if (b == '(')
			f = '<';
	}
	else if (a == '(')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
			f = '<';
		else if (b == ')')
			f = '=';
	}
	else if (a == ')')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#')
			f = '>';
	}
	else if (a == '#')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
			f = '<';
		else if (b == '#')
			f = '=';
	}
	return f;
}

SElemType Operate(SElemType a, SElemType theta, SElemType b) // 运算
{
	SElemType c;
	a = a - '0';
	b = b - '0';
	if (theta == '+')
		c = a + b + '0';
	else if (theta == '-')
		c = a - b + '0';
	else if (theta == '*')
		c = a * b + '0';
	else if (theta == '/')
		c = a / b + '0';
	return c;
}

int EvaluateExpression()
{
	SqStack OPND, OPTR;
	char ch, a, b, theta, x;
	InitStack(OPND); // 寄存操作数和运算结果
	InitStack(OPTR); // 寄存运算符
	Push(OPTR, '#'); // 将 '#' 压入操作符 OPTR 栈
	ch = getchar();
	while (ch != '#' || GetTop(OPTR) != '#')
	{
		if (!In(ch))
		{
			Push(OPND, ch);
			ch = getchar();
		}
		else
		{
			switch (Precede(GetTop(OPTR), ch)) // 比较栈顶元素和 ch 的优先关系
			{
			case '<':
				Push(OPTR, ch); // 栈顶元素优先级低，则压入操作符栈
				ch = getchar();
				break;
			case '>': // 栈顶元素优先级高，取出一个运算符，两个操作数，并计算
				Pop(OPTR, theta);
				Pop(OPND, b);
				Pop(OPND, a);
				Push(OPND, Operate(a, theta, b)); // 将计算结果压入操作数栈
				break;
			case '=':
				Pop(OPTR, x);
				ch = getchar();
				break;
			}
		}
	}
	return GetTop(OPND) - '0';
}

int main()
{
	printf("请输入算术表达式,并以 # 结束\n");
	printf("结果是: %d\n", EvaluateExpression());
	return 0;
}