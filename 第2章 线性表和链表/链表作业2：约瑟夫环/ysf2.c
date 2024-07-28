/* 方法二：数组标志位实现方式 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main2()
{
	int n, m;  // n 猴子个数，报数数到 m 退出
	int number;  // 记录剩余的猴子个数
	int count = 1;  // count 代表当前的报数
	int i, pos;
	while (~scanf("%d%d", &n, &m))
	{
		if (n == 0 || m == 0)
			return 0;

		number = n;
		// monkey 数组存储猴子的编号和状态
		// 存储 -1 代表无效数组部分，0 代表退出的猴子，1 至 n + 1 代表还没退出的猴子代号
		int monkey[301] = { 0 };
		for (i = 0; i < n; i++)
			monkey[i] = i + 1;
		pos = 0;  // pos 控制当前处理的数组下标
		while (number > 1)
		{
			if (monkey[pos] > 0)
			{
				if (count != m)
				{
					count++;  // 报数+1
					pos = (pos + 1) % n;  // 当前处理的数组下标 + 1
				}
				else
				{
					monkey[pos] = 0;  // 标记为 0，设置当前猴子出局
					count = 1;  // 报数重新开始
					number--;  // 猴子个数 - 1
					pos = (pos + 1) % n;  // 当前处理的数组下标 + 1
				}
			}
			else
				pos = (pos + 1) % n;  // 当前处理的数组下标 + 1
		}
		for (i = 0; i < n; i++)
		{
			if (monkey[i] > 0)
				printf("%d\n", monkey[i]);
		}
	}

	return 0;
}
