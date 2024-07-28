void sift(int r[], int k, int end)
{
	// 要筛选结点的编号为 k，堆中最后一个结点的编号为 end
	int i = k;
	int j = 2 * i;
	while (j <= end) // 筛选还没有进行到叶子
	{
		if (j < end && r[j] < r[j + 1]) // 当筛选结点中有左右叶子时为真
			j++; // j 为左右孩子中较大者
		if (r[i] < r[j])
		{
			r[0] = r[i];
			r[i] = r[j];
			r[j] = r[0]; // 把 r[0] 作为临时变量实现 r[i] 和 r[j] 的交换
		}
		i = j;
		j = 2 * i;
	}
}

void hepSort(int r[], int n)
{
	int k;
	for (k = n / 2; k >= 1; k--) // 初建堆
		sift(r, k, n);
	for (k = 1; k < n; k++)
	{
		r[0] = r[n - k + 1];
		r[n - k + 1] = r[1];
		r[1] = r[n - k + 1]; // 移走堆顶，交换利用 r[0] 临时单元
		sift(r, 1, n - k); // 重建堆
	}
}
