typedef struct
{
	// x��y ���������
	int incX, incY;
}Direction;

typedef struct
{
	int x, y; // ��ǰ���ʵ��Թ����ӵ��ݺ�����
	int di; // ��ǰ����
}Box;

const int MAX_SIZE = 100;
class Stack
{
private:
	Box* data;
	int size;
	int top;
public:
	Stack();
	~Stack();
	void push(Box ch);
	Box pop();
	bool isEmpty();
	bool isFull();
};

Stack::Stack()
{
	size = MAX_SIZE;
	top = -1;
	data = new Box[MAX_SIZE];
}

Stack::~Stack()
{
	delete[] data;
}

void Stack::push(Box ch)
{
	if (!isFull())
		data[++top] = ch;
}

Box Stack::pop()
{
	if (!isEmpty())
		return data[top--];
}

bool Stack::isEmpty()
{
	if (top == -1)
		return true;
	else
		return false;
}

bool Stack::isFull()
{
	if (top + 1 == size)
		return true;
	else
		return false;
}

const int M = 20;
const int N = 20;
bool findPath(int maze[M + 2][N + 2], Direction direct[], Stack& s)
{
	Box temp;
	int x, y, di; // �Թ����ӵ�ǰ����Ԫ���ݺ�����ͷ���
	int line, col; // �Թ�������һ��Ԫ���������������
	maze[1][1] = -1;
	temp.x = 1;
	temp.y = 1;
	temp.di = -1;
	s.push(temp);
	while (!s.isEmpty()) // ջ��Ϊ��
	{
		x = temp.x;
		y = temp.y;
		di = temp.di + 1;
		while (di < 4) // ����δ������
		{
			line = x + direct[di].incX;
			col = y + direct[di].incY;
			if (maze[line][col] == 0)
			{
				temp.x = x;
				temp.y = y;
				temp.di = di;
				s.push(temp); // ջ�����������һ���Թ�ͨ·
				x = line;
				y = col;
				maze[line][col] = -1;
				if (x == M && y == N)
					return true; // �Թ���·
				else
					di = 0;
			}
			else di++;
		}
	}
	return false; // �Թ�û��·
}