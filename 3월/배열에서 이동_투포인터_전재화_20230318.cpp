/*
*	https://mona04.github.io/posts/algorithm/boj-gold/BOJ-1981)-%EB%B0%B0%EC%97%B4%EC%97%90%EC%84%9C-%EC%9D%B4%EB%8F%99/
*	투포인터를 사용해서 푸는 방법 => 범위를 구할때 유용할 듯
*	이진탐색보다 빠름 O(N^2 x M)
*/
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int n;
int board[101 * 101], min_v = 1e9, max_v = -1;
bool visitTB[101 * 101];

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
bool Valid(int x, int y) { return x >= 0 && y >= 0 && x < n && y < n; }

bool BFS(int l, int r)
{
	fill(visitTB, visitTB + n * n, 0);
	queue<int> q;
	if (board[0] > r || board[0] < l) return false;
	q.push(0);
	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		for (int i = 0; i < 4; i++)
		{
			int x = cur % n + dx[i], y = cur / n + dy[i];
			int d = y * n + x;
			if (Valid(x, y) && board[d] <= r && board[d] >= l && !visitTB[d])
			{
				visitTB[d] = true;
				q.push(d);
			}
		}
	}
	return visitTB[n * n - 1];
}

int main()
{
	cin >> n;
	for (int i = 0; i < n * n; i++)
	{
		cin >> board[i];
		min_v = min(min_v, board[i]);
		max_v = max(max_v, board[i]);
	}

	int ans = 1e9;
	int begin = min_v, end = min_v;
	while (begin <= end && end <= max_v)
	{
		bool r = BFS(begin, end);
		if (r) {
			ans = min(ans, end - begin);
			begin++;
		}
		else end++;
	}
	cout << ans;
}