#pragma once
#include <iostream>
using namespace std;

const int MAX_VERTEX = 10;  // 图的最大顶点数
typedef char DataType;
class MGraph
{
private:
	DataType vertex[MAX_VERTEX];
	int arc[MAX_VERTEX][MAX_VERTEX];
	int vertexNum, arcNum;
public:
	MGraph(DataType v[], int n, int e);
	~MGraph();
	void DFSTraverse(int v);
	void BFSTraverse(int v);
};
