#include <iostream>
using namespace std;

typedef int dataType;
const int MaxVertex = 10;
const int MaxEdge = 100;
struct EdgeType
{
	int from, to; // ����������������
	int weight; // ���ϵ�Ȩֵ
};
struct EdgeGraph
{
	dataType vertex[MaxVertex]; // ���ͼ���������
	EdgeType edge[MaxEdge]; // ��űߵ�����
	int vertexNum, edgeNum; // ͼ�Ķ������ͱ���
};

int findRoot(int parent[], int v)
{
	int t = v;
	while (parent[t] > -1)
		t = parent[t]; // �󶥵� t �ϵ�˫��ֱ�������
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
		vex1 = findRoot(parent, G.edge[i].from); // �ҵ������������ĸ����
		vex2 = findRoot(parent, G.edge[i].to); // �ҵ������������ĸ����
		if (vex1 != vex2) // �ҵ���������㲻��ͬ�����ṹ�ɻ�
		{
			// �������ıߣ���ʽ��(edge[i].from, edge[i].to)
			outputMST(G.edge[i]);
			parent[vex2] = vex1; // �ϲ�������
			num++;
			if (num == G.vertexNum - 1) // ѭ���ˡ�ͼ�Ķ����� - 1���Σ���ǰ����
				return;
		}
	}
}
