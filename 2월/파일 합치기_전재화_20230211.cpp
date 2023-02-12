/*
*	DP로 풀어야 했던 문제
*	분할정복 처럼 start, end, mid를 나누어가면서 각 구간에서의 최소값을 dp에 저장한다.
* 
*	1. 시간초과를 방지하기 위해 꼭 메모이제이션을 사용해야 한다.
*	2. 구간합을 구하는 방법을 잘 생각해야 한다.
*	3. dp[start][start]가 구간합에 포함되기 때문에 dp[start][start] = 0으로 설정해야 한다.
* 
*	시간을 더 줄인다면...?
*/

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int arr[501];
int dp[501][501];
int acc[501];

void filldp(int start, int end)
{
	if(dp[start][end] != INT_MAX) //메모이제이션!!
		return;

	if (start == end) 
		dp[start][start] = 0; //구간합 더할때 포함됨

	else if(end-start == 1)
		dp[start][end] = arr[start] + arr[end];

	else
	{
		for (int i = start; i < end; i++)
		{
			filldp(start, i);
			filldp(i + 1, end);
			dp[start][end] = min(dp[start][end], dp[start][i] + dp[i + 1][end] + acc[end] - acc[start - 1]);
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int T;
	cin >> T;

	for (int t = 0; t < T; t++)
	{
		int K;
		cin >> K;

		for (int i = 1; i <= K; i++)
		{
			cin >> arr[i];
			acc[i] = acc[i - 1] + arr[i]; //구간합 구하는 센스있는 방법
		}

		for (int i = 1; i <= K; i++)
		{
			for (int j = 1; j <= K; j++)
				dp[i][j] = INT_MAX;
		}

		filldp(1, K);

		cout << dp[1][K] << '\n';
	}
}