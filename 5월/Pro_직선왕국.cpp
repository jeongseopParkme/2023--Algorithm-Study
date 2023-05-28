/*
*	priority queue + cmd queuing
* 
*	너무 너무 어려웠던 문제...
*	전반적인 구조를 잡는것도 어려웠고, 디테일한 부분에서도 꽤 디버깅을 해야 했다.
*/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_ORDER 300
#define CMD_CHECK 400

extern void init(int N, int M);
extern void destroy();
extern int order(int tStamp, int mCityA, int mCityB, int mTax);
extern int check(int tStamp);

/*************************************************************/
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

enum Order { Move /*곡물이동*/, MoveE /*곡물이동 Expected*/, City /*관리자가 도시에 도착*/, Cap /*관리자가 수도에 도착*/, Send /*관리자를 파견*/ };

struct Packet
{
	int time, order, dest, capa;
	bool operator<(const Packet& lhs) const
	{
		if (time == lhs.time)
			return order > lhs.order;
		return time > lhs.time;
	}
};

int N, M, ans, Expected[201], Storage[201];
bool visit[201];
priority_queue<Packet> EventQ;

void init(int N, int M)
{
	::N = N;
	::M = M;
	ans = 0;
	for (int i = 1; i <= N; i++)
	{
		Expected[i] = 0;
		Storage[i] = 0;
		visit[i] = false;
	}
}

void destroy()
{
	while (!EventQ.empty())
		EventQ.pop();
}

void ManageAdmin(int time)
{
	if (M)
	{
		int max = 0;
		int city = 0;
		for (int i = 1; i <= N; i++)
		{
			if (!visit[i] && Expected[i] > max)
			{
				max = Expected[i];
				city = i;
			}
		}

		if (max != 0)
		{
			visit[city] = true;
			EventQ.push({ time + city, City, city, 0 });
			--M;
		}
	}
}

void ManageEventQ(int tStamp)
{
	while (!EventQ.empty() && EventQ.top().time <= tStamp)
	{
		Packet now = EventQ.top();
		EventQ.pop();

		if (now.order == Move)
		{
			Storage[now.dest] += now.capa;
		}

		else if (now.order == MoveE)
		{
			Expected[now.dest] += now.capa;
			EventQ.push({ now.time, Send, 0, 0 });
		}

		else if (now.order == City)
		{
			EventQ.push({ now.time + now.dest, Cap, now.dest, Storage[now.dest] });
			Expected[now.dest] -= Storage[now.dest];
			Storage[now.dest] = 0;
		}

		else if (now.order == Cap)
		{
			++M;
			ans += now.capa;
			visit[now.dest] = false;
			EventQ.push({ now.time, Send, 0, 0 });
		}

		else if (now.order == Send)
		{
			ManageAdmin(now.time);
		}
	}
}

void ManageOrder(int tStamp, int mCityA, int mCityB, int mTax)
{
	int time = max(tStamp, tStamp + abs(mCityA - mCityB) - mCityB);
	EventQ.push({ tStamp + abs(mCityA - mCityB), Move, mCityB, mTax });
	EventQ.push({ time, MoveE, mCityB, mTax });
}

int order(int tStamp, int mCityA, int mCityB, int mTax)
{
	ManageOrder(tStamp, mCityA, mCityB, mTax);
	ManageEventQ(tStamp);
	return ans;
}

int check(int tStamp)
{
	ManageEventQ(tStamp);
	return ans;
}

/*************************************************************/

static int run()
{
	int C;
	int isOK = 0;
	int cmd, ret, chk;

	int mN, mM;
	int mTStamp;

	int mCityA, mCityB, mTax;

	scanf("%d", &C);

	for (int c = 0; c < C; ++c)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d %d ", &mN, &mM);
			init(mN, mM);
			isOK = 1;
			break;

		case CMD_ORDER:
			scanf("%d %d %d %d", &mTStamp, &mCityA, &mCityB, &mTax);
			ret = order(mTStamp, mCityA, mCityB, mTax);
			scanf("%d", &chk);
			if (ret != chk)
				isOK = 0;
			break;

		case CMD_CHECK:
			scanf("%d", &mTStamp);
			ret = check(mTStamp);
			scanf("%d", &chk);
			if (ret != chk)
				isOK = 0;
			break;

		default:
			isOK = 0;
			break;
		}
	}
	destroy();
	return isOK;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		if (run()) printf("#%d %d\n", tc, MARK);
		else printf("#%d %d\n", tc, 0);
	}
	return 0;
}