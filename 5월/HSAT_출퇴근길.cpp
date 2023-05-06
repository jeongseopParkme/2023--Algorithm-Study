/*
*	BFS
* 
*	1트 : 단순히 S->T로 T->S로 BFS를 통해 갈 수 있는 곳을 체크한 후 겹치는 부분을 찾음 => 출근길 or 퇴근길에 속하지 않은 노드가 선택될 수 있음
*	2트 : Rmap을 만들어서 출근길 or 퇴근길에만 속하는 노드를 선택함 => '출근길 경로에 S는 여러 번 등장해도 되고' 조건 만족 못함
*	3트 : bool reverse를 넣어서 reverse탐색 시에는 end node에서 계속 탐색할 수 있게 함
*	+4트 : 출근길에서 Rmap을 검사했으면, 퇴근길에서는 검사할 필요없음 => 'S에서 T로 가는 경로와 T에서 S로 가는 경로가 하나 이상 존재함이 보장된다' 조건 때문에 
*	3트의 조건과 결합하여 한바퀴 돌면 퇴근길 Rmap가 동일하다
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, S, T, ans;
vector<int> map[100001];
vector<int> Rmap[100001];
bool visitST[100001];
bool visitRST[100001];
bool visitTS[100001];
bool visitRTS[100001];

void fillVisit(int start, int end, vector<int> map[], bool visit[], bool reverse)
{
	queue<int> q;
	q.push(start);
	visit[start] = true;

	while (!q.empty())
	{
		int now = q.front();
		q.pop();

		if (now == end && !reverse)
			continue;

		for (auto& it : map[now])
		{
			if (!visit[it])
			{
				q.push(it);
				visit[it] = true;
			}
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n >> m;
	int x, y;
	for (int i = 0; i < m; i++)
	{
		cin >> x >> y;
		map[x].push_back(y);
		Rmap[y].push_back(x);
	}
	cin >> S >> T;

	// S->T
	fillVisit(S, T, map, visitST, false);
	fillVisit(T, S, Rmap, visitRST, true);
	
	// T->S
	fillVisit(T, S, map, visitTS, false);
	fillVisit(S, T, Rmap, visitRTS, true);

	for (int i = 1; i <= n; i++)
	{
		if (i != S && i != T && visitST[i] && visitRST[i] && visitTS[i] && visitRTS[i])
			ans++;
	}

	cout << ans << '\n';
}