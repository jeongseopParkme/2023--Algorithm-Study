/*
*	다익스트라 + dp를 이용한 풀이
*	비슷하게 발상을 했으나, 데이터 구조를 어떻게 설정해야할지 몰라 답지를 참고했음
* 
*	시간 단축할 때 사용했던 기법에 대해서 토의해보는게 좋을 듯 함 (https://conkjh032.tistory.com/356)
*/
#include <iostream>
#include <queue>
#include <climits>
#include <vector>
using namespace std;

struct EDGE
{
	int to, cost, time;
};

struct DATA
{
	int node, cost, time;
	bool operator<(const DATA& a) const
	{
		return time > a.time;
	}
};

int T, N, M, K, ans;
int dp[101][10001];
vector<EDGE> edge[101];

void init(void)
{
	for (int i = 1; i <= N; i++)
	{
		edge[i].clear();
		for (int j = 0; j <= M; j++)
			dp[i][j] = INT_MAX;
	}
}

void input(void)
{
	int u, v, c, d;
	for (int i = 0; i < K; i++)
	{
		cin >> u >> v >> c >> d;
		edge[u].push_back({ v,c,d });
	}
}

void dij(void)
{
	priority_queue<DATA> pq;
	pq.push({ 1,0,0 });
	dp[1][0] = 0;

	int nnode, ntime, ncost;
	while (!pq.empty())
	{
		DATA now = pq.top();
		pq.pop();

		if (dp[now.node][now.cost] < now.time)
			continue;

		for (int i = 0; i < edge[now.node].size(); i++)
		{
			nnode = edge[now.node][i].to;
			ncost = now.cost + edge[now.node][i].cost;
			ntime = now.time + edge[now.node][i].time;
						
			if (ncost <= M && ntime < dp[nnode][ncost]) //ncost <= M 유의! --> out of bound 예방
			{
				pq.push({ nnode, ncost, ntime });
				for (int j = ncost; j <= M; j++)
				{
					if (dp[nnode][j] < ntime) //시간 단축법 --> break시에 시간이 많이 줄어드는 정확한 이유는 모르겠음
						break;
					dp[nnode][j] = ntime;
				}
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> T;
	for (int tc = 0; tc < T; tc++)
	{
		cin >> N >> M >> K;
		init();
		input();
		dij();
		
		ans = INT_MAX;
		for (int i = 0; i <= M; i++)
			ans = min(ans, dp[N][i]);

		if (ans == INT_MAX)
			cout << "Poor KCM" << '\n';
		else
			cout << ans << '\n';
	}
}