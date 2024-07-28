#include "Stack.h"
#include <iostream>
using namespace std;

template<class DataType>
Stack<DataType>::Stack() // 构造函数
{
	size = MAX_SIZE;
	top = -1;
	data = new DataType[MAX_SIZE];
}

template<class DataType>
Stack<DataType>::Stack(int s) // 有参构造函数
{
	size = s;
	top = -1;
	data = new DataType[size];
}

template<class DataType>
Stack<DataType>::~Stack() // 析构函数
{
	delete[] data;
}

template<class DataType>
void Stack<DataType>::push(DataType ch)// 成员函数：入栈
{
	if (isFull())
		throw Stack<DataType>::Full();
	else
		data[++top] = ch;
}

template<class DataType>
DataType Stack<DataType>::pop() // 成员函数：出栈并返回栈顶元素
{
	if (isEmpty())
		throw Stack<DataType>::Empty();
	else
		return data[top--];
}

template<class DataType>
DataType Stack<DataType>::getTop() // 成员函数：获得栈顶元素（不出栈）
{
	if (!isEmpty())
		return data[top];
}

template<class DataType>
bool Stack<DataType>::isEmpty() // 成员函数：栈是否为空
{
	if (top == -1)
		return true;
	else
		return false;
}

template<class DataType>
bool Stack<DataType>::isFull() // 成员函数：栈是否满
{
	if (top + 1 == size)
		return true;
	else
		return false;
}

template<class DataType>
void Stack<DataType>::setNull() // 设置栈为空
{
	top = -1;
}

// 在 cpp 文件中显式子的声明要使用的模板类实例
template class Stack<char>;
template class Stack<double>;
template class Stack<int>;