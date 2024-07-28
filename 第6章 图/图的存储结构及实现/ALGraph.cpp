#include "ALGraph.h"
ALGraph::ALGraph(DataType v[], int n, int e)
{
	int i, j;
	vertexNum = n;
	arcNum = e;
	for (i = 0; i < vertexNum; i++)
	{
		// 输入顶点信息，初始化顶点表
		adjList[i].vertex = v[i];
		adjList[i].firstEdge = NULL;
	}
	for (i = 0; i < arcNum; i++)
	{
		// 输入边的信息存储在边表中
		cin >> i >> j;  // 输入边依附的两个顶点的编号
		ArcNode* s = new ArcNode;
		s->adjvex = j;
		s->next = adjList[i].firstEdge;
		adjList[i].firstEdge = s;
	}
}