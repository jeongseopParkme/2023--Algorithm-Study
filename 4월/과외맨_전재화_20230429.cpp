/*
*	구현
* 
*	생각보다 디테일하게 봐줘야 할 것이 많았고, 특히 Qpush에서 구현한
*	같은 타일에 있는 칸을 같이 넣어줘야 한다는 사실을 파악하는데 오래걸렸다.
* 
*	입력처리할 때, 코드가 상당히 길었는데, GPT의 도움을 받아 비트 연산을 이용해
*	코드를 compact하게 바꿀 수 있었다.
*/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct tile
{
	int num, idx, len;
	pair<int, int> path, partner;
};

typedef pair<int, int> coor;
tile map[1000][1000];
bool visit[1000][1000];
int N, ans;
int dy[4] = { -1,0,0,+1 }, dx[4] = { 0,-1,+1,0 };
queue<coor> q;

void printPath(int y, int x)
{
	if (map[y][x].idx == 1)
	{
		cout << map[y][x].idx << ' ';
		return;
	}
	printPath(map[y][x].path.first, map[y][x].path.second);
	cout << map[y][x].idx << ' ';
}

bool isrange(int y, int x)
{
	if (y < 0 || y >= N)
		return false;

	// y가 짝수인지 홀수인지 판단하는 비트 연산
	bool even = (y & 1) == 0;

	// x의 범위를 한 번에 비교하는 삼항 연산
	return even ? (x >= 0 && x < 2 * N) : (x >= 1 && x < 2 * N - 1);
}

// 같은 타일에 있는 칸을 같이 넣어주는 것이 핵심
void Qpush(int y, int x, int pathY, int pathX, int len)
{
	int py = map[y][x].partner.first;
	int px = map[y][x].partner.second;
	
	q.push({ y, x });
	q.push({ py, px });

	visit[y][x] = true;
	visit[py][px] = true;

	map[y][x].path = { pathY, pathX };
	map[py][px].path = { pathY, pathX };

	map[y][x].len = len + 1;
	map[py][px].len = len + 1;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;

	int end, idx = 0;
	const int ENDTILE = N * N - N / 2;

	for (int i = 0; i < N; i++)
	{
		end = ((i & 1) == 0) ? N : N - 1;
		for (int j = 0; j < end * 2; j++)
		{
			// fill num
			cin >> map[i][j + (i & 1)].num;
			// fill idx
			map[i][j + (i & 1)].idx = ++idx;
			if ((j & 1) == 0)
				idx--;
			// fill partner
			map[i][j + (i & 1)].partner = { i, j + (i & 1) + (j & 1 ? -1 : +1) };
		}
	}

	Qpush(0, 0, 0, 0, 0);

	int maxIdx = 0;
	coor maxIdxCoor;
	while (!q.empty())
	{
		auto [y, x] = q.front(); // 구조체 분해 할당
		q.pop();

		auto& cur = map[y][x]; // 현재 위치의 참조

		if (maxIdx < cur.idx) // 가장 큰 번호가 답이다
		{
			maxIdx = cur.idx;
			maxIdxCoor = { y,x };
			ans = cur.len;
		}

		if (cur.idx == ENDTILE)
			break;

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (isrange(ny, nx) && !visit[ny][nx] && map[ny][nx].num == cur.num)
				Qpush(ny, nx, y, x, cur.len);
		}
	}

	cout << ans << '\n';
	printPath(maxIdxCoor.first, maxIdxCoor.second);
}