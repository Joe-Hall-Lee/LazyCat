/* �������������־λʵ�ַ�ʽ */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main2()
{
	int n, m;  // n ���Ӹ������������� m �˳�
	int number;  // ��¼ʣ��ĺ��Ӹ���
	int count = 1;  // count ����ǰ�ı���
	int i, pos;
	while (~scanf("%d%d", &n, &m))
	{
		if (n == 0 || m == 0)
			return 0;

		number = n;
		// monkey ����洢���ӵı�ź�״̬
		// �洢 -1 ������Ч���鲿�֣�0 �����˳��ĺ��ӣ�1 �� n + 1 ����û�˳��ĺ��Ӵ���
		int monkey[301] = { 0 };
		for (i = 0; i < n; i++)
			monkey[i] = i + 1;
		pos = 0;  // pos ���Ƶ�ǰ����������±�
		while (number > 1)
		{
			if (monkey[pos] > 0)
			{
				if (count != m)
				{
					count++;  // ����+1
					pos = (pos + 1) % n;  // ��ǰ����������±� + 1
				}
				else
				{
					monkey[pos] = 0;  // ���Ϊ 0�����õ�ǰ���ӳ���
					count = 1;  // �������¿�ʼ
					number--;  // ���Ӹ��� - 1
					pos = (pos + 1) % n;  // ��ǰ����������±� + 1
				}
			}
			else
				pos = (pos + 1) % n;  // ��ǰ����������±� + 1
		}
		for (i = 0; i < n; i++)
		{
			if (monkey[i] > 0)
				printf("%d\n", monkey[i]);
		}
	}

	return 0;
}
