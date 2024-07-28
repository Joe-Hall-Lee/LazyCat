void selectSort(int r[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int index = i;
		int min = i + 1;
		for (int j = i + 1; j < n; j++) // 找到无序区最小的数的下标
		{
			if (r[j] < r[min])
				min = j;
			if (min != i) // 无序区最小的记录作为有序区的第 i 个记录
			{
				int temp = min;
				min = i;
				i = temp;
			}
		}
	}
}
