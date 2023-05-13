/*
*	DP(점화식)
* 
*	처음에는 앞선 메모이제이션 문제처럼 풀려고 했으나 시간초과로 풀지 못했다 (dp[현재 색][몇 번째 선택])
*	시작점 for문 * 함수 내부 for문 * K = N^2K가 돼서 매우 큰 수가 된다.
* 
*	=> 앞선 메모이제이션은 비트마스킹을 통해 dp의 index자체가 visit체크를 할 수 있게 되어, dp를 채우는데에
*	중복이 없어지지만, 이 문제는 중복이 생기게된다(한번 방문했던 곳이 색상환을 만들 수 없다면 다시 방문해야 함)
*/
#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int dp[1001][1001]; //dp[i][j] i개의 색에서 k개를 선택할 수 있는 경우의 수
const int mod = 1000000003;

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;

	for (int i = 0; i <= N; i++)
	{
		dp[i][0] = 1;
		dp[i][1] = i;
	}

	int end;
	for (int i = 2; i <= N; i++)
	{
		end = min(K, i);
		for (int j = 2; j <= end; j++)
		{
			dp[i][j] = (dp[i - 1][j] + dp[i - 2][j - 1]) % mod; //i번째 color를 칠하지 않을 때 + i번째 color를 칠할 때
		}
	}

	dp[N][K] = (dp[N - 1][K] + dp[N - 3][K - 1]) % mod;
	
	cout << dp[N][K] << '\n';
}