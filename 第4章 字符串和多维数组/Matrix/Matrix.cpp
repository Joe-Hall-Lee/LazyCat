#include <iostream>
using namespace std;

#define MAX 100
#define ERROR 0
#define OK 1
typedef int Status; // 函数结果状态类型

typedef struct
{
	int row, col; // 三元组的行号、列号
	int item; // 三元组的值
} Triple;

// 定义 TripleMatrix 类，每个 TripleMatrix 对象访问一个矩阵的信息
class TripleMatrix
{
private:
	Triple data[MAX]; // 非零元三元组
	int mu, nu, num; // 矩阵的行数、列数和非零元个数
public:
	TripleMatrix();
	TripleMatrix(int m, int n); // 创建对象时，完成属性的初始化
	~TripleMatrix();
	Status setItem(int row, int col, int item); // 根据行号、列号、非零元，在尾部添加一个三元组
	int getItem(int row, int col); // 根据行号、列号，获得矩阵元素值
	void printMatrix(); // 按矩阵方式打印稀疏矩阵
	void printTriple(); // 打印三元组数组
	friend bool matrixAdd(TripleMatrix a, TripleMatrix b, TripleMatrix& result);
	friend bool matrixMulty(TripleMatrix a, TripleMatrix b, TripleMatrix& result);
};

TripleMatrix::TripleMatrix()
{
	// 初始化矩阵的行数、列数和非零元个数
	mu = nu = num = 0;
}

TripleMatrix::TripleMatrix(int m, int n)
{
	// 初始化矩阵的行数、列数和非零元个数
	mu = m;
	nu = n;
	num = 0;
}

TripleMatrix::~TripleMatrix()
{
}

// 根据行号、列号获得稀疏矩阵元素的值
int TripleMatrix::getItem(int row, int col)
{
	if (row > mu || col > nu) // 超过范围直接返回 0
		return 0;
	for (int i = 0; i < num; i++) // 遍历三元组
	{
		// 如果发现行列号匹配的三元组，则返回非零元值
		if (data[i].row == row && data[i].col == col)
			return data[i].item;
	}
	return 0;
}

/*
	这个成员函数往三元组中存入一个稀疏矩阵的一个元素。
	由于三元组是按行、列由小到大排序的，因此需要先找到需要插入的位置，
	然后考虑元素后移，然后插入。
*/
Status TripleMatrix::setItem(int row, int col, int item)
{
	if (row > mu || col > nu) // 超过范围，返回 ERROR
		return ERROR;
	// 在三元组中存储一个非零元素
	if (num >= MAX) // 已存元素个数 num 达到三元组可以存储的最大范围
		return ERROR;
	if (item == 0) // 输入的数组元素值为 0，则什么也不做直接返回
		return OK;

	// 利用 while 循环先找到合适的存储位置
	int index = 0; // 存储元素应该插入的位置
	while (index < num)
	{
		// 如果要找的 row 和 col，比已有三元组中的行、列值大，则继续向后移动
		if (row > data[index].row)
			index++;
		else if (row == data[index].row && (col > data[index].col))
			index++;
		else
			break;
	}

	if ((index < num) && (row == data[index].row) && (col == data[index].col))
	{
		// 当前行列元素已经存在，则将新输入的数据替换三元表中的 item
		data[index].item = item;
	}
	else // 插入新的元素
	{
		// index 的后续元素都移动一个单元，腾出 index 的位置
		for (int i = num; i > index; i--)
		{
			data[i].row = data[i - 1].row;
			data[i].col = data[i - 1].col;
			data[i].item = data[i - 1].item;
		}
		// 在 index 位置存入新的元素
		data[index].row = row;
		data[index].col = col;
		data[index].item = item;
		// 元素个数 num 加 1
		num++;
	}
	return OK;
}

// 打印稀疏矩阵
void TripleMatrix::printMatrix()
{
	int trippleIndex = 0; // tripleIndex 用来控制三元组 data 数组的下标
	cout << "打印矩阵：\n";
	for (int i = 1; i <= mu; i++) // 遍历矩阵
	{
		for (int j = 1; j <= nu; j++)
		{
			// 如果发现行列号匹配的三元组，则输出非零元
			if (trippleIndex < num && data[trippleIndex].row == i && data[trippleIndex].col == j)
			{
				cout << data[trippleIndex].item << "\t";
				trippleIndex++;
			}
			else // 否则输出 0
			{
				cout << "0\t";
			}
		}
		cout << endl;
	}
	cout << "矩阵有 " << mu << " 行 " << nu << " 列 " << num << " 个非零元素" << endl;
	return;
}

// 打印三元组数组
void TripleMatrix::printTriple()
{
	cout << "打印三元组数组：" << endl;
	cout << "row\tcol\titem" << endl;
	for (int i = 0; i < num; i++)
	{
		cout << data[i].row << "\t" << data[i].col << "\t" << data[i].item << endl;
	}
}

void inputMatrix(int m, int n, int num, TripleMatrix& triple)
{
	int row, col, item;
	for (int i = 1; i <= num; i++)
	{
		cout << "请依次输入行、列和非零元：";
		cin >> row >> col >> item;
		if (item != 0)
		{
			if (triple.setItem(row, col, item) == ERROR)
			{
				cout << "行号或列号不正确，或者三元组数组满，不能正确存储！" << endl;
				break;
			}
		}
	}
}

bool matrixAdd(TripleMatrix a, TripleMatrix b, TripleMatrix& result)
{
	if (a.mu != b.mu || b.mu != result.mu || a.nu != b.nu || a.nu != result.nu) // 行、列不正确，矩阵不正确，不能进行加法运算
		return false;
	else
	{
		for (int i = 0; i <= a.mu; i++)
		{
			for (int j = 0; j <= a.nu; j++)
			{
				int item = a.getItem(i, j) + b.getItem(i, j);
				// 如果计算出来的值不为 0，则插入到稀疏矩阵中
				if (item != 0)
				{
					result.setItem(i, j, item);
				}
			}
		}
		return true;
	}
}

bool matrixMulty(TripleMatrix a, TripleMatrix b, TripleMatrix& result)
{
	int i, j, k;
	// 如果 a 的列数不等于 b 的行数，则返回 false
	if (a.nu != b.mu)
		return false;

	// 初始化 result的行、列值
	result.mu = a.mu;
	result.nu = b.nu;

	// 乘法计算
	for (int i = 1; i <= a.mu; i++)
	{
		for (int j = 1; j <= b.nu; j++)
		{
			int sum = 0;
			for (int k = 1; k <= a.nu; k++)
			{
				sum += a.getItem(i, k) * b.getItem(k, j);
			}
			// 如果计算出来的值不为 0，则插入到稀疏矩阵中
			if (sum != 0)
			{
				result.setItem(i, j, sum);
			}
		}
	}
	return true;
}
/*
	// 三元组的测试代码
	int main()
	{
		int m, n, num;
		cout << "请输入矩阵的行、列、非零元素个数：";
		cin >> m >> n >> num;
		TripleMatrix triple(m, n);
		inputMatrix(m, n, num, triple);
		triple.printTriple();
		triple.printMatrix();
		return 0;
	}
*/
/*
	三元组测试用例：
3 4 4
1 1 2
3 4 1
1 1 3
2 2 -1

	请输入矩阵的行、列、非零元素个数：3 4 4
	请依次输入行、列和非零元：1 1 2
	请依次输入行、列和非零元：3 4 1
	请依次输入行、列和非零元：1 1 3
	请依次输入行、列和非零元：2 2 -1
*/
/*
// 加法的测试代码
int main()
{
	int m, n, num;
	cout << "请输入第一个矩阵的行、列、非零元素个数：";
	cin >> m >> n >> num;
	cout << "第一个矩阵：" << endl;
	TripleMatrix tripleA(m, n);
	inputMatrix(m, n, num, tripleA);
	// tripleA.printTriple();
	tripleA.printMatrix();

	cout << "请输入第二个矩阵的行、列、非零元素个数：";
	cin >> m >> n >> num;
	cout << "第二个矩阵：" << endl;
	TripleMatrix tripleB(m, n);
	inputMatrix(m, n, num, tripleB);
	// tripleB.printTriple();
	tripleB.printMatrix();

	TripleMatrix tripleResult(m, n);
	if (matrixAdd(tripleA, tripleB, tripleResult))
	{
		cout << endl << "矩阵相加后：" << endl;
		// tripleResult.printTriple();
		tripleResult.printMatrix();
	}
	else
	{
		cout << "矩阵不能相加。" << endl;
	}

	return 0;
}
*/
/*
	加法的测试用例 1：
3 3 2
1 1 5
2 3 1
3 3 4
1 1 5
1 2 6
3 2 1
2 1 1

	请输入第一个矩阵的行、列、非零元素个数：3 3 2
	第一个矩阵：
	请依次输入行、列和非零元：1 1 5
	请依次输入行、列和非零元：2 3 1
	请依次输入行、列和非零元：3 3 4
	请输入第二个矩阵的行、列、非零元素个数：1 1 5
	第二个矩阵：
	请依次输入行、列和非零元：1 1 5
	请依次输入行、列和非零元：1 2 6
	请输入第二个矩阵的行、列、非零元素个数：3 2 1

	请依次输入行、列和非零元：2 1 1
*/

// 乘法测试代码
int main()
{
	int m, n, num;
	cout << "请输入第一个矩阵的行、列、非零元素个数：";
	cin >> m >> n >> num;
	cout << "第一个矩阵：" << endl;
	TripleMatrix tripleA(m, n);
	inputMatrix(m, n, num, tripleA);

	// tripleA.printTriple();
	tripleA.printMatrix();

	cout << "请输入第二个矩阵的行、列、非零元素个数：";
	cin >> m >> n >> num;
	cout << "第二个矩阵：" << endl;
	TripleMatrix tripleB(m, n);
	inputMatrix(m, n, num, tripleB);

	// tripleB.printTriple();
	tripleB.printMatrix();

	TripleMatrix tripleResult;
	if (matrixMulty(tripleA, tripleB, tripleResult))
	{
		cout << endl << "矩阵相乘后：" << endl;
		// tripleResult.printTriple();
		tripleResult.printMatrix();
	}
	else
	{
		cout << "矩阵不能相乘。" << endl;
	}
	return 0;
}
/*
	测试用例：
3 3 2
1 1 5
2 3 1
3 2 2
1 1 2
3 1 4

	请输入第一个矩阵的行、列、非零元素个数：3 3 2
	第一个矩阵：
	请依次输入行、列和非零元：1 1 5
	请依次输入行、列和非零元：2 3 1
	打印矩阵：
	5       0       0
	0       0       1
	0       0       0
	请输入第二个矩阵的行、列、非零元素个数：3 2 2
	第二个矩阵：
	请依次输入行、列和非零元：1 1 2
	请依次输入行、列和非零元：3 1 4
	打印矩阵：
	2       0
	0       0
	4       0
*/