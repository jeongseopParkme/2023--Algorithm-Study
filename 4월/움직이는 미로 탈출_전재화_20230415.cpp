/*
*	쉬운듯 한데 실수가 많았던 문제
*	풀이는 단순 구현
* 
*	1. WALL을 옮길때 위에서 부터 옮김 -> 바로 아래 WALL이 옮겨질때 EMPTY로 바뀌면서 WALL로 표시가 안됨
*		=> sort로 아래서 부터 옮길 수 있게 함
* 
*	2. vector erase할때 idx꼬이는 오류
*		=> erase시 iterator반환되는 것 활용(이 테크닉 익혀두기!)
* 
*	3. visit배열을 매번 초기화 해줘야 함
*		=> 왜 그런지 정확하게 모르겠음... 논의 필요(반례? https://www.acmicpc.net/board/view/33740)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

struct COOR
{
	int y, x;
	bool operator==(const COOR& a) const
	{
		return y == a.y && x == a.x;
	}
};

inline bool isrange(int y, int x)
{
	return y >= 0 && y < 8 && x >= 0 && x < 8;
}

constexpr char WALL = '#';
constexpr char EMPTY = '.';
constexpr COOR START = { 7,0 };
constexpr COOR END = { 0,7 };
char map[8][8];
bool visit[8][8];
int dy[8] = { -1,1,0,0,-1,-1,+1,+1 };
int dx[8] = { 0,0,-1,+1,-1,+1,-1,+1 };
vector<COOR> wall;

bool comp(COOR& a, COOR& b)
{
	return a.y > b.y;
}

void move_wall(void)
{
	for (auto it = wall.begin(); it != wall.end();)
	{
		if ((*it).y == 7)
		{
			map[(*it).y][(*it).x] = EMPTY;
			it = wall.erase(it);
		}
		else
		{
			map[(*it).y][(*it).x] = EMPTY;
			map[(*it).y + 1][(*it).x] = WALL;
			(*it).y += 1;
			it++;
		}
	}
}

void move_chr(queue<COOR>& q)
{
	int cnt = q.size();
	while (cnt--)
	{
		COOR now = q.front();
		q.pop();

		if (now == END)
		{
			cout << 1 << '\n';
			exit(0);
		}

		if (map[now.y][now.x] == WALL)
			continue;

		//캐릭터 이동
		for (int i = 0; i < 8; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (isrange(ny, nx) && map[ny][nx] != WALL && !visit[ny][nx])
			{
				q.push({ ny,nx });
				visit[ny][nx] = true;
			}
		}
		//캐릭터 제자리
		q.push({ now });
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == WALL)
				wall.push_back({ i,j });
		}
	}
	sort(wall.begin(), wall.end(), comp);

	queue<COOR> q;
	q.push(START);
	visit[START.y][START.x] = true;

	while (!q.empty())
	{
		move_chr(q);
		move_wall();
		memset(visit, 0, sizeof(visit));
	}

	cout << 0 << '\n';
}