void selectSort(int r[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int index = i;
		int min = i + 1;
		for (int j = i + 1; j < n; j++) // �ҵ���������С�������±�
		{
			if (r[j] < r[min])
				min = j;
			if (min != i) // ��������С�ļ�¼��Ϊ�������ĵ� i ����¼
			{
				int temp = min;
				min = i;
				i = temp;
			}
		}
	}
}
