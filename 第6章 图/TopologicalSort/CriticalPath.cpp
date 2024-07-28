/*
	���ڽӱ�ʵ�� AOE ���Ĺؼ�·���㷨

	��ֱ��ճ�������룺
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

const int MAX_VERTEX = 30;  // ͼ����󶥵���

struct ArcNode  /* �߱� */
{
	int weight;  // ����Ȩֵ����������ʱ��
	int adjvex;
	ArcNode* next;
};

struct VertexNode  /* ����� */
{
	int in;  // ��������ֶ�
	char vertex;
	ArcNode* firstEdge;
};

class ALGraph
{
private:
	VertexNode* adjList;  // �ڽӱ�
	int vertexNum, arcNum;
	int* ve, * vl;  // ve�������¼����緢��ʱ�䣬vl�¼���ٷ���ʱ��(���鳤�ȸ����������)
public:
	ALGraph(char v[], int n, int e);
	~ALGraph();
	void inputEdges();
	bool setEdge(int vi, int vj, int weight);
	void displayData();

	bool TopologicalSort(int result[], int& count);  // ��������
	bool CriticalPath();   // ��ؼ�·��
};

ALGraph::ALGraph(char v[], int n, int e)
{
	vertexNum = n;
	arcNum = e;
	adjList = new VertexNode[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		// ���붥����Ϣ����ʼ�������
		adjList[i].in = 0;  // ���� in �ĳ�ʼ��
		adjList[i].vertex = v[i];
		adjList[i].firstEdge = NULL;
	}
	ve = new int[vertexNum];
	vl = new int[vertexNum];
}
ALGraph ::~ALGraph()
{
	ArcNode* p, * pre;
	// ������������飬�Ѷ����ָ������б߽��ɾ��
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
	cout << "�����������¼�������(��Χ0-" << vertexNum - 1 << ")�ͻʱ��:" << endl;
	for (int i = 0; i < arcNum; i++) {
		// ����ߵ���Ϣ�洢�ڱ߱���
		int vi, vj, weight;
		cin >> vi >> vj >> weight;   // �������������������ı��
		if (!setEdge(vi, vj, weight))
		{
			cout << "����Ķ����ų�����Χ������ȣ���Ҫ��������" << endl;
			i--;
		}
	}
}

bool ALGraph::setEdge(int vi, int vj, int weight)
{
	// �޸� setEdge �������� vj ������е���� + 1
	ArcNode* s;
	if (vi >= 0 && vi < vertexNum && vj >= 0 && vj < vertexNum && vi != vj)
	{
		// ����һ���߽��vj
		s = new ArcNode;
		s->adjvex = vj;
		s->weight = weight;
		// �ѱ߽��vj���뵽�����vi����ڽӱ��У���Ϊ��һ�����
		s->next = adjList[vi].firstEdge;
		adjList[vi].firstEdge = s;
		// vj������е����+1
		adjList[vj].in++;
		return true;
	}
	else
		return false;
}

void ALGraph::displayData()
{
	ArcNode* p;
	cout << "���ͼ�Ĵ洢�����" << endl;
	for (int i = 0; i < vertexNum; i++)
	{
		cout << "����" << adjList[i].vertex << "�����Ϊ��" << adjList[i].in << "����������㷢���ĵı�Ϊ��" << endl;
		p = adjList[i].firstEdge;
		if (!p)
			cout << "û�С�" << endl;
		while (p)
		{
			cout << "<" << i << "," << p->adjvex << ">" << p->weight << endl;
			p = p->next;
		}
	}
}

/*
	TopologicalSort ����ʵ����������
	������result �������洦������������򶥵㣻count �������洦������������򶥵�ĸ���
	���ܣ������������򣬽��ҵ������˶�����Ŵ��� result ���飨result���Կ���һ��ջ��count ���Կ�����ջ��ָ�룩�������������ͬʱ���� ve �����ֵ���¼����緢��ʱ�䣩
*/
bool ALGraph::TopologicalSort(int result[], int& count)
{
	int stack[MAX_VERTEX];  // �Ѷ����Ӧ���±�ѹ���ջ

	int top = -1;
	int inVex;  // ��������Ӷ�ջ�е����Ķ��㣨�±꣩������һ���ߵ���ʼ����
	int outVex;  // ����һ������������ڽӱ߽��ʱ,�� outVex �ݴ浱ǰ����Ķ��㣬����һ���ߵ���ֹ����]
	ArcNode* p;

	// ��ʼ���¼����緢��ʱ�� ve ����
	for (int i = 0; i < vertexNum; i++)
		ve[i] = 0;

	//��������������Ϊ 0 ��ѹջ
	for (int i = 0; i < vertexNum; i++)
	{
		if (adjList[i].in == 0)
			stack[++top] = i;
	}

	count = 0;  // count ����ͳ�ƴ�����Ķ������
	while (top != -1)
	{
		inVex = stack[top--];  // ��ջ
		result[count] = inVex;
		count++;

		// �ҳ���ǰ����Ķ�������г���
		p = adjList[inVex].firstEdge;
		while (p)
		{
			outVex = p->adjvex;
			adjList[outVex].in--;
			if (adjList[outVex].in == 0)  // �����Ϊ0�ı�ѹջ
				stack[++top] = outVex;  // ��ջ
			if (ve[inVex] + p->weight > ve[outVex])  // ��ve�����ֵ
				ve[outVex] = ve[inVex] + p->weight;
			p = p->next;
		}
	}

	//�ж����������Ƿ���ȷ
	if (count == vertexNum)
		return true;
	else
		return false;
}
// CriticalPath ������ؼ�·�������ȵ��� TopologicalSort ��������Ƿ���һ��û�л���ͼ

bool ALGraph::CriticalPath()
{
	int resultStack[MAX_VERTEX];  // �洢��������������(�洢�±�)
	int resultTop;  // ����������Ч�������(ջ��ָ��)
	ArcNode* p;
	int i, count;
	int inVex, outVex;  //inVex��outVex���ֱ����һ���ߵ���㶥��ź��յ㶥���

	if (!TopologicalSort(resultStack, count))
		return false;

	// �����������Ķ��㴦��˳��
	cout << "�ز�����Ķ��㴦��˳��Ϊ��";
	for (i = 0; i < count; i++)
		cout << resultStack[i] << " ";
	cout << endl;
	// ���ve�����ֵ
	for (i = 0; i < count; i++)
		cout << "ve[" << i << "]=" << ve[i] << endl;

	resultTop = count - 1;  // �����鿴��ջ����ָ��ջ���� resultTop Ϊ������ - 1
	inVex = resultStack[resultTop--];  // ����ȳ�ջ

	// ��ʼ�� vl ����Ϊ������� ve ֵ����� ve ֵ�����ģ���Ϊ���� vl ���� min ֵ��
	for (i = 0; i < vertexNum; i++)
		vl[i] = ve[inVex];

	// ջ��Ϊ��ʱ�����ز��������������� vl ֵ
	while (resultTop != -1)
	{
		inVex = resultStack[resultTop--];  // ��ջ
		p = adjList[inVex].firstEdge;
		while (p)
		{
			outVex = p->adjvex;
			if (vl[inVex] > vl[outVex] - p->weight)
				vl[inVex] = vl[outVex] - p->weight;
			p = p->next;
		}
	}
	cout << "vl�����ֵΪ��" << endl;
	for (i = 0; i < count; i++)
		cout << "vl[" << i << "]=" << vl[i] << endl;

	// ��ɹؼ�·�������
	cout << "����ؼ�·����" << endl;
	// ��������ɨ�趥�������ÿ������ı߱����� ee �� el ��ֵ��ee ����翪ʼʱ�䣬el �����ʼʱ�䣩
	for (inVex = 0; inVex < vertexNum; inVex++)
	{
		p = adjList[inVex].firstEdge;
		while (p)
		{
			outVex = p->adjvex;
			int weight = p->weight;
			int ee = ve[inVex];  // ����翪ʼʱ�� e���뵱ǰ������ ve ֵ���
			int el = vl[outVex] - weight;  // �����ʼʱ�䣬Ϊ��ǰ���յ�� vl ֵ - �ߵ�Ȩֵ

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

	cout << "�����붥������ͱߵĸ�����";
	cin >> num >> edge;
	for (int i = 0; i < num; i++)
		vertex[i] = i + '0';

	ALGraph graph(vertex, num, edge);
	graph.inputEdges();
	graph.displayData();

	if (!graph.CriticalPath())
		cout << "���ͼ�л�·��������ؼ�·����";

	// main �������ý����󣬻��Զ�����������������ͼ�������Լ� ve��vl ��������ͷš�

	return 0;
}