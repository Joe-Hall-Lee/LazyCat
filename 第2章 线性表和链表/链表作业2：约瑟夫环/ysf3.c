/* 方法三：数组链接实现方式 */
/* 数组存储下一个猴子的位置，标识为 -1 的为退出的猴子，标识为 -2 的为无效的存储区 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	int n, m; // n 猴子个数，报数数到m退出
	int number; // 记录剩余的猴子个数
	int count; // count 代表当前的报数
	int i, pos, prior;
	while (~scanf("%d%d", &n, &m))
	{
		if (n == 0 || m == 0)
			return 0;

		int monkey[301] = { 0 }; // 数组存储下一个猴子的位置，标识为 -1 的为退出的猴子
		// 初始化数组，数组存储下一个猴子的下标
		for (i = 0; i < n - 1; i++)
			monkey[i] = i + 1;
		monkey[i] = 0; // 下标为 n - 1 的元素的下个序号为 0，形成循环链表
		// monkey[i + 1] = 2; // 将超过范围的元素标识为 -2，方便跟踪的时候看数据内存

		number = n;
		pos = 0;
		prior = n - 1;
		count = 1;
		while (number > 1) // 也可以不需要 number 计数，直接将退出条件设置为 prior != pos
		{
			if (count != m)
			{
				prior = pos; // prior 保存 pos 的上一个结点的下标
				pos = monkey[pos]; // pos移动到下一个有效结点的下标
				count++;
			}
			else
			{
				monkey[prior] = monkey[pos]; // 更改链接关系
				monkey[pos] = -1; // 猴子出局，标识为 -1
				pos = monkey[prior]; // pos 移动到下一个有效结点的下标
				number--; // 猴子个数 -1
				count = 1;
			}
		}
		// 找出有效的猴子并输出
		printf("%d\n", pos + 1);
	}
	return 0;
}
