/*
*	풀이 : dp
* 
*	문제를 읽었을 때, dp문제라는 것을 파악할 수 있었다.
*	다만 양끝에 색이 달라야 한다는 점을 처리하는게 약간 고민이었는데, 단순히 첫번째 칠해지는 색을 고정해서 3번 돌리는 것으로 해결했다.
*/
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

#define R 0
#define G 1
#define B 2

int N, ans = INT_MAX;
int dp[1000][3];
int cost[1000][3];

int filldp(int startColor)
{
	dp[0][R] = INT_MAX;
	dp[0][G] = INT_MAX;
	dp[0][B] = INT_MAX;
	dp[0][startColor] = cost[0][startColor];

	for (int n = 1; n < N; n++)
	{
		// paint RED
		if (dp[n - 1][G] == INT_MAX && dp[n - 1][B] == INT_MAX)
			dp[n][R] = INT_MAX;
		else
			dp[n][R] = min(dp[n - 1][G], dp[n - 1][B]) + cost[n][R];

		// paint GREEN
		if (dp[n - 1][R] == INT_MAX && dp[n - 1][B] == INT_MAX)
			dp[n][G] = INT_MAX;
		else
			dp[n][G] = min(dp[n - 1][R], dp[n - 1][B]) + cost[n][G];

		// paint BLUE
		if (dp[n - 1][R] == INT_MAX && dp[n - 1][G] == INT_MAX)
			dp[n][B] = INT_MAX;
		else
			dp[n][B] = min(dp[n - 1][R], dp[n - 1][G]) + cost[n][B];
	}

	dp[N - 1][startColor] = INT_MAX;
	return min({ dp[N - 1][R], dp[N - 1][G], dp[N - 1][B] });
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 3; j++)
			cin >> cost[i][j];
	}

	for (int i = 0; i < 3; i++)
		ans = min(ans, filldp(i));

	cout << ans << '\n';
}