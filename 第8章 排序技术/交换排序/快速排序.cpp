int partition(int a[], int first, int end)
{
	int i = first;
	int j = end;
	while (i < j)
	{
		while (i < j && a[i] <= a[j])
			j--;
		if (i < j) // 由于 a[i] > a[j] 退出前面的循环，则交换，并调整 i
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
		}
		while (i < j && a[i] <= a[j])
			i++;
		if (i < j) // 由于 a[i] > a[j] 退出前面的循环，则交换，并调整 j
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			j--;
		}
		return i; // i == j 时，返回轴值
	}
}

void quickSort(int r[], int first, int end)
{
	int pos = partition(r, first, end); // 一次划分
	quickSort(r, first, pos - 1); // 对前一个子序列进行快速排序
	quickSort(r, pos + 1, end); // 对后一个子序列进行快速排序
}
