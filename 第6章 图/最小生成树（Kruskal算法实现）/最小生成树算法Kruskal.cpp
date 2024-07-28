#include <iostream>
using namespace std;

typedef int dataType;
const int MaxVertex = 10;
const int MaxEdge = 100;
struct EdgeType
{
	int from, to; // 边依附的两个顶点
	int weight; // 边上的权值
};
struct EdgeGraph
{
	dataType vertex[MaxVertex]; // 存放图顶点的数据
	EdgeType edge[MaxEdge]; // 存放边的数组
	int vertexNum, edgeNum; // 图的顶点数和边数
};

int findRoot(int parent[], int v)
{
	int t = v;
	while (parent[t] > -1)
		t = parent[t]; // 求顶点 t 上的双亲直到根结点
	return t;
}

void outputMST(EdgeType e)
{
	cout << "(" << e.from << ", " << e.to << ")" << endl;
}

void Kruskal(EdgeGraph G)
{
	int i, num, vex1, vex2, * parent;
	parent = new int[G.vertexNum];
	for (i = 0; i < G.vertexNum; i++)
		parent[i] = -1;
	for (num = 0, i = 0; i < G.edgeNum; i++)
	{
		vex1 = findRoot(parent, G.edge[i].from); // 找到所在生成树的根结点
		vex2 = findRoot(parent, G.edge[i].to); // 找到所在生成树的根结点
		if (vex1 != vex2) // 找到两个根结点不相同，不会构成环
		{
			// 输出加入的边，格式：(edge[i].from, edge[i].to)
			outputMST(G.edge[i]);
			parent[vex2] = vex1; // 合并生成树
			num++;
			if (num == G.vertexNum - 1) // 循环了“图的顶点数 - 1”次，提前返回
				return;
		}
	}
}
