/*
*	BFS가 더 빨랐음. 자세한 풀이는 BFS를 참고하자.
*/

#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

#define EMPTY '.'
#define WALL '*'
#define MAX 20000

struct info
{
	int y, x, dir, cnt;
};

int H, W, ans = MAX;
char map[100][100];
int memo[100][100][4];
int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0, 0,-1,+1};
int visited[100][100];
pair<int, int> c1, c2;

bool inline isrange(int y, int x) { return y >= 0 && y < H&& x >= 0 && x < W; }

void dfs(int y, int x, int dir, int cnt)
{
	if (y == c2.first && x == c2.second)
	{
		ans = min(ans, cnt);
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];
		int ncnt = cnt;
		if (i != dir)
			ncnt++;

		if (isrange(ny, nx) && map[ny][nx] != WALL && visited[ny][nx] == false && memo[ny][nx][i] > ncnt)
		{
			memo[ny][nx][i] = ncnt;

			visited[ny][nx] = true;
			dfs(ny, nx, i, ncnt);
			visited[ny][nx] = false;
		}
	}
}



int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> W >> H;
	bool c1Find = false;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'C')
			{
				if (c1Find)
				{
					c2.first = i;
					c2.second = j;
				}
				else
				{
					c1.first = i;
					c1.second = j;
					c1Find = true;
				}
			}
			memo[i][j][0] = MAX; memo[i][j][1] = MAX; 
			memo[i][j][2] = MAX; memo[i][j][3] = MAX;
		}
	}

	memo[c1.first][c1.second][0] = 0;
	memo[c1.first][c1.second][1] = 0;
	memo[c1.first][c1.second][2] = 0;
	memo[c1.first][c1.second][3] = 0;
	for (int i = 0; i < 4; i++)
	{
		int ny = c1.first + dy[i];
		int nx = c1.second + dx[i];

		if (isrange(ny, nx) && map[ny][nx] != WALL && visited[ny][nx] == false)
		{
			memo[ny][nx][i] = 0;

			visited[ny][nx] = true;
			dfs(ny, nx, i, 0);
			visited[ny][nx] = false;
		}
	}

	cout << ans << '\n';
}