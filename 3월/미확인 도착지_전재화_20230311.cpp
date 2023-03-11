/*
*	처음에는 dij를 한번 돌린후에 각 목적지 후보들의 경로를 추척하면서 g,h를 거쳐가는지 확인하려고 했다.
*	하지만 코드를 작성하기 전에 예상했던 것처럼, 특정 교차로로 가는 경로가 두가지 이상일 때, 답이 나오지 않는 경우가 생긴다.
*	만약 이러한 방법으로 풀기 위해서는 path배열을 vector로 선언하고 특정 교차로로 오는 최단 경로가 여러개일 경우 모두 저장해야 한다 => 역추적하는 과정에서 시간초과가 발생할 것 같다. 
* 
*	이렇게 하기보다는 
*	's에서 g로' + 'g에서 h' + 'h에서 목적지 후보' == 's에서 목적지 후보' 혹은
*	's에서 h로' + 'h에서 g' + 'g에서 목적지 후보' == 's에서 목적지 후보'
*
*	라면 해당 목적지 후보가 답이 되는 방법을 사용하였다(질문 게시판 참고)
*	따라서 s가 시작, g가 시작, h가 시작으로 하는 dij를 각각 돌린 후 정답을 구하였다.
*/
#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

int weight[2001][2001];
int dest[100];
vector<int> ans;
int n, m, t;
int s, g, h;

int dist_s[2001];
int dist_g[2001];
int dist_h[2001];

struct DATA
{
	int node, dist;
	bool operator<(const DATA& data) const
	{
		return dist > data.dist;
	}
};

void init(void)
{
	ans.clear();
	for (int i = 1; i <= n; i++)
	{
		dist_s[i] = INT_MAX;
		dist_g[i] = INT_MAX;
		dist_h[i] = INT_MAX;
		for (int j = 1; j <= n; j++)
		{
			weight[i][j] = INT_MAX;
		}
	}
}

void dij(int s, int dist[])
{
	priority_queue<DATA> pq;
	pq.push({ s,0 });
	dist[s] = 0;

	while (!pq.empty())
	{
		DATA now = pq.top();
		pq.pop();

		if(now.dist > dist[now.node])
			continue;

		int ndist;
		for (int next = 1; next <= n; next++)
		{
			if (weight[now.node][next] != INT_MAX && (ndist = now.dist + weight[now.node][next]) < dist[next])
			{
				pq.push({ next, ndist });
				dist[next] = ndist;
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int TC;
	cin >> TC;
	for (int T = 0; T < TC; T++)
	{
		cin >> n >> m >> t;
		cin >> s >> g >> h;
		init();

		int a, b, d;
		for (int i = 0; i < m; i++)
		{	
			cin >> a >> b >> d;
			weight[a][b] = d;
			weight[b][a] = d;
		}

		int x;
		for (int i = 0; i < t; i++)
		{
			cin >> x;
			dest[i] = x;
		}

		dij(s, dist_s);
		dij(g, dist_g);
		dij(h, dist_h);

		for (int i = 0; i < t; i++)
		{
			if(dist_s[dest[i]] == dist_s[g] + weight[g][h] + dist_h[dest[i]] || 
				dist_s[dest[i]] == dist_s[h] + weight[h][g] + dist_g[dest[i]])
				ans.push_back(dest[i]);
		}

		sort(ans.begin(), ans.end());

		size_t len = ans.size();
		for (int i = 0; i < len; i++)
			cout << ans[i] << ' ';
		cout << '\n';
	}
}