/*
*	DP => 회문이 되기 위해서는 양 끝의 문자가 같고, 그 사이의 문자열이 회문이어야 한다는 특성을 이용해 DP를 채웠다.
*	N이 2000이어서 N^2까지는 가능하다.
*	DP문제인지 몰랐으면 쉽게 접근을 못했을 것 같다.
*/

#include <iostream>
using namespace std;

int N, M;
int arr[2001];
int dp[2001][2001];

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	for (int k = 0; k < N; k++)
	{
		for (int i = 1; i + k <= N; i++)
		{
			if (k == 0)
				dp[i][i + k] = 1;
			else if (k == 1)
				dp[i][i + k] = (arr[i] == arr[i + k]);
			else
				dp[i][i + k] = dp[i + 1][i + k - 1] * (arr[i] == arr[i + k]);
		}
	}

	cin >> M;
	int S, E;
	for (int i = 0; i < M; i++)
	{
		cin >> S >> E;
		cout << dp[S][E] << '\n'; //endl로 하면 안됨 => endl는 buffer flushing을 동반하기 때문에 훨씬 느리다!!!
	}
}