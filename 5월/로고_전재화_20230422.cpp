/*
*	Disjoint Set + 기하
* 
*	Disjoint Set 잘 알아두기! (교재 170p)
*	=> find_set은 recursive하게 root찾기
*	=> Union은 root찾고, rank 낮은 set을 높은 set에 붙히기(같으면 rank++)
* 
*	직사각형이 겹치는지 판단하는 알고리즘은 주석 잘 읽어보기
*/
#include <iostream>
#include <algorithm>
using namespace std;

struct rectangle
{
	int x1, y1, x2, y2;
};

int N;
rectangle rect[1001];
int p[1001];
int Rank[1001];

int find_set(int x)
{
	if (x != p[x])
		p[x] = find_set(p[x]);
	return p[x];
}

void Union(int x, int y)
{
	int rx = find_set(x);
	int ry = find_set(y);

	if (Rank[rx] > Rank[ry])
		p[ry] = rx;
	else
	{
		p[rx] = ry;
		if (Rank[rx] == Rank[ry])
			Rank[ry]++;
	}
}

// 원점과 직사각형의 각 변이 만나는지 확인하는 함수
bool intersectZero(rectangle& r)
{
	if ((r.y1 == 0 || r.y2 == 0) && (r.x1 <= 0 && r.x2 >= 0))
		return true;

	if ((r.x1 == 0 || r.x2 == 0) && (r.y1 <= 0 && r.y2 >= 0))
		return true;

	return false;
}

bool intersect(rectangle& r1, rectangle& r2)
{
	// x axis not overlap
	if (r1.x1 > r2.x2 || r1.x2 < r2.x1)
		return false;

	// y axis not overlap
	if (r1.y1 > r2.y2 || r1.y2 < r2.y1)
		return false;

	// r1 is small and contained
	if ((r1.x1 > r2.x1 && r1.x2 < r2.x2) && (r1.y1 > r2.y1 && r1.y2 < r2.y2))
		return false;

	// r2 is small and contained
	if ((r2.x1 > r1.x1 && r2.x2 < r1.x2) && (r2.y1 > r1.y1 && r2.y2 < r1.y2))
		return false;

	return true;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> rect[i].x1 >> rect[i].y1 >> rect[i].x2 >> rect[i].y2;
		p[i] = i;
	}

	for (int i = 0; i <= N; i++)
	{
		for (int j = i + 1; j <= N; j++)
		{
			if (i == 0 && intersectZero(rect[j]))
				Union(0, j);

			else if (intersect(rect[i], rect[j]))
				Union(i, j);
		}
	}

	int ans = 0;
	for (int i = 0; i <= N; i++)
	{
		if (p[i] == i)
			ans++;
	}

	cout << ans - 1 << endl;
}