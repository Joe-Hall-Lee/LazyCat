#pragma once
#ifndef STACK_H
#define STACK_H

const int MAX_SIZE = 100; // ����ջ���ֵ����
template<class DataType>
class Stack
{
private:
	DataType* data; // ���ԣ����Ա�
	int size; // ���ԣ���ջ��ʵ�ʴ�С
	int top; // ���ԣ�ջ��
public:
	Stack(); // ���캯��
	Stack(int s); // �вι��캯��
	~Stack(); // ��������
	void push(DataType ch); // ��Ա��������ջ
	DataType pop(); // ��Ա��������ջ������ջ��Ԫ��
	DataType getTop(); // ��Ա���������ջ��Ԫ�أ�����ջ��
	bool isEmpty(); // ��Ա������ջ�Ƿ�Ϊ��
	bool isFull(); // ��Ա������ջ�Ƿ���
	void setNull(); // ����ջΪ��
	class Full {};
	class Empty {};
};

// Ϊ��֤ģ������������� cpp �ļ���ʹ�ã���Ҫ��Դ�ļ���ĩβ��ʽ��ʵ������Ҫ�õİ汾���� int��char�����൱��Ϊÿ�����͵�ģ�嶨����һ������
typedef Stack<char> CharStack;
typedef Stack<int> IntStack;
typedef Stack<double> DoubleStack;

#endif
