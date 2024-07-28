#include "CirQueue.h"

bool CirQueue::enQueue(DataType x)
{
	if (isFull())
		return false;
	rear = (rear + 1) % QUEUESIZE;
	data[rear] = x;
	return true;
}

bool CirQueue::deQueue(DataType* item)
{
	if (isEmpty())
		return false;
	front = (front + 1) % QUEUESIZE;

	*item = data[front];
	return true;
}

bool CirQueue::getQueue(DataType* item)
{
	if (isEmpty())
		return false;
	int i = (front + 1) % QUEUESIZE;
	*item = data[i];
	return true;
}
