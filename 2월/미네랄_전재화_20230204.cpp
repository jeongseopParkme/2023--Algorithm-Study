/*
*	������ϴµ� ���� �ð��� ��
* 
*	1. isfloat�Լ����� cluster�� ��� ��ǥ�� visited�� ǥ������� �ϴµ� �ٴڿ�
*		��ġ�� �̳׶��� ���̸� �ٷ� return�ϵ��� �ؼ� visited�� cluster�� �Ϻΰ� false�� ǥ�õ�
*		--> �ϳ��� cluster���� �ٸ� cluster�� �ν��ϴ� ����
* 
*	2. iscluster�Լ��� �ʱ�ȭ�� isfloat�Լ��� ȣ��� ������ �ؾ��ϴµ� findFloatCluster�Լ����� ���ִ� ����
* 
*	3. movecluster�Լ����� �ٴڿ� �̳׶��� �ִ� ��� num--�� ����ε�, �ٴ��� ��� break�ϴ� if���� ���� ���� ����ؼ� 
*		�ٴڿ� �̳׶��� �ִ� ��� �������� ��캸�� num�� +1 Ŀ���� ����
* 
*	Ǯ�̴� ���� + BFS
*	
*	@�ٴڿ� �ִ� �̳׶����� ������� BFS�� �����ϰ�, visitedüũ�� �ȵ� �̳׶��� floatCluster�� �Ǵ��ϴ� ����� ���� �� ȿ������ ��
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define CANNOTDOWN 101

struct COOR
{
	int y, x;
};

int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0,0,-1,+1 };
int R, C, N;
char map[100][100];
bool visited[100][100];
bool iscluster[100][100];
vector<COOR> cluster;

inline bool isrange(COOR coor)
{
	return coor.y >= 0 && coor.y < R && coor.x >= 0 && coor.x < C;
}

bool compare(COOR a, COOR b)
{
	if (a.y == b.y)
		return a.x < b.x;
	return a.y > b.y;
}

/* �̳׶� �� �ٴ���ǥ�� �ִ� �̳׶��� ������ floatCluster�� �ƴ� */
bool isfloat(int y, int x)
{
	cluster.clear();
	memset(iscluster, 0, sizeof(iscluster)); //���� 2
	bool val = true; //���� 1

	queue<COOR> q;
	q.push({ y,x });
	visited[y][x] = true;
	/* BFS */
	while (!q.empty())
	{
		COOR now = q.front();
		q.pop();

		cluster.push_back(now);
		iscluster[now.y][now.x] = true;

		if (now.y == R - 1)
			val = false; //���� 1

		for (int i = 0; i < 4; i++)
		{
			COOR next = { now.y + dy[i], now.x + dx[i] };
			if (isrange(next) && visited[next.y][next.x] == false && map[next.y][next.x] == 'x')
			{
				q.push(next);
				visited[next.y][next.x] = true;
			}
		}
	}

	return val; //���� 1
}

bool findFloatCluster(void)
{
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (visited[i][j] == false && map[i][j] == 'x' && isfloat(i,j))
				return true;
			else 
				visited[i][j] = true;
		}
	}
	return false;
}

/* floatCluster�� ��� �̳׶��� ���� => �������ٰ� �� �ڽ� cluster�� ������ ���� ����� �ƴ� */
void moveCluster(void)
{
	int downNumber = CANNOTDOWN;
	size_t ssize = cluster.size();

	for (int i = 0; i < ssize; i++)
	{
		COOR temp = cluster[i];
		int num = 1;
		while (true)
		{
			if (map[temp.y + num][temp.x] == 'x' && iscluster[temp.y + num][temp.x] == false)
			{
				num--;
				break;
			}
			else if (temp.y + num == R - 1) //���� 3
				break;
			else if (map[temp.y + num][temp.x] == 'x' && iscluster[temp.y + num][temp.x] == true)
			{
				num = CANNOTDOWN;
				break;
			}
			else
				num++;
		}

		downNumber = min(downNumber, num);
	}

	sort(cluster.begin(), cluster.end(), compare);

	for (int i = 0; i < ssize; i++)
	{
		COOR temp = cluster[i];

		map[temp.y][temp.x] = '.';
		map[temp.y + downNumber][temp.x] = 'x';
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> R >> C;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			cin >> map[i][j];

	cin >> N;
	for (int turn = 0; turn < N; turn++)
	{
		int height;
		cin >> height;
		height = R - height;
		if (turn % 2 == 0)
		{
			for (int i = 0; i < C; i++)
			{
				if (map[height][i] == 'x')
				{
					map[height][i] = '.';
					break;
				}
			}
		}
		else
		{
			for (int i = C - 1; i >= 0; i--)
			{
				if (map[height][i] == 'x')
				{
					map[height][i] = '.';
					break;
				}
			}
		}
		/* �ٽ� �ڵ� */
		if(findFloatCluster())
		{
			moveCluster();
		}
	}
	/* ���� ��� */
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
			cout << map[i][j];
		cout << '\n';
	}
}