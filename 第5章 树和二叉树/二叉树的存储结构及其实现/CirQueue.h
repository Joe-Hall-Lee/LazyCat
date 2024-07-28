#pragma once
typedef char DataType;
const int QUEUESIZE = 100;
class CirQueue
{
private:
	DataType* data; // 指向队列存储空间
	int front; // 队首下标
	int rear; // 队尾下标
	int mSize; // 存放队列的数组的大小
public:
	CirQueue(); // 建立缺省长度（QUEUESIZE）的队列
	CirQueue(int size); // 建立长度为 size 的队列
	~CirQueue(); // 清空队列，释放内存
	bool enQueue(DataType item); // 入队
	bool deQueue(DataType* item); // 出队
	bool getQueue(DataType* item); // 读取队头元素，但不删除
	bool isEmpty(); // 判断队列是否为空
	bool isFull(); // 判断队列是否为满
	void clearQueue(); // 清空队列
	void displayQueue(); // 显示队列内容
	int queueLength(); // 获取队列元素个数
};
