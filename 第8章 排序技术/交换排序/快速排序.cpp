int partition(int a[], int first, int end)
{
	int i = first;
	int j = end;
	while (i < j)
	{
		while (i < j && a[i] <= a[j])
			j--;
		if (i < j) // ���� a[i] > a[j] �˳�ǰ���ѭ�����򽻻��������� i
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
		}
		while (i < j && a[i] <= a[j])
			i++;
		if (i < j) // ���� a[i] > a[j] �˳�ǰ���ѭ�����򽻻��������� j
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			j--;
		}
		return i; // i == j ʱ��������ֵ
	}
}

void quickSort(int r[], int first, int end)
{
	int pos = partition(r, first, end); // һ�λ���
	quickSort(r, first, pos - 1); // ��ǰһ�������н��п�������
	quickSort(r, pos + 1, end); // �Ժ�һ�������н��п�������
}
