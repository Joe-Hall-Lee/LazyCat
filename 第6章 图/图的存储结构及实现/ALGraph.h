#pragma once
#include <iostream>
using namespace std;

const int MAX_VERTEX = 10;  // ͼ����󶥵���

typedef int DataType;
struct ArcNode /* �߱� */
{
	int adjvex;
	ArcNode* next;
};
struct VertexNode /* ����� */
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
