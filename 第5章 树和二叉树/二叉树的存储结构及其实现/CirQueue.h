#pragma once
typedef char DataType;
const int QUEUESIZE = 100;
class CirQueue
{
private:
	DataType* data; // ָ����д洢�ռ�
	int front; // �����±�
	int rear; // ��β�±�
	int mSize; // ��Ŷ��е�����Ĵ�С
public:
	CirQueue(); // ����ȱʡ���ȣ�QUEUESIZE���Ķ���
	CirQueue(int size); // ��������Ϊ size �Ķ���
	~CirQueue(); // ��ն��У��ͷ��ڴ�
	bool enQueue(DataType item); // ���
	bool deQueue(DataType* item); // ����
	bool getQueue(DataType* item); // ��ȡ��ͷԪ�أ�����ɾ��
	bool isEmpty(); // �ж϶����Ƿ�Ϊ��
	bool isFull(); // �ж϶����Ƿ�Ϊ��
	void clearQueue(); // ��ն���
	void displayQueue(); // ��ʾ��������
	int queueLength(); // ��ȡ����Ԫ�ظ���
};
