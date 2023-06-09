#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define BLANK 0
#define NONE -1

#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

struct coor
{
	int y, x;
} blank;
int memo[5][5], path[5][5], opposeDir[4] = { DOWN,LEFT,UP,RIGHT };
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
bool fix[5][5]; //fix : pattern을 완성함
extern bool swap(int dir);
bool isrange(int y, int x) { return y >= 0 && y < 5 && x >= 0 && x < 5; }

void BFS(coor from, coor to)
{
	memset(memo, NONE, sizeof(path));
	queue<coor> q;
	bool visit[5][5];
	memset(visit, 0, sizeof(visit));

	q.push(from);
	visit[from.y][from.x] = true;

	while (!q.empty())
	{
		coor now = q.front();
		q.pop();

		if (now.y == to.y && now.x == to.x)
			return;

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = now.y + dy[dir];
			int nx = now.x + dx[dir];
			if (isrange(ny, nx) && !visit[ny][nx] && !fix[ny][nx] && path[ny][nx] == NONE)
			{
				q.push({ ny,nx });
				visit[ny][nx] = true;
				memo[ny][nx] = opposeDir[dir];
			}
		}
	}
}

void callswap(coor from, coor to, bool fillpath, int board[5][5])
{
	while (blank.y != to.y || blank.x != to.x)
	{
		int dir = memo[blank.y][blank.x];

		if (fillpath)
			path[blank.y][blank.x] = dir;

		swap(dir);
		swap(board[blank.y][blank.x], board[blank.y + dy[dir]][blank.x + dx[dir]]);
		blank.y += dy[dir];
		blank.x += dx[dir];
	}
}

coor findcolor(coor from, int color, int board[5][5])
{
	queue<coor> q;
	bool visit[5][5];
	memset(visit, 0, sizeof(visit));

	q.push(from);
	visit[from.y][from.x] = true;

	while (!q.empty())
	{
		coor now = q.front();
		q.pop();

		if (board[now.y][now.x] == color)
			return { now.y, now.x };

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = now.y + dy[dir];
			int nx = now.x + dx[dir];
			if (isrange(ny, nx) && !visit[ny][nx] && !fix[ny][nx] && path[ny][nx] == NONE)
			{
				q.push({ ny,nx });
				visit[ny][nx] = true;
			}
		}
	}
}

void solve(int board[5][5], int pattern[3][3], int callCntLimit) 
{
	memset(fix, 0, sizeof(fix));
	blank = { -1,-1 };

	for (int i = 0; i < 5 && blank.y == -1; i++)
	{
		for (int j = 0; j < 5 && blank.y == -1; j++)
		{
			if (board[i][j] == BLANK)
				blank = { i,j };
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (pattern[i][j] != board[i + 1][j + 1])
			{
				memset(path, NONE, sizeof(path));
				//색이 다른 곳까지 blank를 옮긴다
				coor now = { i + 1,j + 1 };
				BFS(now, blank);
				callswap(blank, now, false, board); //path를 채워 넣지 않음
				//순환하는 path를 만든다
				coor target = findcolor(blank, pattern[i][j], board);
				BFS(target, now);
				callswap(now, target, true, board); //path를 채워 넣음
				BFS(now, target);
				callswap(target, now, true, board); //path를 채워 넣음

				while (pattern[i][j] != board[i + 1][j + 1])
				{
					int dir = path[blank.y][blank.x];
					swap(dir);
					swap(board[blank.y][blank.x], board[blank.y + dy[dir]][blank.x + dx[dir]]);
					blank.y += dy[dir];
					blank.x += dx[dir];
				}
				fix[now.y][now.x] = true;
			}
			else
				fix[i + 1][j + 1] = true;
		}
	}
}