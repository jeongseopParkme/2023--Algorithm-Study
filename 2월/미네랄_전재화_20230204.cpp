/*
*	디버깅하는데 많은 시간을 씀
* 
*	1. isfloat함수에서 cluster의 모든 좌표를 visited로 표시해줘야 하는데 바닥에
*		위치한 미네랄이 보이면 바로 return하도록 해서 visited에 cluster의 일부가 false로 표시됨
*		--> 하나의 cluster지만 다른 cluster로 인식하는 오류
* 
*	2. iscluster함수의 초기화를 isfloat함수가 호출될 때마다 해야하는데 findFloatCluster함수에서 해주는 오류
* 
*	3. movecluster함수에서 바닥에 미네랄이 있는 경우 num--의 대상인데, 바닥일 경우 break하는 if문을 가장 먼저 사용해서 
*		바닥에 미네랄이 있는 경우 정상적인 경우보다 num이 +1 커지는 오류
* 
*	풀이는 구현 + BFS
*	
*	@바닥에 있는 미네랄들을 대상으로 BFS를 진행하고, visited체크가 안된 미네랄을 floatCluster로 판단하는 방법이 조금 더 효율적일 듯
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

/* 미네랄 중 바닥좌표에 있는 미네랄이 있으면 floatCluster가 아님 */
bool isfloat(int y, int x)
{
	cluster.clear();
	memset(iscluster, 0, sizeof(iscluster)); //오류 2
	bool val = true; //오류 1

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
			val = false; //오류 1

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

	return val; //오류 1
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

/* floatCluster의 모든 미네랄을 조사 => 내려가다가 내 자신 cluster를 만나면 조사 대상이 아님 */
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
			else if (temp.y + num == R - 1) //오류 3
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
		/* 핵심 코드 */
		if(findFloatCluster())
		{
			moveCluster();
		}
	}
	/* 정답 출력 */
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
			cout << map[i][j];
		cout << '\n';
	}
}