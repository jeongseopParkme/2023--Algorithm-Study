/*
*	풀이 : BFS
*	생각을 전환해서 맵 전체를 훑어나가면서 연속된 EMPTY영역의 크기를 계산
*	BFS를 할때, 두 개의 queue를 이용해 EMPTY영역의 모서리의 WALL에 EMPTY의 크기를 누적시킴
*	visit배열을 운용하돼, 모서리의 WALL에 누적시킨 후에는 visit[][] = false로 바꿀 것
* 
*	=> 발상의 전환 + 코드최적화에 대해서 반성을 했음...
*/
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct COOR
{
	int y, x;
};

constexpr int EMPTY = 0;
int N, M;
int input[1000][1000];
bool visit[1000][1000];
int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0,0,-1,+1 };

inline bool isrange(int y, int x)
{
	return y >= 0 && y < N && x >= 0 && x < M;
}

void fill_chunkinput(int y, int x)
{
	//initialize
	queue<COOR> q, q_;
	int cnt = 0;

	//find chunkSize
	q.push({ y,x });
	visit[y][x] = true;
	cnt++;
	while (!q.empty())
	{
		COOR now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (isrange(ny, nx) && visit[ny][nx] == false)
			{
				if (input[ny][nx] != EMPTY)
					q_.push({ ny,nx });
				else
				{
					q.push({ ny,nx });
					cnt++;
				}
				visit[ny][nx] = true;
			}
		}
	}

	//plus chunksize to wall
	while (!q_.empty())
	{
		COOR now = q_.front();
		q_.pop();
		input[now.y][now.x] += cnt;
		visit[now.y][now.x] = false;
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	//input
	cin >> N >> M;
	char temp;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> temp;
			input[i][j] = temp - '0';
		}
	}

	//make chunkinput
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (input[i][j] == 0 && visit[i][j] == false)
				fill_chunkinput(i, j);
		}
	}

	//output
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << input[i][j] % 10;
		cout << '\n';
	}
}