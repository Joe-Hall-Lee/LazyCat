#include <iostream>
using namespace std;

#define MAX 100
#define ERROR 0
#define OK 1
typedef int Status; // �������״̬����

typedef struct
{
	int row, col; // ��Ԫ����кš��к�
	int item; // ��Ԫ���ֵ
} Triple;

// ���� TripleMatrix �࣬ÿ�� TripleMatrix �������һ���������Ϣ
class TripleMatrix
{
private:
	Triple data[MAX]; // ����Ԫ��Ԫ��
	int mu, nu, num; // ����������������ͷ���Ԫ����
public:
	TripleMatrix();
	TripleMatrix(int m, int n); // ��������ʱ��������Եĳ�ʼ��
	~TripleMatrix();
	Status setItem(int row, int col, int item); // �����кš��кš�����Ԫ����β�����һ����Ԫ��
	int getItem(int row, int col); // �����кš��кţ���þ���Ԫ��ֵ
	void printMatrix(); // ������ʽ��ӡϡ�����
	void printTriple(); // ��ӡ��Ԫ������
	friend bool matrixAdd(TripleMatrix a, TripleMatrix b, TripleMatrix& result);
	friend bool matrixMulty(TripleMatrix a, TripleMatrix b, TripleMatrix& result);
};

TripleMatrix::TripleMatrix()
{
	// ��ʼ������������������ͷ���Ԫ����
	mu = nu = num = 0;
}

TripleMatrix::TripleMatrix(int m, int n)
{
	// ��ʼ������������������ͷ���Ԫ����
	mu = m;
	nu = n;
	num = 0;
}

TripleMatrix::~TripleMatrix()
{
}

// �����кš��кŻ��ϡ�����Ԫ�ص�ֵ
int TripleMatrix::getItem(int row, int col)
{
	if (row > mu || col > nu) // ������Χֱ�ӷ��� 0
		return 0;
	for (int i = 0; i < num; i++) // ������Ԫ��
	{
		// ����������к�ƥ�����Ԫ�飬�򷵻ط���Ԫֵ
		if (data[i].row == row && data[i].col == col)
			return data[i].item;
	}
	return 0;
}

/*
	�����Ա��������Ԫ���д���һ��ϡ������һ��Ԫ�ء�
	������Ԫ���ǰ��С�����С��������ģ������Ҫ���ҵ���Ҫ�����λ�ã�
	Ȼ����Ԫ�غ��ƣ�Ȼ����롣
*/
Status TripleMatrix::setItem(int row, int col, int item)
{
	if (row > mu || col > nu) // ������Χ������ ERROR
		return ERROR;
	// ����Ԫ���д洢һ������Ԫ��
	if (num >= MAX) // �Ѵ�Ԫ�ظ��� num �ﵽ��Ԫ����Դ洢�����Χ
		return ERROR;
	if (item == 0) // ���������Ԫ��ֵΪ 0����ʲôҲ����ֱ�ӷ���
		return OK;

	// ���� while ѭ�����ҵ����ʵĴ洢λ��
	int index = 0; // �洢Ԫ��Ӧ�ò����λ��
	while (index < num)
	{
		// ���Ҫ�ҵ� row �� col����������Ԫ���е��С���ֵ�����������ƶ�
		if (row > data[index].row)
			index++;
		else if (row == data[index].row && (col > data[index].col))
			index++;
		else
			break;
	}

	if ((index < num) && (row == data[index].row) && (col == data[index].col))
	{
		// ��ǰ����Ԫ���Ѿ����ڣ���������������滻��Ԫ���е� item
		data[index].item = item;
	}
	else // �����µ�Ԫ��
	{
		// index �ĺ���Ԫ�ض��ƶ�һ����Ԫ���ڳ� index ��λ��
		for (int i = num; i > index; i--)
		{
			data[i].row = data[i - 1].row;
			data[i].col = data[i - 1].col;
			data[i].item = data[i - 1].item;
		}
		// �� index λ�ô����µ�Ԫ��
		data[index].row = row;
		data[index].col = col;
		data[index].item = item;
		// Ԫ�ظ��� num �� 1
		num++;
	}
	return OK;
}

// ��ӡϡ�����
void TripleMatrix::printMatrix()
{
	int trippleIndex = 0; // tripleIndex ����������Ԫ�� data ������±�
	cout << "��ӡ����\n";
	for (int i = 1; i <= mu; i++) // ��������
	{
		for (int j = 1; j <= nu; j++)
		{
			// ����������к�ƥ�����Ԫ�飬���������Ԫ
			if (trippleIndex < num && data[trippleIndex].row == i && data[trippleIndex].col == j)
			{
				cout << data[trippleIndex].item << "\t";
				trippleIndex++;
			}
			else // ������� 0
			{
				cout << "0\t";
			}
		}
		cout << endl;
	}
	cout << "������ " << mu << " �� " << nu << " �� " << num << " ������Ԫ��" << endl;
	return;
}

// ��ӡ��Ԫ������
void TripleMatrix::printTriple()
{
	cout << "��ӡ��Ԫ�����飺" << endl;
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
		cout << "�����������С��кͷ���Ԫ��";
		cin >> row >> col >> item;
		if (item != 0)
		{
			if (triple.setItem(row, col, item) == ERROR)
			{
				cout << "�кŻ��кŲ���ȷ��������Ԫ����������������ȷ�洢��" << endl;
				break;
			}
		}
	}
}

bool matrixAdd(TripleMatrix a, TripleMatrix b, TripleMatrix& result)
{
	if (a.mu != b.mu || b.mu != result.mu || a.nu != b.nu || a.nu != result.nu) // �С��в���ȷ��������ȷ�����ܽ��мӷ�����
		return false;
	else
	{
		for (int i = 0; i <= a.mu; i++)
		{
			for (int j = 0; j <= a.nu; j++)
			{
				int item = a.getItem(i, j) + b.getItem(i, j);
				// ������������ֵ��Ϊ 0������뵽ϡ�������
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
	// ��� a ������������ b ���������򷵻� false
	if (a.nu != b.mu)
		return false;

	// ��ʼ�� result���С���ֵ
	result.mu = a.mu;
	result.nu = b.nu;

	// �˷�����
	for (int i = 1; i <= a.mu; i++)
	{
		for (int j = 1; j <= b.nu; j++)
		{
			int sum = 0;
			for (int k = 1; k <= a.nu; k++)
			{
				sum += a.getItem(i, k) * b.getItem(k, j);
			}
			// ������������ֵ��Ϊ 0������뵽ϡ�������
			if (sum != 0)
			{
				result.setItem(i, j, sum);
			}
		}
	}
	return true;
}
/*
	// ��Ԫ��Ĳ��Դ���
	int main()
	{
		int m, n, num;
		cout << "�����������С��С�����Ԫ�ظ�����";
		cin >> m >> n >> num;
		TripleMatrix triple(m, n);
		inputMatrix(m, n, num, triple);
		triple.printTriple();
		triple.printMatrix();
		return 0;
	}
*/
/*
	��Ԫ�����������
3 4 4
1 1 2
3 4 1
1 1 3
2 2 -1

	�����������С��С�����Ԫ�ظ�����3 4 4
	�����������С��кͷ���Ԫ��1 1 2
	�����������С��кͷ���Ԫ��3 4 1
	�����������С��кͷ���Ԫ��1 1 3
	�����������С��кͷ���Ԫ��2 2 -1
*/
/*
// �ӷ��Ĳ��Դ���
int main()
{
	int m, n, num;
	cout << "�������һ��������С��С�����Ԫ�ظ�����";
	cin >> m >> n >> num;
	cout << "��һ������" << endl;
	TripleMatrix tripleA(m, n);
	inputMatrix(m, n, num, tripleA);
	// tripleA.printTriple();
	tripleA.printMatrix();

	cout << "������ڶ���������С��С�����Ԫ�ظ�����";
	cin >> m >> n >> num;
	cout << "�ڶ�������" << endl;
	TripleMatrix tripleB(m, n);
	inputMatrix(m, n, num, tripleB);
	// tripleB.printTriple();
	tripleB.printMatrix();

	TripleMatrix tripleResult(m, n);
	if (matrixAdd(tripleA, tripleB, tripleResult))
	{
		cout << endl << "������Ӻ�" << endl;
		// tripleResult.printTriple();
		tripleResult.printMatrix();
	}
	else
	{
		cout << "��������ӡ�" << endl;
	}

	return 0;
}
*/
/*
	�ӷ��Ĳ������� 1��
3 3 2
1 1 5
2 3 1
3 3 4
1 1 5
1 2 6
3 2 1
2 1 1

	�������һ��������С��С�����Ԫ�ظ�����3 3 2
	��һ������
	�����������С��кͷ���Ԫ��1 1 5
	�����������С��кͷ���Ԫ��2 3 1
	�����������С��кͷ���Ԫ��3 3 4
	������ڶ���������С��С�����Ԫ�ظ�����1 1 5
	�ڶ�������
	�����������С��кͷ���Ԫ��1 1 5
	�����������С��кͷ���Ԫ��1 2 6
	������ڶ���������С��С�����Ԫ�ظ�����3 2 1

	�����������С��кͷ���Ԫ��2 1 1
*/

// �˷����Դ���
int main()
{
	int m, n, num;
	cout << "�������һ��������С��С�����Ԫ�ظ�����";
	cin >> m >> n >> num;
	cout << "��һ������" << endl;
	TripleMatrix tripleA(m, n);
	inputMatrix(m, n, num, tripleA);

	// tripleA.printTriple();
	tripleA.printMatrix();

	cout << "������ڶ���������С��С�����Ԫ�ظ�����";
	cin >> m >> n >> num;
	cout << "�ڶ�������" << endl;
	TripleMatrix tripleB(m, n);
	inputMatrix(m, n, num, tripleB);

	// tripleB.printTriple();
	tripleB.printMatrix();

	TripleMatrix tripleResult;
	if (matrixMulty(tripleA, tripleB, tripleResult))
	{
		cout << endl << "������˺�" << endl;
		// tripleResult.printTriple();
		tripleResult.printMatrix();
	}
	else
	{
		cout << "��������ˡ�" << endl;
	}
	return 0;
}
/*
	����������
3 3 2
1 1 5
2 3 1
3 2 2
1 1 2
3 1 4

	�������һ��������С��С�����Ԫ�ظ�����3 3 2
	��һ������
	�����������С��кͷ���Ԫ��1 1 5
	�����������С��кͷ���Ԫ��2 3 1
	��ӡ����
	5       0       0
	0       0       1
	0       0       0
	������ڶ���������С��С�����Ԫ�ظ�����3 2 2
	�ڶ�������
	�����������С��кͷ���Ԫ��1 1 2
	�����������С��кͷ���Ԫ��3 1 4
	��ӡ����
	2       0
	0       0
	4       0
*/