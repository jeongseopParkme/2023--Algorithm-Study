/*
*	풀이 : 메모이제이션 + brute force + (프루닝)
* 
*	처음에는 단순하게 최단거리에 위치한 먼지들을 찾아가는 방식으로 풀었다.
*	하지만 이 경우, 돌아가는 경우가 생기거나, 최소값 거리가 여러개 있을때 어떤 먼지를 먼저 청소할지 정해야하는 문제가 있었다.
*	=> https://www.acmicpc.net/board/view/65038
* 
*	결국 brute force를 사용해야만 했다.
*	하지만, brute force시 n!의 시간복잡도가 요구되고, 각 경우마다 bfs로 최단거리를 구하게 되면 h*w의 시간복잡도가 요구되므로 총
*	시간복잡도는 n!*h*w 이다.
* 
*	시간을 줄이기 위해 brute force를 하기 전 메모이제이션을 통해 각 먼지에서 다른 먼지까지의 최단거리를 미리 구해놓으면 시간복잡도는
*	n*h*w + n! 으로 줄어들게 된다.
* 
*	추가적으로 프루닝을 통해 시간을 더 단축시킬 수 있었다.
* 
*	==> 숫자가 충분히 작고 특별한 방법이 생각나지 않는다면 효율적인 brute force가 답일 수도 있다!
*/
#include <iostream>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

#define CLEAN '.'
#define DIRTY '*'
#define WALL  'x'
#define START 'o'

struct DATA
{
	int y, x;
	int cnt;
};

int w, h;
int y, x;
int cnt;
int ans;
int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0,0,-1,+1 };
char map[20][20];
bool visit[20][20];
pair<int,int> dirty[10];
int dist[20][20][20][20];
bool visited[10];

bool inline isrange(int y, int x)
{
	return (y >= 0 && y < h && x >= 0 && x < w);
}

void print()
{
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < cnt; j++)
		{
			int sy = dirty[i].first;
			int sx = dirty[i].second;
			int ty = dirty[j].first;
			int tx = dirty[j].second;
			cout << "from : " << sy << " " << sx << " to : " << ty << " " << tx << " dist : " << dist[sy][sx][ty][tx] << "\n";
		}
	}
}

bool bfs(int sy, int sx)
{
	bool flag = false;

	memset(visit, false, sizeof(visit));
	queue<DATA> q;
	q.push({ sy,sx,0 });
	visit[sy][sx] = true;

	while (!q.empty())
	{
		DATA temp = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int ny = temp.y + dy[i];
			int nx = temp.x + dx[i];
			if (isrange(ny, nx) && map[ny][nx] != WALL && visit[ny][nx] == false)
			{
				if (map[ny][nx] == DIRTY)
				{
					flag = true;
					dist[sy][sx][ny][nx] = temp.cnt + 1;
				}
				q.push({ ny,nx, temp.cnt + 1 });
				visit[ny][nx] = true;
			}
		}
	}

	return flag;
}

void worker(int sy, int sx, int depth, int val)
{
	if (depth == cnt)
	{
		ans = min(ans, val);
		return;
	}

	if (val > ans)
		return;

	for (int i = 0; i < cnt; i++)
	{
		if (visited[i] == false)
		{
			visited[i] = true;
			worker(dirty[i].first, dirty[i].second, depth + 1, val + dist[sy][sx][dirty[i].first][dirty[i].second]);
			visited[i] = false;
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	while (1)
	{
		ans = INT_MAX;
		cnt = 0;
		cin >> w >> h;
		if (w == 0 && h == 0)
			break;

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				cin >> map[i][j];
				if (map[i][j] == START)
				{
					y = i; x = j;
				}
				else if (map[i][j] == DIRTY)
				{
					dirty[cnt++] = { i,j };
				}
			}
		}

		bool flag = true;
		bfs(y, x);
		for (int i = 0; i < cnt; i++)
		{
			flag = bfs(dirty[i].first, dirty[i].second);
			if (!flag)
			{
				cout << -1 << '\n';
				break;
			}
		}

		if (flag)
		{
			worker(y, x, 0, 0);
			cout << ans << '\n';
		}
	}
}