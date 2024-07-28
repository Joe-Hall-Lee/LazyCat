// �����Ŷ�ģ�⣨��ɢ�¼�ģ�⣩

#include <iostream>
#include <random>

using namespace std;

// �����¼�������ȡ����һ����㣨ͷ���ĺ�һ����㣩�ҵ�һ�����ĵڶ���������Ϊ -1 ʱ��-1 ��ʾ�ÿͻ�����������Ҫ�������������
// ��һ����Ϊ�ÿͻ������ʱ�䣬�ڶ�����������һ���ͻ������ʱ�䣨����һ���ͻ��ĵ���ʱ�� = ��ǰʱ�� + ���ʱ�䣬��ǰʱ����ǵ�һ�����ĵ�һ��������

const int CLOSE_TIME = 40; // ���йر�ʱ��
const int MAX_DURATION = 30; // ����ͻ����ʱ��
const int MAX_INTER_TIME = 10; // ��һλ�ͻ����������ʱ����

int total_client; // ���ڴ洢��������û���
int total_service_time; // ���ڴ洢�������ʱ��

// �ͻ���Ϣ
typedef struct client
{
	int arrival_time; // �û�����ʱ��
	int duration; //�û�����ʱ��
} Client;

// �¼�����
typedef struct event_list
{
	int occur_time; // �û��뿪���ߵ����ʱ��
	int type; // -1 ��ʾ�û��ﵽ 0-3 ��ʾ�û��Ӽ��Ŵ����뿪
	struct event_list* next; // ָ����һ��
} EventList, * List;

// ���н������
typedef struct node
{
	Client client;
	struct node* next;
} Node, * N;

// ������ʽ����ʵ��
typedef struct windows
{
	Node* front, * rear; // ���е�ͷָ���βָ��
	int length; // ���г���
} Windows, * Window;

Windows queue[4]; // �ĸ�����

// ��ʼ���¼�����
List initList(List list)
{
	// ��ʼ��ͷ���
	list = (List)malloc(sizeof(EventList));
	list->next = nullptr;
	return list;
}

// ��ʼ���ĸ�����
Window initWindow(Windows* q)
{
	q = (Window)malloc(sizeof(Windows));
	N node = (N)malloc(sizeof(Node));
	q->front = node;
	q->front->next = nullptr;
	q->rear = q->front;
	q->length = 0;
	return q;
}

// �ڲ����¼������ʱ��Ҫ����occurTime��������
void insertList(List list, int occurTime, int type)
{
	List p = (List)malloc(sizeof(EventList));
	p->occur_time = occurTime;
	p->type = type;
	p->next = nullptr;
	// ά������ָ��
	List q = list->next;
	List k = list;
	while (q != nullptr)
	{
		if (q->occur_time > p->occur_time)
		{
			p->next = q;
			k->next = p;
			return;
		}
		k = q;
		q = q->next;
	}
	// k������ĩβ�ˣ�pֱ�Ӳ���β��
	k->next = p;
}

// ��ȡ�¼�����ĵ�һ�����
List deleteFirstNode(List list)
{
	List p = list->next;
	list->next = p->next;
	p->next = nullptr;
	return p;
}

// �������
void insertWindow(Window window, int arrivalTime, int duration)
{
	Client client;
	client.arrival_time = arrivalTime;
	client.duration = duration;
	N node = (N)malloc(sizeof(Node));
	node->client = client;
	node->next = nullptr;
	window->rear->next = node;
	window->rear = node;
	window->length++;
}

// ������
N deleteWindow(Window window)
{
	N node = window->front->next;
	window->front->next = node->next;
	window->length--;
	if (window->length == 0) window->rear = window->front; // ��������������һ�������� rear ����Ļ���rear ���ΪҰָ��
	return node;
}

// ��ȡ��һ��
N getFirstNode(Window window)
{
	return window->front->next;
}

// ��ӡ�¼�����
void displayList(List list)
{
	List p = list->next;
	while (p != nullptr)
	{
		cout << "[" << p->occur_time << "," << p->type << "]->";
		p = p->next;
	}
}

// ��ӡ���ڶ���
void displayQueue(Window window)
{
	cout << "�����Ŷ�Ϊ ";
	N node = window->front->next;
	while (node != nullptr)
	{
		cout << "[" << node->client.arrival_time << "," << node->client.duration << "]->";
		node = node->next;
	}
	cout << endl;
}

int main()
{
	// ���ó�ʼ������
	List list = nullptr;
	list = initList(list);
	for (auto& i : queue)
		i = *initWindow(&i);

	// ���¼���������һ������
	insertList(list, 0, -1);

	// ��ʼ��������Ͷ���
	List p = list;
	List temp;
	int count = 0;
	while (p->next != nullptr)
	{
		displayList(list);
		cout << endl;
		count++;
		cout << " -------------------�� " << count << " ��ѭ��----------------- " << endl;
		temp = deleteFirstNode(list);
		cout << "��ǰ������¼���ϢΪ��occurTime" << temp->occur_time << " , type" << temp->type << endl;
		if (temp->type == -1) // ��ʾ�¿ͻ�����
		{
			cout << "���¿ͻ����� = ���������ʱ�� durTime �ͼ��ʱ�� interTime: ";
			total_client++; // �ܿͻ���++
			// ������ɵ�ǰ�ͻ�����ʱ�����һ���ͻ������ļ��ʱ��
			int durTime = rand() % MAX_DURATION;
			int interTime = rand() % MAX_INTER_TIME;
			cout << durTime << "  " << interTime << endl;

			if (temp->occur_time + interTime < CLOSE_TIME) // �ڹ���ǰ�ſ��Խ��в���
				// ���뵽�¼�������
				insertList(list, temp->occur_time + interTime, -1);

			cout << "��ǰ�¼��� : ";
			displayList(list);
			cout << endl;
			// ���ոյ�temp���뵽�����У����ҵ���̵Ķ���
			int min_length = queue[0].length;
			int flag = 0;
			for (int i = 1; i < 4; ++i) {
				if (queue[i].length < min_length) {
					flag = i;
					min_length = queue[i].length;
				}
			}
			// �������
			insertWindow(&queue[flag], temp->occur_time, durTime);
			cout << "�¿ͻ����� queue" << flag << endl;
			displayQueue(&queue[flag]);
			cout << endl;
			// �����ǰ���еĳ���Ϊ 0�������뿪�¼������¼�����
			if (min_length == 0)
				insertList(list, temp->occur_time + durTime, flag);
		}
		else // ��ʾ�ͻ����뿪
		{
			displayList(list);
			cout << endl;
			N node = deleteWindow(&queue[temp->type]);
			cout << "Ҫ�뿪�ͻ����еĽ�� " << node->client.arrival_time << " , " << node->client.duration << endl;
			displayQueue(&queue[temp->type]);
			total_service_time += node->client.duration;
			cout << "total_time : " << total_service_time << endl;
			delete node;
			// ɾ���ö��еĵ�һ�����֮�������ǰ���еĳ��Ȳ�Ϊ 0������Ҫ����һ�������뿪�¼����뵽�¼�������
			if (queue[temp->type].length != 0)
			{
				N nodeNext = getFirstNode(&queue[temp->type]);
				insertList(list, nodeNext->client.arrival_time + nodeNext->client.duration, temp->type);
			}
		}
	}
	cout << total_service_time * 1.0 / total_client << endl;
	return 0;
}