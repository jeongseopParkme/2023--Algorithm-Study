/*
*	풀이 : 벨만포드 알고리즘
*	=> 모든 간선에 대해서 간선완화를 n-1번 진행한다. 이때 for문을 n번 돌리고, n번째에서도 간선완화가 생기면 음수 사이클이 생긴것이다.
* 
*	만약 1번과 2번 노드사이에 음수간선이 양방향으로 있다면, 간선완화를 진행할 때마다 dist가 작아지기 때문에 최대 N * M * -10,000 = -3*10^10의 underflow가 발생할 수 있다
*	=> 따라서 cost관련 변수들은 long long을 이용해야 한다.
*/
#include <iostream>
#include <climits>
using namespace std;

typedef long long ll;

struct DATA
{
	int from, to;
	ll cost;
};

int N, M;

bool BellmanFord(long long dist[], DATA edges[])
{
	dist[1] = 0;

	int from, to;
	ll cost, ncost;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			from = edges[j].from;
			to = edges[j].to;
			cost = edges[j].cost;
			if (dist[from] != LLONG_MAX && (ncost = dist[from] + cost) < dist[to])
			{
				dist[to] = ncost;
				if (i == N - 1)
					return true;
			}
		}
	}

	return false;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> M;
	ll* dist = new ll[N + 1];
	DATA* edges = new DATA[M];

	for (int i = 1; i < N + 1; i++)
		dist[i] = LLONG_MAX;

	for (int i = 0; i < M; i++)
		cin >> edges[i].from >> edges[i].to >> edges[i].cost;

	bool isNegativeCycle = BellmanFord(dist, edges);

	if (isNegativeCycle)
		cout << -1 << '\n';

	else
	{
		for (int i = 2; i <= N; i++)
			cout << (dist[i] == LLONG_MAX ? -1 : dist[i]) << '\n';
	}
}