#include <iostream>
using namespace std;

int N, ans, ansIdx;
int num[1000], dp[1000], path[1000];

void print(int idx)
{
	if (path[idx] == idx)
	{
		cout << num[idx] << ' ';
		return;
	}
	print(path[idx]);
	cout << num[idx] << ' ';
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> num[i];

	for (int i = 0; i < N; i++)
	{
		dp[i] = 1;
		path[i] = i;
		for (int j = 0; j < i; j++)
		{
			if (num[j] < num[i] && dp[i] < dp[j] + 1)
			{
				dp[i] = dp[j] + 1;
				path[i] = j;
			}
		}
		if (ans < dp[i])
		{
			ans = dp[i];
			ansIdx = i;
		}
	}

	cout << ans << '\n';
	print(ansIdx);
}