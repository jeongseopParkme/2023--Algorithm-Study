/*
*	ó������ dij�� �ѹ� �����Ŀ� �� ������ �ĺ����� ��θ� ��ô�ϸ鼭 g,h�� ���İ����� Ȯ���Ϸ��� �ߴ�.
*	������ �ڵ带 �ۼ��ϱ� ���� �����ߴ� ��ó��, Ư�� �����η� ���� ��ΰ� �ΰ��� �̻��� ��, ���� ������ �ʴ� ��찡 �����.
*	���� �̷��� ������� Ǯ�� ���ؼ��� path�迭�� vector�� �����ϰ� Ư�� �����η� ���� �ִ� ��ΰ� �������� ��� ��� �����ؾ� �Ѵ� => �������ϴ� �������� �ð��ʰ��� �߻��� �� ����. 
* 
*	�̷��� �ϱ⺸�ٴ� 
*	's���� g��' + 'g���� h' + 'h���� ������ �ĺ�' == 's���� ������ �ĺ�' Ȥ��
*	's���� h��' + 'h���� g' + 'g���� ������ �ĺ�' == 's���� ������ �ĺ�'
*
*	��� �ش� ������ �ĺ��� ���� �Ǵ� ����� ����Ͽ���(���� �Խ��� ����)
*	���� s�� ����, g�� ����, h�� �������� �ϴ� dij�� ���� ���� �� ������ ���Ͽ���.
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