#pragma once
#include <iostream>
using namespace std;

const int MAX_VERTEX = 10;  // 图的最大顶点数

typedef int DataType;
struct ArcNode /* 边表 */
{
	int adjvex;
	ArcNode* next;
};
struct VertexNode /* 顶点表 */
{
	DataType vertex;
	ArcNode* firstEdge;
};
class ALGraph
{
private:
	VertexNode adjList[MAX_VERTEX];
	int vertexNum, arcNum;
public:
	ALGraph(DataType v[], int n, int e);
	~ALGraph();
	void DFSTraverse(int v);
	void BFSTraverse(int v);
};
