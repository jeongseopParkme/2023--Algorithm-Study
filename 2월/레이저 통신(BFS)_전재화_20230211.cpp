/*
*	BFS�� DFS���� �޸� & �ð����⵵ ���鿡�� �����ϴ�
* 
*	1.	ó������ �ܼ� brute force�� ������ Ǯ���� => �翬�� �ð��ʰ�
* 
*	2.	memo[][] �迭�� ���� pruning�� �ϰ��� �ߴ�. ó������ ncnt�� memo[][]������ �������� push�� �ߴµ�,
*		�̷��� �ϸ� ���� ĭ���� �����ϴµ� �־ �ּҰ� �ƴ� ��찡 ���� �� �ִ�. ���� ��� �Ʒ��������� �����ϴ�
*		��Ȳ���� cnt�� 2����, �� ���� ������ �������� �����ϴ� ��Ȳ���� cnt�� 2��� ����. �̶� ������ �Ǵ� ������ �ش�
*		ĭ���� ���� �����̶��, ���� ������ pruning�Ǹ鼭 ���� �ȳ����� �ȴ� => �۰ų� ���� �� push�ϵ��� ����
* 
*	3.	https://www.acmicpc.net/board/view/109356 ������ �ð��ʰ� or �޸� �ʰ��� ���Դ� => ���� ĭ, ���� ����, ���� cnt�� ��� ���̰� �Ǹ鼭
*		��û�� �ӵ��� �Ҿ�� �ȴ�. ����, memo �迭�� ���⿡ ���� ������ ����� �� �ֵ��� 3���� �迭�� �������־���. �� �� ncnt�� memo[][][dir]������
*		������ push �ϵ��� �ߴ�. 
* 
*	@@@ BFS�̵� DFS�̵�, push�ϱ����� ��� ������ �˻��ϰ�, data�� ������ �Ŀ� push ������Ѵ�! => �׷��� �ߺ��� �߻����� �ʴ´�.
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