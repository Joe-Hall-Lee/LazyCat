#include "Stack.h"
#include <iostream>
using namespace std;

template<class DataType>
Stack<DataType>::Stack() // ���캯��
{
	size = MAX_SIZE;
	top = -1;
	data = new DataType[MAX_SIZE];
}

template<class DataType>
Stack<DataType>::Stack(int s) // �вι��캯��
{
	size = s;
	top = -1;
	data = new DataType[size];
}

template<class DataType>
Stack<DataType>::~Stack() // ��������
{
	delete[] data;
}

template<class DataType>
void Stack<DataType>::push(DataType ch)// ��Ա��������ջ
{
	if (isFull())
		throw Stack<DataType>::Full();
	else
		data[++top] = ch;
}

template<class DataType>
DataType Stack<DataType>::pop() // ��Ա��������ջ������ջ��Ԫ��
{
	if (isEmpty())
		throw Stack<DataType>::Empty();
	else
		return data[top--];
}

template<class DataType>
DataType Stack<DataType>::getTop() // ��Ա���������ջ��Ԫ�أ�����ջ��
{
	if (!isEmpty())
		return data[top];
}

template<class DataType>
bool Stack<DataType>::isEmpty() // ��Ա������ջ�Ƿ�Ϊ��
{
	if (top == -1)
		return true;
	else
		return false;
}

template<class DataType>
bool Stack<DataType>::isFull() // ��Ա������ջ�Ƿ���
{
	if (top + 1 == size)
		return true;
	else
		return false;
}

template<class DataType>
void Stack<DataType>::setNull() // ����ջΪ��
{
	top = -1;
}

// �� cpp �ļ�����ʽ�ӵ�����Ҫʹ�õ�ģ����ʵ��
template class Stack<char>;
template class Stack<double>;
template class Stack<int>;