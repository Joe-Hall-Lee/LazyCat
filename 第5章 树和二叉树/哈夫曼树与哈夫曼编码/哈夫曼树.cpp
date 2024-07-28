typedef struct element
{
	int weight;
	int lchild, rchild, parent;
}HTNode;

void select(HTNode* HT, int m, int& s1, int& s2) // ���� m �������ѡ����С�� 2 ��
{
	int i; // ���±�Ϊ 1 ��λ�ÿ�ʼ���� 
	int min1 = 1000;
	int min2 = 1000; // �涨һ���ر����� 

	for (i = 1; i <= m; i++)
	{
		if (HT[i].parent == -1 && min1 > HT[i].weight)
		{
			min1 = HT[i].weight;
			s1 = i;
		}
	}
	for (i = 1; i <= m; i++)
	{
		if (i != s1 && HT[i].parent == 0 && HT[i].weight < min2) // ע����� i != s1 ��� min 
		{
			min2 = HT[i].weight;
			s2 = i;
		}
	}
}

void HuffmanTree(HTNode huffTree[], int w[], int n)
{
	int i1, i2;
	for (int i = 0; i < 2 * n - 1; i++) // ��ʼ�����н�����ĿΪ -1
	{
		huffTree[i].parent = -1;
		huffTree[i].lchild = -1;
		huffTree[i].rchild = -1;
	}
	for (int i = 0; i < n; i++) // ��ʼ��ǰ n ������Ȩֵ
		huffTree[i].weight = w[i];
	for (int k = n; k < 2 * n - 1; k++) // ������������
	{
		select(huffTree, k, i1, i2); // �ҵ� parent Ϊ -1 ����С�ʹ�С�Ľ��
		huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
		huffTree[i1].parent = k;
		huffTree[i2].parent = k;
		huffTree[k].lchild = i1;
		huffTree[k].rchild = i2;
	}
}