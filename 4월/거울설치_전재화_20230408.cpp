/*
*	거울의 상하좌우 직진성을 이용한 다익스트라 문제
*	벽에 있을 때도(53번째 줄) break해줘야 하는 것에 유의!!!
*/
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

#define DOOR '#'
#define EMPTY '.'
#define MIRROR '!'
#define WALL '*'

struct DATA
{
	int y, x, num;
	bool operator<(const DATA& a) const
	{
		return num > a.num;
	}
};

int N;
int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0,0,-1,+1 };
char map[50][50];
int cost[50][50];
priority_queue<DATA> pq;

inline bool isrange(int y, int x)
{
	return y >= 0 && y < N && x >= 0 && x < N;
}

void dij(void)
{
	while (!pq.empty())
	{
		DATA now = pq.top();
		pq.pop();

		if (cost[now.y][now.x] < now.num)
			continue;

		for (int dir = 0; dir < 4; dir++)
		{
			for (int i = 1; i < N; i++)
			{
				int ny = now.y + dy[dir] * i;
				int nx = now.x + dx[dir] * i;
				
				if (!isrange(ny, nx) || map[ny][nx] == WALL)
					break;

				int nnum;
				if ((map[ny][nx] == MIRROR || map[ny][nx] == DOOR) && (nnum = now.num + 1) < cost[ny][nx])
				{
					cost[ny][nx] = nnum;
					pq.push({ ny,nx,nnum });
				}
			}
		}
	}
}

int main(void)
{
	cin >> N;
	bool door = false;
	int yy, xx;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			cost[i][j] = INT_MAX;
			if (map[i][j] == DOOR && !door)
			{
				pq.push({ i,j,0 });
				cost[i][j] = 0;
				door = true;
			}
			else if (map[i][j] == DOOR && door)
			{
				yy = i;
				xx = j;
			}
		}
	}

	dij();

	cout << cost[yy][xx] - 1 << '\n';
}