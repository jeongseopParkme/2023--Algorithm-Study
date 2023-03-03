/*
*	ó������ ���� ������ �����ϴٰ� �����Ǿ�, �޸𸮰� j���� ��Ÿ���� dp�� ����Ͽ���. 
*	������ j�� ũ�Ⱑ �ִ� 10,000,000�� �� �� �ֱ� ������ �޸��ʰ��� �Ͼ��.
* 
*	����� j�� �ǰ��ϴ� dp�� ����Ͽ��� �ذ��ߴ�(�ִ� j�� 10,000).
*	�ִ�� ä�� �� �ִ� ����� j�϶�, i��° �ۿ������� �ִ�� ��Ȱ��ȭ ��ų�� �ִ� �뷮�� 2���� dp�迭�� ä�쵵�� �ߴ�.
*	���� dp[i][j]�� ���� M���� �Ѿ�� �ش� j���� ans���� ���Ͽ� �� ���� ���� ans�� �����Ѵ�.
* 
*	�����Ҵ��� �Ƚᵵ ������(�Ƹ� ���°��� �� ���� ���̴�), ������� �غ��Ҵ�.
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
	memset(dp, 0, sizeof(int) * (N + 1) * (sum + 1)); //�����Ҵ��� ��� sizeof(dp)�� �ȵ�!!!

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