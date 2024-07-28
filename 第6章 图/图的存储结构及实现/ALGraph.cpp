#include "ALGraph.h"
ALGraph::ALGraph(DataType v[], int n, int e)
{
	int i, j;
	vertexNum = n;
	arcNum = e;
	for (i = 0; i < vertexNum; i++)
	{
		// ���붥����Ϣ����ʼ�������
		adjList[i].vertex = v[i];
		adjList[i].firstEdge = NULL;
	}
	for (i = 0; i < arcNum; i++)
	{
		// ����ߵ���Ϣ�洢�ڱ߱���
		cin >> i >> j;  // �������������������ı��
		ArcNode* s = new ArcNode;
		s->adjvex = j;
		s->next = adjList[i].firstEdge;
		adjList[i].firstEdge = s;
	}
}