/*
*	처음에는 냅색 문제와 유사하다고 생각되어, 메모리가 j값을 나타내는 dp를 사용하였다. 
*	하지만 j의 크기가 최대 10,000,000이 될 수 있기 때문에 메모리초과가 일어났다.
* 
*	비용이 j가 되게하는 dp를 사용하여서 해결했다(최대 j가 10,000).
*	최대로 채울 수 있는 비용이 j일때, i번째 앱에서까지 최대로 비활성화 시킬수 있는 용량을 2차원 dp배열에 채우도록 했다.
*	만약 dp[i][j]의 값이 M값을 넘어가면 해당 j값과 ans값을 비교하여 더 작은 값을 ans에 저장한다.
* 
*	동적할당을 안써도 되지만(아마 쓰는것이 더 느릴 것이다), 연습삼아 해보았다.
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

int N, M, ans = INT_MAX;
int bytes[101];
int cost[101];

#define IDX(i, j) ((i) * (sum + 1) + (j))

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	int sum = 0;
	for (int i = 1; i <= N; i++)
		cin >> bytes[i];

	for (int i = 1; i <= N; i++)
	{
		cin >> cost[i];
		sum += cost[i];
	}

	int *dp = new int[(N + 1) * (sum + 1)];
	memset(dp, 0, sizeof(int) * (N + 1) * (sum + 1)); //동적할당의 경우 sizeof(dp)가 안됨!!!

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= sum; j++)
		{
			if (j >= cost[i])
				dp[IDX(i, j)] = max(dp[IDX(i - 1, j)], dp[IDX(i - 1, j - cost[i])] + bytes[i]);
			else
				dp[IDX(i, j)] = dp[IDX(i - 1, j)];

			if(dp[IDX(i,j)] >= M)
				ans = min(ans, j);
		}
	}

	cout << ans << endl;
}