/*
*	DP => ȸ���� �Ǳ� ���ؼ��� �� ���� ���ڰ� ����, �� ������ ���ڿ��� ȸ���̾�� �Ѵٴ� Ư���� �̿��� DP�� ä����.
*	N�� 2000�̾ N^2������ �����ϴ�.
*	DP�������� �������� ���� ������ ������ �� ����.
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
		cout << dp[S][E] << '\n'; //endl�� �ϸ� �ȵ� => endl�� buffer flushing�� �����ϱ� ������ �ξ� ������!!!
	}
}