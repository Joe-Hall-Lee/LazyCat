void sift(int r[], int k, int end)
{
	// Ҫɸѡ���ı��Ϊ k���������һ�����ı��Ϊ end
	int i = k;
	int j = 2 * i;
	while (j <= end) // ɸѡ��û�н��е�Ҷ��
	{
		if (j < end && r[j] < r[j + 1]) // ��ɸѡ�����������Ҷ��ʱΪ��
			j++; // j Ϊ���Һ����нϴ���
		if (r[i] < r[j])
		{
			r[0] = r[i];
			r[i] = r[j];
			r[j] = r[0]; // �� r[0] ��Ϊ��ʱ����ʵ�� r[i] �� r[j] �Ľ���
		}
		i = j;
		j = 2 * i;
	}
}

void hepSort(int r[], int n)
{
	int k;
	for (k = n / 2; k >= 1; k--) // ������
		sift(r, k, n);
	for (k = 1; k < n; k++)
	{
		r[0] = r[n - k + 1];
		r[n - k + 1] = r[1];
		r[1] = r[n - k + 1]; // ���߶Ѷ����������� r[0] ��ʱ��Ԫ
		sift(r, 1, n - k); // �ؽ���
	}
}
