/*
*	플로이드 와셜 알고리즘
* 
*	dist[i][i]를 구하는 것이 사이클이라고 생각할 수 있다. 
*	이 때 모든 i에 대해서 dist를 구해야 하므로 플로이드 와셜 알고리즘이 적절하다.
*	=> cycle이 생기는(i == j) 경우에 따로 조건을 두어 처리한다. 
*/
#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

typedef long long ll;
int V, E;
ll dist[401][401];
ll ans = INT_MAX;

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> V >> E;

	//initialize
	for (int i = 1; i <= V; i++)
	{
		for (int j = 1; j <= V; j++)
		{
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = INT_MAX;
		}
	}

	//input
	int a, b, c;
	for (int i = 0; i < E; i++)
	{
		cin >> a >> b >> c;
		dist[a][b] = c;
	}

	//floyd warshall
	for (int k = 1; k <= V; k++)
	{
		for (int i = 1; i <= V; i++)
		{
			for (int j = 1; j <= V; j++)
			{
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				if (i == j && i != k) // key code
					ans = min(ans, dist[i][k] + dist[k][j]);
			}
		}
	}

	//output
	if (ans == INT_MAX)
		cout << -1 << '\n';
	else
		cout << ans << '\n';
}