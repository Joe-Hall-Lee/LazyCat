// 银行排队模拟（离散事件模拟）

#include <iostream>
#include <random>

using namespace std;

// 当从事件链表中取出第一个结点（头结点的后一个结点）且第一个结点的第二个数据域为 -1 时（-1 表示该客户到来），需要随机生成两个数
// 第一个数为该客户服务的时间，第二个数是与下一个客户间隔的时间（即下一个客户的到来时间 = 当前时间 + 间隔时间，当前时间就是第一个结点的第一个数据域）

const int CLOSE_TIME = 40; // 银行关闭时间
const int MAX_DURATION = 30; // 服务客户的最长时间
const int MAX_INTER_TIME = 10; // 下一位客户到来的最大时间间隔

int total_client; // 用于存储服务的总用户数
int total_service_time; // 用于存储服务的总时间

// 客户信息
typedef struct client
{
	int arrival_time; // 用户到达时间
	int duration; //用户服务时间
} Client;

// 事件链表
typedef struct event_list
{
	int occur_time; // 用户离开或者到达的时间
	int type; // -1 表示用户达到 0-3 表示用户从几号窗口离开
	struct event_list* next; // 指向下一个
} EventList, * List;

// 队列结点类型
typedef struct node
{
	Client client;
	struct node* next;
} Node, * N;

// 窗口链式队列实现
typedef struct windows
{
	Node* front, * rear; // 队列的头指针和尾指针
	int length; // 队列长度
} Windows, * Window;

Windows queue[4]; // 四个窗口

// 初始化事件链接
List initList(List list)
{
	// 初始化头结点
	list = (List)malloc(sizeof(EventList));
	list->next = nullptr;
	return list;
}

// 初始化四个窗口
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

// 在插入事件链表的时候，要根据occurTime进行排序
void insertList(List list, int occurTime, int type)
{
	List p = (List)malloc(sizeof(EventList));
	p->occur_time = occurTime;
	p->type = type;
	p->next = nullptr;
	// 维护两个指针
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
	// k到链表末尾了，p直接插入尾巴
	k->next = p;
}

// 获取事件链表的第一个结点
List deleteFirstNode(List list)
{
	List p = list->next;
	list->next = p->next;
	p->next = nullptr;
	return p;
}

// 插入队列
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

// 出队列
N deleteWindow(Window window)
{
	N node = window->front->next;
	window->front->next = node->next;
	window->length--;
	if (window->length == 0) window->rear = window->front; // 如果弹出的是最后一个并不对 rear 处理的话，rear 会成为野指针
	return node;
}

// 获取第一个
N getFirstNode(Window window)
{
	return window->front->next;
}

// 打印事件链表
void displayList(List list)
{
	List p = list->next;
	while (p != nullptr)
	{
		cout << "[" << p->occur_time << "," << p->type << "]->";
		p = p->next;
	}
}

// 打印窗口队列
void displayQueue(Window window)
{
	cout << "窗口排队为 ";
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
	// 调用初始化函数
	List list = nullptr;
	list = initList(list);
	for (auto& i : queue)
		i = *initWindow(&i);

	// 在事件链表插入第一个数据
	insertList(list, 0, -1);

	// 开始处理链表和队列
	List p = list;
	List temp;
	int count = 0;
	while (p->next != nullptr)
	{
		displayList(list);
		cout << endl;
		count++;
		cout << " -------------------第 " << count << " 次循环----------------- " << endl;
		temp = deleteFirstNode(list);
		cout << "当前处理的事件信息为：occurTime" << temp->occur_time << " , type" << temp->type << endl;
		if (temp->type == -1) // 表示新客户到来
		{
			cout << "是新客户到来 = 请输入服务时间 durTime 和间隔时间 interTime: ";
			total_client++; // 总客户数++
			// 随机生成当前客户服务时间和下一个客户到来的间隔时间
			int durTime = rand() % MAX_DURATION;
			int interTime = rand() % MAX_INTER_TIME;
			cout << durTime << "  " << interTime << endl;

			if (temp->occur_time + interTime < CLOSE_TIME) // 在关门前才可以进行操作
				// 插入到事件链表中
				insertList(list, temp->occur_time + interTime, -1);

			cout << "当前事件表 : ";
			displayList(list);
			cout << endl;
			// 将刚刚的temp插入到队列中，先找到最短的队列
			int min_length = queue[0].length;
			int flag = 0;
			for (int i = 1; i < 4; ++i) {
				if (queue[i].length < min_length) {
					flag = i;
					min_length = queue[i].length;
				}
			}
			// 插入队列
			insertWindow(&queue[flag], temp->occur_time, durTime);
			cout << "新客户进入 queue" << flag << endl;
			displayQueue(&queue[flag]);
			cout << endl;
			// 如果当前队列的长度为 0，则将其离开事件插入事件链表
			if (min_length == 0)
				insertList(list, temp->occur_time + durTime, flag);
		}
		else // 表示客户的离开
		{
			displayList(list);
			cout << endl;
			N node = deleteWindow(&queue[temp->type]);
			cout << "要离开客户队列的结点 " << node->client.arrival_time << " , " << node->client.duration << endl;
			displayQueue(&queue[temp->type]);
			total_service_time += node->client.duration;
			cout << "total_time : " << total_service_time << endl;
			delete node;
			// 删除该队列的第一个结点之后，如果当前队列的长度不为 0，则需要将下一个结点的离开事件插入到事件链表中
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