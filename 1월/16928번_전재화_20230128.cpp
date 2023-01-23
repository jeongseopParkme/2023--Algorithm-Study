/*
*	BFS 사용
*	Brute Force + 최소 or 최대 => BFS
*/

#include <cstdio>
#include <queue>
using namespace std;

#define START 1
#define END 100
#define INVALID 0

struct Data
{
	int pos, num;
};

int N, M;
int ladder[101], snake[101];
bool visited[101];
int ans;
queue<Data> q;

int main(void)
{
	/* 입력값 처리 */
	scanf("%d %d", &N, &M);
	
	for (int i = 0; i < N; i++)
	{
		int start, end;
		scanf("%d %d", &start, &end);
		ladder[start] = end;
	}

	for (int i = 0; i < M; i++)
	{
		int start, end;
		scanf("%d %d", &start, &end);
		snake[start] = end;
	}
	/* BFS */
	q.push({ START,0 });
	visited[START] = true;
	while (!q.empty())
	{
		int nowPos = q.front().pos;
		int nowNum = q.front().num;
		q.pop();

		if (nowPos == END)
		{
			ans = nowNum;
			break;
		}

		for (int dice = 1; dice <= 6; dice++)
		{
			int next = nowPos + dice;
			/* 사다리 or 뱀을 탈경우 */
			if (ladder[next] != INVALID)
				next = ladder[next];
			else if (snake[next] != INVALID)
				next = snake[next];
			/* next <= 100을 통해 visted[next]에 seg fault를 막아줘야 함 */
			if (next <= 100 && visited[next] == false)
			{
				q.push({ next, nowNum + 1 });
				visited[next] = true;
			}
		}
	}

	printf("%d\n", ans);
}