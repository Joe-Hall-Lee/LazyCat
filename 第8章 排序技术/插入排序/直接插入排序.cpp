void insertSort(int r[], int n)
{
	int i, j;
	for (i = 2; i <= n; i++)
	{
		r[0] = r[i];
		j = i - 1;
		while (r[0] < r[j])
		{
			r[j + 1] = r[j];
			j--;
		}
		r[j + 1] = r[0];
	}
}
