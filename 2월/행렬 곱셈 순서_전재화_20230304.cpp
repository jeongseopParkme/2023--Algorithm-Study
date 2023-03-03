/*
*	�ռ� dp�� Ǯ���� "���� ��ġ��"�� ������ ����
*	������ �� index�� ������ �ؾ��Ѵٸ� �� ��ų�� ���� ����� �� ���� �� ����.
*/

#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

int N;
int row[501];
int col[501];
int dp[501][501];

void filldp(int start, int end)
{
	if (dp[start][end] != INT_MAX)
		return;

	else if (start == end)
	{
		dp[start][end] = 0;
		return;
	}

	else if (end - start == 1)
	{
		dp[start][end] = row[start] * col[start] * col[end];
		return;
	}

	else
	{
		for (int mid = start; mid < end; mid++) //mid ������ �� ���� ����!!!
		{
			filldp(start, mid);
			filldp(mid + 1, end);
			dp[start][end] = min(dp[start][end], dp[start][mid] + dp[mid + 1][end] + row[start] * col[mid] * col[end]);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> row[i] >> col[i];
		for (int j = 1; j <= N; j++)
			dp[i][j] = INT_MAX;
	}

	filldp(1, N);

	cout << dp[1][N] << '\n';
}