/*
	用邻接表实现 AOE 网的关键路径算法

	可直接粘贴的输入：
9 11
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4

*/

#include <iostream>
#include <stdio.h>
using namespace std;

const int MAX_VERTEX = 30;  // 图的最大顶点数

struct ArcNode  /* 边表 */
{
	int weight;  // 增加权值分量，代表活动时间
	int adjvex;
	ArcNode* next;
};

struct VertexNode  /* 顶点表 */
{
	int in;  // 增加入度字段
	char vertex;
	ArcNode* firstEdge;
};

class ALGraph
{
private:
	VertexNode* adjList;  // 邻接表
	int vertexNum, arcNum;
	int* ve, * vl;  // ve数组是事件最早发生时间，vl事件最迟发生时间(数组长度跟顶点数相等)
public:
	ALGraph(char v[], int n, int e);
	~ALGraph();
	void inputEdges();
	bool setEdge(int vi, int vj, int weight);
	void displayData();

	bool TopologicalSort(int result[], int& count);  // 拓扑排序
	bool CriticalPath();   // 求关键路径
};

ALGraph::ALGraph(char v[], int n, int e)
{
	vertexNum = n;
	arcNum = e;
	adjList = new VertexNode[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		// 输入顶点信息，初始化顶点表
		adjList[i].in = 0;  // 增加 in 的初始化
		adjList[i].vertex = v[i];
		adjList[i].firstEdge = NULL;
	}
	ve = new int[vertexNum];
	vl = new int[vertexNum];
}
ALGraph ::~ALGraph()
{
	ArcNode* p, * pre;
	// 遍历顶点表数组，把顶点表指向的所有边结点删除
	for (int i = 0; i < vertexNum; i++)
	{
		p = adjList[i].firstEdge;
		adjList[i].firstEdge = NULL;
		while (p)
		{
			pre = p;
			p = p->next;
			delete pre;
		}
	}
	delete[] adjList;
	delete[] ve;
	delete[] vl;
}

void ALGraph::inputEdges()
{
	cout << "请输入两个事件顶点编号(范围0-" << vertexNum - 1 << ")和活动时间:" << endl;
	for (int i = 0; i < arcNum; i++) {
		// 输入边的信息存储在边表中
		int vi, vj, weight;
		cin >> vi >> vj >> weight;   // 输入边依附的两个顶点的编号
		if (!setEdge(vi, vj, weight))
		{
			cout << "输入的顶点编号超过范围或者相等，需要重新输入" << endl;
			i--;
		}
	}
}

bool ALGraph::setEdge(int vi, int vj, int weight)
{
	// 修改 setEdge 函数，把 vj 顶点表中的入度 + 1
	ArcNode* s;
	if (vi >= 0 && vi < vertexNum && vj >= 0 && vj < vertexNum && vi != vj)
	{
		// 创建一个边结点vj
		s = new ArcNode;
		s->adjvex = vj;
		s->weight = weight;
		// 把边结点vj插入到顶点表vi项的邻接表中，成为第一个结点
		s->next = adjList[vi].firstEdge;
		adjList[vi].firstEdge = s;
		// vj顶点表中的入度+1
		adjList[vj].in++;
		return true;
	}
	else
		return false;
}

void ALGraph::displayData()
{
	ArcNode* p;
	cout << "输出图的存储情况：" << endl;
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "顶点" << adjList[i].vertex << "的入度为：" << adjList[i].in << "，从这个顶点发出的的边为：" << endl;
		p = adjList[i].firstEdge;
		if (!p)
			cout << "没有。" << endl;
		while (p)
		{
			cout << "<" << i << "," << p->adjvex << ">" << p->weight << endl;
			p = p->next;
		}
	}
}

/*
	TopologicalSort 用于实现拓扑排序
	参数：result 用来保存处理过的拓扑排序顶点；count 用来保存处理过的拓扑排序顶点的个数
	功能：进行拓扑排序，将找到的拓扑顶点序号存入 result 数组（result可以看成一个栈，count 可以看成是栈顶指针），在拓扑排序的同时计算 ve 数组的值（事件最早发生时间）
*/
bool ALGraph::TopologicalSort(int result[], int& count)
{
	int stack[MAX_VERTEX];  // 把顶点对应的下标压入堆栈

	int top = -1;
	int inVex;  // 用来保存从堆栈中弹出的顶点（下标），代表一个边的起始顶点
	int outVex;  // 遍历一个顶点的所有邻接边结点时,用 outVex 暂存当前处理的顶点，代表一个边的终止顶点]
	ArcNode* p;

	// 初始化事件最早发生时间 ve 数组
	for (int i = 0; i < vertexNum; i++)
		ve[i] = 0;

	//遍历顶点表，把入度为 0 的压栈
	for (int i = 0; i < vertexNum; i++)
	{
		if (adjList[i].in == 0)
			stack[++top] = i;
	}

	count = 0;  // count 用来统计处理过的顶点个数
	while (top != -1)
	{
		inVex = stack[top--];  // 出栈
		result[count] = inVex;
		count++;

		// 找出当前处理的顶点的所有出边
		p = adjList[inVex].firstEdge;
		while (p)
		{
			outVex = p->adjvex;
			adjList[outVex].in--;
			if (adjList[outVex].in == 0)  // 把入度为0的边压栈
				stack[++top] = outVex;  // 入栈
			if (ve[inVex] + p->weight > ve[outVex])  // 求ve数组的值
				ve[outVex] = ve[inVex] + p->weight;
			p = p->next;
		}
	}

	//判断拓扑排序是否正确
	if (count == vertexNum)
		return true;
	else
		return false;
}
// CriticalPath 用于求关键路径，首先调用 TopologicalSort 函数检查是否是一个没有环的图

bool ALGraph::CriticalPath()
{
	int resultStack[MAX_VERTEX];  // 存储拓扑排序结果序列(存储下标)
	int resultTop;  // 拓扑排序有效顶点个数(栈顶指针)
	ArcNode* p;
	int i, count;
	int inVex, outVex;  //inVex，outVex，分别代表一条边的起点顶点号和终点顶点号

	if (!TopologicalSort(resultStack, count))
		return false;

	// 输出拓扑排序的顶点处理顺序
	cout << "拓补排序的顶点处理顺序为：";
	for (i = 0; i < count; i++)
		cout << resultStack[i] << " ";
	cout << endl;
	// 输出ve数组的值
	for (i = 0; i < count; i++)
		cout << "ve[" << i << "]=" << ve[i] << endl;

	resultTop = count - 1;  // 把数组看成栈，则指向栈顶的 resultTop 为顶点数 - 1
	inVex = resultStack[resultTop--];  // 汇点先出栈

	// 初始化 vl 数组为结束点的 ve 值，这个 ve 值是最大的（因为后面 vl 是求 min 值）
	for (i = 0; i < vertexNum; i++)
		vl[i] = ve[inVex];

	// 栈不为空时，按拓补排序求各个顶点的 vl 值
	while (resultTop != -1)
	{
		inVex = resultStack[resultTop--];  // 出栈
		p = adjList[inVex].firstEdge;
		while (p)
		{
			outVex = p->adjvex;
			if (vl[inVex] > vl[outVex] - p->weight)
				vl[inVex] = vl[outVex] - p->weight;
			p = p->next;
		}
	}
	cout << "vl数组的值为：" << endl;
	for (i = 0; i < count; i++)
		cout << "vl[" << i << "]=" << vl[i] << endl;

	// 完成关键路径的求解
	cout << "输出关键路径：" << endl;
	// 从上往下扫描顶点表，处理每个顶点的边表，计算 ee 和 el 的值（ee 活动最早开始时间，el 活动最晚开始时间）
	for (inVex = 0; inVex < vertexNum; inVex++)
	{
		p = adjList[inVex].firstEdge;
		while (p)
		{
			outVex = p->adjvex;
			int weight = p->weight;
			int ee = ve[inVex];  // 活动最早开始时间 e，与当前边起点的 ve 值相等
			int el = vl[outVex] - weight;  // 活动最晚开始时间，为当前边终点的 vl 值 - 边的权值

			if (ee == el)
				cout << "<" << inVex << "," << outVex << ">" << weight << "  ";
			p = p->next;
		}
	}
	return true;
}

int main()
{
	char vertex[MAX_VERTEX];
	int num, edge;

	cout << "请输入顶点个数和边的个数：";
	cin >> num >> edge;
	for (int i = 0; i < num; i++)
		vertex[i] = i + '0';

	ALGraph graph(vertex, num, edge);
	graph.inputEdges();
	graph.displayData();

	if (!graph.CriticalPath())
		cout << "这个图有回路，不能求关键路径。";

	// main 函数调用结束后，会自动调用析构函数，对图的数据以及 ve、vl 数组进行释放。

	return 0;
}