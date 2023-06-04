#include <queue>
#include <cstring>
#include <vector>
using namespace std;

 int N;
 int theater[2001][11][11], remnant[2001];
 bool visit[2001][11][11];
 inline bool isrange(int y, int x) { return y >= 1 && y <= 10 && x >= 1 && x <= 10; }
 int dy[4] = { -1,+1,0,0 };
 int dx[4] = { 0,0,-1,+1 };

struct Result {
	int id;
	int num;
};

struct Ret
{
	bool success;
	int num, canceled;
};

struct Coor
{
	int y, x;
	bool operator<(const Coor& coor) const
	{
		return (y * 10 + x) > (coor.y * 10 + coor.x);
	}
};

void init(int N)
{
	::N = N;
	memset(theater, 0, sizeof(theater));
	fill(remnant + 1, remnant + 1 + N, 100);
}

bool countBFS(int id, int y, int x, int K)
{
	queue<Coor> q;
	int count = 0;
	//init
	q.push({ y,x });
	visit[id][y][x] = true;
	//bfs start
	while (!q.empty())
	{
		Coor now = q.front();
		q.pop();
		count++;

		if (count == K)
			return true;

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = now.y + dy[dir];
			int nx = now.x + dx[dir];
			if (isrange(ny, nx) && !visit[id][ny][nx] && !theater[id][ny][nx])
			{
				q.push({ ny,nx });
				visit[id][ny][nx] = true;
			}
		}
	}
	//return
	return false;
}

void reserveBFS(int id, int y, int x, int mID, int K)
{
	priority_queue<Coor> pq;
	int count = 0;
	//init
	pq.push({ y,x });
	visit[id][y][x] = true;
	//bfs start
	while (!pq.empty())
	{
		Coor now = pq.top();
		pq.pop();
		theater[id][now.y][now.x] = mID;
		count++;

		if (count == K)
			return;
		
		for (int dir = 0; dir < 4; dir++)
		{
			int ny = now.y + dy[dir];
			int nx = now.x + dx[dir];
			if (isrange(ny, nx) && !visit[id][ny][nx] && !theater[id][ny][nx])
			{
				pq.push({ ny,nx });
				visit[id][ny][nx] = true;
			}
		}
	}
}

Ret cancelBFS(int id, int y, int x, int mID)
{
	queue<Coor> q;
	int num = 0, canceled = 0;
	//init
	q.push({ y,x });
	visit[id][y][x] = true;
	//bfs start
	while (!q.empty())
	{
		Coor now = q.front();
		q.pop();

		theater[id][now.y][now.x] = 0;
		num += (now.y - 1) * 10 + now.x;
		canceled++;

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = now.y + dy[dir];
			int nx = now.x + dx[dir];
			if (isrange(ny, nx) && !visit[id][ny][nx] && theater[id][ny][nx] == mID)
			{
				q.push({ ny,nx });
				visit[id][ny][nx] = true;	
			}
		}
	}
	//return
	return { 0, num, canceled };
}

Ret reserve(int id, int mID, int K)
{
	memset(visit[id], false, sizeof(visit[id]));
	bool success = false;
	int num = 0;

	if (remnant[id] < K)
		return { false, 0, 0 };

	Coor coor;
	for (int i = 1; i <= 10 && !success; i++)
	{
		for (int j = 1; j <= 10 && !success; j++)
		{
			if (!visit[id][i][j] && !theater[id][i][j] && countBFS(id, i, j, K))
			{
				coor = { i,j };
				success = true;
				num = (i - 1) * 10 + j;
			}
		}
	}

	if (success)
	{
		memset(visit[id], false, sizeof(visit[id]));
		reserveBFS(id, coor.y, coor.x, mID, K);
		remnant[id] -= K;
	}

	return { success, num, 0 };
}

Result reserveSeats(int mID, int K)
{
	Result res = { 0,0 };

	for (int id = 1; id <= N; id++)
	{
		Ret temp = reserve(id, mID, K);
		if (temp.success)
		{
			res.id = id;
			res.num = temp.num;
			break;
		}
	}

	return res;
}

Ret cancel(int id, int mID)
{
	memset(visit[id], false, sizeof(visit[id]));
	bool success = false;
	int num = 0;

	for (int i = 1; i <= 10 && !success; i++)
	{
		for (int j = 1; j <= 10 && !success; j++)
		{
			if (theater[id][i][j] == mID)
			{
				success = true;
				Ret temp = cancelBFS(id, i, j, mID);
				num = temp.num;
				remnant[id] += temp.canceled;
			}
		}
	}

	return { success, num, 0 };
}

Result cancelReservation(int mID)
{
	Result res;
	res.id = 0;
	res.num = 0;

	for (int id = 1; id <= N; id++)
	{
		Ret temp = cancel(id, mID);
		if (temp.success)
		{
			res.id = id;
			res.num = temp.num;
			break;
		}
	}

	return res;
}