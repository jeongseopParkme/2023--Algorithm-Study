/*
*	DP�� Ǯ��� �ߴ� ����
*	�������� ó�� start, end, mid�� ������鼭 �� ���������� �ּҰ��� dp�� �����Ѵ�.
* 
*	1. �ð��ʰ��� �����ϱ� ���� �� �޸������̼��� ����ؾ� �Ѵ�.
*	2. �������� ���ϴ� ����� �� �����ؾ� �Ѵ�.
*	3. dp[start][start]�� �����տ� ���ԵǱ� ������ dp[start][start] = 0���� �����ؾ� �Ѵ�.
* 
*	�ð��� �� ���δٸ�...?
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
	if(dp[start][end] != INT_MAX) //�޸������̼�!!
		return;

	if (start == end) 
		dp[start][start] = 0; //������ ���Ҷ� ���Ե�

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
			acc[i] = acc[i - 1] + arr[i]; //������ ���ϴ� �����ִ� ���
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