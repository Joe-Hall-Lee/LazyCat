#include "MGraph.h"
MGraph::MGraph(DataType v[], int n, int e)
{
	int i, j;
	vertexNum = n;
	arcNum = e;
	for (i = 0; i < vertexNum; i++)
		vertex[i] = v[i];
	for (i = 0; i < vertexNum; i++) // ��ʼ���ڽӾ���
	{
		for (j = 0; j < vertexNum; j++)
			arc[i][j] = 0;
	}
	for (i = 0; i < arcNum; i++) // ��������ÿһ����
	{
		cin >> i >> j; // �������������������ı��
		arc[i][j] = 1; // ���б߱�־
		arc[j][i] = 1;
	}
}