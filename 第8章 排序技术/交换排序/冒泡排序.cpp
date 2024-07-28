void bubbleSort(int r[], int n)
{
	int exchange = n - 1;
	while (exchange)
	{
		int bound = exchange;
		exchange = 0;
		for (int j = 0; j < bound; j++)
		{
			if (r[j] > r[j + 1])
			{
				int temp = r[j];
				r[j] = r[j + 1];
				r[j + 1] = temp;
				exchange = j;
			}
		}
	}
}
