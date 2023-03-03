/*
*	Ǯ�� : �޸������̼� + brute force + (�����)
* 
*	ó������ �ܼ��ϰ� �ִܰŸ��� ��ġ�� �������� ã�ư��� ������� Ǯ����.
*	������ �� ���, ���ư��� ��찡 ����ų�, �ּҰ� �Ÿ��� ������ ������ � ������ ���� û������ ���ؾ��ϴ� ������ �־���.
*	=> https://www.acmicpc.net/board/view/65038
* 
*	�ᱹ brute force�� ����ؾ߸� �ߴ�.
*	������, brute force�� n!�� �ð����⵵�� �䱸�ǰ�, �� ��츶�� bfs�� �ִܰŸ��� ���ϰ� �Ǹ� h*w�� �ð����⵵�� �䱸�ǹǷ� ��
*	�ð����⵵�� n!*h*w �̴�.
* 
*	�ð��� ���̱� ���� brute force�� �ϱ� �� �޸������̼��� ���� �� �������� �ٸ� ���������� �ִܰŸ��� �̸� ���س����� �ð����⵵��
*	n*h*w + n! ���� �پ��� �ȴ�.
* 
*	�߰������� ������� ���� �ð��� �� �����ų �� �־���.
* 
*	==> ���ڰ� ����� �۰� Ư���� ����� �������� �ʴ´ٸ� ȿ������ brute force�� ���� ���� �ִ�!
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