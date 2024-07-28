#include <iostream>
using namespace std;

typedef struct element
{
	int weight;
	int lchild, rchild, parent;
}HTNode;

void huffmanCoding(HTNode huffTree[], char* huffCode[], int n)
{
	char* temp = new char[n]; // ���幤���ռ䣬�洢��ʱ�����ı��봮
	temp[n - 1] = '\0';
	for (int i = 0; i < n; i++) // ���������������飬���ɹ���������
	{
		int start = n - 1;
		int pos = i; // pos ��¼���ڴ���ĵ�ǰλ��
		int parent = huffTree[i].parent; // �ҳ������
		while (parent != -1)
		{
			if (huffTree[parent].lchild == pos) // �жϵ�ǰ�����ӻ����Һ���
				temp[--start] = '0';
			else
				temp[--start] = '1';
			pos = parent; // ��ǰλ���ƶ��������
			parent = huffTree[parent].parent; // ���¸����
		}
		huffCode[i] = new char[n - start]; // ��������������ʵ����Ҫ���ڴ�ռ�
		strcpy(huffCode[i], &temp[start]); // ��ʱ�洢�Ĺ���������洢�� huffCode ��
	}
	delete[]temp; // �ͷŹ����ռ�
}
