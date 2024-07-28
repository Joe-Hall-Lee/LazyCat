#include "MGraph.h"
MGraph::MGraph(DataType v[], int n, int e)
{
	int i, j;
	vertexNum = n;
	arcNum = e;
	for (i = 0; i < vertexNum; i++)
		vertex[i] = v[i];
	for (i = 0; i < vertexNum; i++) // 初始化邻接矩阵
	{
		for (j = 0; j < vertexNum; j++)
			arc[i][j] = 0;
	}
	for (i = 0; i < arcNum; i++) // 依次输入每一条边
	{
		cin >> i >> j; // 输入边依附的两个顶点的编号
		arc[i][j] = 1; // 置有边标志
		arc[j][i] = 1;
	}
}