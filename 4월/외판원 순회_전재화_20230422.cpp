/*
*	풀이 : 메모이제이션 + dfs
*	
*	https://www.notion.so/einsteinandfeynman/_-519856516765491880e4c7e8b3df9c8c?pvs=4
*/
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

typedef unsigned int uint;
int N;
uint W[16][16];
uint memo[16][1 << 16];

uint dfs(int now, int visit)
{
	// end of node
	if (visit == (1 << N) - 1)
	{
		if (W[now][0])
			return W[now][0];
		else
			return INT_MAX;
	}

	// 이미 탐색한 tree일때
	if (memo[now][visit] != 0)
		return memo[now][visit];

	// 하위 트리 탐색
	memo[now][visit] = INT_MAX;
	for (int next = 1; next < N; next++)
	{
		if ((1 << next) & visit || W[now][next] == 0) // 이미 방문한 노드 일때 OR 다음 노드로 갈 수 없을 때
			continue;
		memo[now][visit] = min(memo[now][visit], W[now][next] + dfs(next, (1 << next) | visit));
	}
	return memo[now][visit];
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cin >> W[i][j];
	}

	cout << dfs(0, 1) << '\n';
}