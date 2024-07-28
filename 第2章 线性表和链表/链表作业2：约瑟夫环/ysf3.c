/* ����������������ʵ�ַ�ʽ */
/* ����洢��һ�����ӵ�λ�ã���ʶΪ -1 ��Ϊ�˳��ĺ��ӣ���ʶΪ -2 ��Ϊ��Ч�Ĵ洢�� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	int n, m; // n ���Ӹ�������������m�˳�
	int number; // ��¼ʣ��ĺ��Ӹ���
	int count; // count ����ǰ�ı���
	int i, pos, prior;
	while (~scanf("%d%d", &n, &m))
	{
		if (n == 0 || m == 0)
			return 0;

		int monkey[301] = { 0 }; // ����洢��һ�����ӵ�λ�ã���ʶΪ -1 ��Ϊ�˳��ĺ���
		// ��ʼ�����飬����洢��һ�����ӵ��±�
		for (i = 0; i < n - 1; i++)
			monkey[i] = i + 1;
		monkey[i] = 0; // �±�Ϊ n - 1 ��Ԫ�ص��¸����Ϊ 0���γ�ѭ������
		// monkey[i + 1] = 2; // ��������Χ��Ԫ�ر�ʶΪ -2��������ٵ�ʱ�������ڴ�

		number = n;
		pos = 0;
		prior = n - 1;
		count = 1;
		while (number > 1) // Ҳ���Բ���Ҫ number ������ֱ�ӽ��˳���������Ϊ prior != pos
		{
			if (count != m)
			{
				prior = pos; // prior ���� pos ����һ�������±�
				pos = monkey[pos]; // pos�ƶ�����һ����Ч�����±�
				count++;
			}
			else
			{
				monkey[prior] = monkey[pos]; // �������ӹ�ϵ
				monkey[pos] = -1; // ���ӳ��֣���ʶΪ -1
				pos = monkey[prior]; // pos �ƶ�����һ����Ч�����±�
				number--; // ���Ӹ��� -1
				count = 1;
			}
		}
		// �ҳ���Ч�ĺ��Ӳ����
		printf("%d\n", pos + 1);
	}
	return 0;
}
