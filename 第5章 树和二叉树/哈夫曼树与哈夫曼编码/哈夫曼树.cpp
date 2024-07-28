typedef struct element
{
	int weight;
	int lchild, rchild, parent;
}HTNode;

void select(HTNode* HT, int m, int& s1, int& s2) // 从这 m 个数里边选择最小的 2 个
{
	int i; // 从下标为 1 的位置开始计数 
	int min1 = 1000;
	int min2 = 1000; // 规定一个特别大的数 

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
		if (i != s1 && HT[i].parent == 0 && HT[i].weight < min2) // 注意这个 i != s1 标记 min 
		{
			min2 = HT[i].weight;
			s2 = i;
		}
	}
}

void HuffmanTree(HTNode huffTree[], int w[], int n)
{
	int i1, i2;
	for (int i = 0; i < 2 * n - 1; i++) // 初始化所有结点的项目为 -1
	{
		huffTree[i].parent = -1;
		huffTree[i].lchild = -1;
		huffTree[i].rchild = -1;
	}
	for (int i = 0; i < n; i++) // 初始化前 n 个结点的权值
		huffTree[i].weight = w[i];
	for (int k = n; k < 2 * n - 1; k++) // 构建哈夫曼树
	{
		select(huffTree, k, i1, i2); // 找到 parent 为 -1 的最小和次小的结点
		huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
		huffTree[i1].parent = k;
		huffTree[i2].parent = k;
		huffTree[k].lchild = i1;
		huffTree[k].rchild = i2;
	}
}