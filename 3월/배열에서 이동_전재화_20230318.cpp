/*
*	어려웠던 문제
* 
*	풀이 : 이분탐색 + BFS
*	이분탐색을 통해 가능한 diff의 후보값을 찾고, 해당 후보값을 이용해서 [i, i+diff]의 범위에 해당하는 값으로만
*	시작점에서 끝점까지 이동가능한지 BFS로 확인. 이때 i값은 0~200까지이다.
*	=> map에 적힌 숫자들로 돌리게되면 최대 100*100번 확인해야 해서 시간초과가 뜬다(중복을 제거해서 돌리면 괜찮을 듯하다)
*	
*	가능한 최소값 혹은 최대값은 결정문제인 경우가 많으므로 이분탐색이 해결책이 될 수 있다!
*	이분탐색은 해당 글 참고 : https://www.acmicpc.net/blog/view/109
*/
#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
#include <cstring>
using namespace std;

#define MAX 200

int n;
int map[100][100];
int ans = INT_MAX;
int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0,0,-1,+1 };
int mmin = INT_MAX, mmax = INT_MIN;

struct COOR 
{ 
	int y, x; 
};

bool inline isrange(int y, int x)
{
	return y >= 0 && y < n && x >= 0 && x < n;
}

bool bfs(int start, int end)
{
	if (map[0][0] < start || map[0][0] > end)
		return false;

	bool visit[100][100];
	memset(visit, false, sizeof(visit));

	queue <COOR> q;
	q.push({ 0,0 });
	visit[0][0] = true;

	while (!q.empty())
	{
		COOR now = q.front();
		q.pop();

		if (now.y == n - 1 && now.x == n - 1)
			return true;

		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (isrange(ny, nx) && visit[ny][nx] == false && map[ny][nx] >= start && map[ny][nx] <= end)
			{
				q.push({ ny, nx });
				visit[ny][nx] = true;
			}
		}
	}

	return false;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> map[i][j];
			mmin = min(mmin, map[i][j]);
			mmax = max(mmax, map[i][j]);
		}
	}

	int maxDiff = mmax - mmin;
	int low = -1;
	int high = maxDiff;
	int mid;

	while (low + 1 < high)
	{
		bool possible = false;
		mid = (low + high) / 2;
		
		for (int i = 0; i <= MAX; i++)
			possible = possible || bfs(i, i + mid);

		if (possible)
			high = mid;
		else
			low = mid;
	}

	int ans = high;
	cout << ans << '\n';
}