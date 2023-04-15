/*
*	플로이드 워셜 알고리즘 --> 경유지 k가 outer loop에 위치해야 한다는 사실 꼭 기억!
*/

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

typedef long long ll;

int n, m;
ll dist[101][101];

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i == j) dist[i][j] = 0;
			else dist[i][j] = INT_MAX;
		}
	}

	int from, to;
	ll cost;
	for (int i = 0; i < m; i++)
	{
		cin >> from >> to >> cost;
		dist[from][to] = min(dist[from][to], cost);
	}

	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (dist[i][j] == INT_MAX)
				cout << 0 << ' ';
			else
				cout << dist[i][j] << ' ';
		}
		cout << '\n';
	}
}