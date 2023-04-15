/*
*	풀이 : 메모이제이션 + dfs
* 
*	외판원문제와 유사하나, visit 비트 마스킹이 필요없음 => 같은 칸을 여러 번 방문할 수 있기 때문에
*	따라서, dfs tree의 깊이만 알 수 있으면, memoization을 할 수 있다. 
* 
*	memset 사용시 byte 단위로 초기화가 진행되는 것에 유의 => char, bool등 1byte 변수에 사용하거나, "0 or -1"로 초기화 해야한다.
*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define NaN -1

char map[100][100];
string str;
int N, M, K, ans;
int dy[4] = { -1,+1,0,0 }, dx[4] = { 0,0,-1,+1 };
int memo[100][100][80];

bool inline isrange(int y, int x)
{
	return y >= 0 && y < N && x >= 0 && x < M;
}

int dfs(int y, int x, int depth)
{
	if (memo[y][x][depth] != NaN)
		return memo[y][x][depth];

	if (depth == str.size() - 1)
		return memo[y][x][depth] = 1;

	memo[y][x][depth] = 0;
	for (int k = 1; k <= K; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i] * k;
			int nx = x + dx[i] * k;
			if (isrange(ny, nx) && map[ny][nx] == str[depth + 1])
			{
				memo[y][x][depth] += dfs(ny, nx, depth + 1);
			}
		}
	}
	return memo[y][x][depth];
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	}

	cin >> str;

	memset(memo, NaN, sizeof(memo)); // 1Byte식 초기화 => 1Byte 변수에만 사용하거나(char, bool), 0 or -1로만 초기화

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == str[0])
				ans += dfs(i, j, 0);
		}
	}

	cout << ans << '\n';
}