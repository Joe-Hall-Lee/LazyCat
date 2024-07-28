#pragma once
#ifndef STACK_H
#define STACK_H

const int MAX_SIZE = 100; // 定义栈最大值常量
template<class DataType>
class Stack
{
private:
	DataType* data; // 属性：线性表
	int size; // 属性：堆栈的实际大小
	int top; // 属性：栈顶
public:
	Stack(); // 构造函数
	Stack(int s); // 有参构造函数
	~Stack(); // 析构函数
	void push(DataType ch); // 成员函数：入栈
	DataType pop(); // 成员函数：出栈并返回栈顶元素
	DataType getTop(); // 成员函数：获得栈顶元素（不出栈）
	bool isEmpty(); // 成员函数：栈是否为空
	bool isFull(); // 成员函数：栈是否满
	void setNull(); // 设置栈为空
	class Full {};
	class Empty {};
};

// 为保证模板类可以在其它 cpp 文件中使用，需要在源文件的末尾显式地实例化想要用的版本（如 int，char），相当于为每个类型的模板定义了一个类型
typedef Stack<char> CharStack;
typedef Stack<int> IntStack;
typedef Stack<double> DoubleStack;

#endif
