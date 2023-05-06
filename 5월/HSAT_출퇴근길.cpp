/*
*	BFS
* 
*	1Ʈ : �ܼ��� S->T�� T->S�� BFS�� ���� �� �� �ִ� ���� üũ�� �� ��ġ�� �κ��� ã�� => ��ٱ� or ��ٱ濡 ������ ���� ��尡 ���õ� �� ����
*	2Ʈ : Rmap�� ���� ��ٱ� or ��ٱ濡�� ���ϴ� ��带 ������ => '��ٱ� ��ο� S�� ���� �� �����ص� �ǰ�' ���� ���� ����
*	3Ʈ : bool reverse�� �־ reverseŽ�� �ÿ��� end node���� ��� Ž���� �� �ְ� ��
*	+4Ʈ : ��ٱ濡�� Rmap�� �˻�������, ��ٱ濡���� �˻��� �ʿ���� => 'S���� T�� ���� ��ο� T���� S�� ���� ��ΰ� �ϳ� �̻� �������� ����ȴ�' ���� ������ 
*	3Ʈ�� ���ǰ� �����Ͽ� �ѹ��� ���� ��ٱ� Rmap�� �����ϴ�
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