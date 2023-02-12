/*
*	BFS가 DFS보다 메모리 & 시간복잡도 측면에서 유리하다
* 
*	1.	처음에는 단순 brute force로 문제를 풀었다 => 당연히 시간초과
* 
*	2.	memo[][] 배열을 만들어서 pruning을 하고자 했다. 처음에는 ncnt가 memo[][]값보다 작을때만 push를 했는데,
*		이렇게 하면 다음 칸으로 진행하는데 있어서 최소가 아닌 경우가 생길 수 있다. 예를 들어 아랫방향으로 접근하는
*		상황에서 cnt가 2였고, 그 다음 접근이 왼쪽으로 접근하는 상황에서 cnt가 2라고 하자. 이때 정답이 되는 방향은 해당
*		칸에서 왼쪽 접근이라면, 왼쪽 접근이 pruning되면서 답이 안나오게 된다 => 작거나 같을 때 push하도록 수정
* 
*	3.	https://www.acmicpc.net/board/view/109356 때문에 시간초과 or 메모리 초과가 나왔다 => 같은 칸, 같은 방향, 같은 cnt가 계속 쌓이게 되면서
*		엄청난 속도로 불어나게 된다. 따라서, memo 배열에 방향에 대한 정보도 기억할 수 있도록 3차원 배열로 선언해주었다. 그 후 ncnt가 memo[][][dir]값보다
*		작을때 push 하도록 했다. 
* 
*	@@@ BFS이든 DFS이든, push하기전에 모든 조건을 검사하고, data를 갱신한 후에 push 해줘야한다! => 그래야 중복이 발생하지 않는다.
*/


#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define EMPTY '.'
#define WALL '*'
#define MAX 20000

pair<int, int> c1 = {-1, -1}, c2;
char map[100][100];
int memo[100][100][4];
int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0, 0,-1,+1 };
int H, W, ans = MAX;

struct info
{
	int y, x, dir, cnt;
};

inline bool isvalid(int y, int x, int dir, int cnt)
{
	return y >= 0 && y < H && x >= 0 && x < W && map[y][x] != WALL && memo[y][x][dir] > cnt;
}

int main(void)
{
	cin >> W >> H;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'C')
			{
				if (c1.first == -1 && c1.second == -1)
					c1 = { i,j };
				else
					c2 = { i,j };
			}
			memo[i][j][0] = MAX;
			memo[i][j][1] = MAX;
			memo[i][j][2] = MAX;
			memo[i][j][3] = MAX;
		}
	}

	memo[c1.first][c1.second][0] = 0;
	memo[c1.first][c1.second][1] = 0;
	memo[c1.first][c1.second][2] = 0;
	memo[c1.first][c1.second][3] = 0;
	queue<info> q;
	for (int i = 0; i < 4; i++)
	{
		int ny = c1.first + dy[i];
		int nx = c1.second + dx[i];
		if (isvalid(ny, nx, i, 0))
		{
			q.push({ ny,nx,i,0 });
			memo[ny][nx][i] = 0;
		}
	}

	while (!q.empty())
	{
		info cur = q.front();
		q.pop();

		if (cur.y == c2.first && cur.x == c2.second)
		{
			ans = min(ans, cur.cnt);
			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];
			int ncnt = cur.cnt;
			if (cur.dir != i)
				ncnt++;
			if (isvalid(ny, nx, i, ncnt))
			{
				q.push({ ny,nx,i,ncnt });
				memo[ny][nx][i] = ncnt;
			}
		}
	}

	cout << ans << '\n';
}