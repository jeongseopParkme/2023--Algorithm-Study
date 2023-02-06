/*
*	푸는 방법 찾는것도 어려웠고, 배워갈 것도 많았던 문제
*	
*	푸는 방법 :
*		3개의 다익스트라(or 모든 좌표를 도착점으로 하는 BFS)를 돌린다. 이때 바깥 지점에서 만나야 하는 경우도 있으므로
*		padding을 해줘야 한다. 세개의 다익스트라 결과값을 더해서 나온 값은 해당 지점에서 만날때 통과해야하는 문의 개수이다(중복포함)
*		특정 좌표에서 만날 때 중복되는 문이 없는 지점이 생기므로 최소 값이 답이 된다
* 
*	배워갈 것 :
*		1. 우선순위 큐에서 구조체 내의 operator로 간편하게 내림차순(오름차순)으로 선언하는 방법
*		2. 다익스트라 돌릴 때 간단하게 짜는 방법
*		3. 초기화는 항상 유의할 것 => 특히 padding이 필요한 문제의 경우 모든 2차원 배열을 초기화 해주는 것이 맘편하다!!!	
*/

#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

#define EMPTY '.'
#define WALL '*'
#define DOOR '#'
#define PRISONER '$'

#define INF 30000

struct DATA
{
	int w;
	int y,x;

	bool operator<(const DATA& x) const { return w > x.w; } //https://wannabe-gosu.tistory.com/7 -> 참일때 위로 올려준다
};

int TC, h, w;
int ans = INF;
int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0,0,-1,+1 };
char map[102][102];
int weight[102][102];
int DijForA[102][102]; //죄수 A
int DijForB[102][102]; //죄수 B
int DijForS[102][102]; //상근
pair<int, int> A, B;

inline bool isrange(int y, int x) { return y >= 0 && y <= h + 1 && x >= 0 && x <= w + 1; }

/* for debug */
void printDij(int arr[][102])
{
	for (int i = 0; i <= h + 1; i++)
	{
		for (int j = 0; j <= w + 1; j++)
		{
			cout << arr[i][j] << '\t';
		}
		cout << '\n';
	}
	cout << '\n';
}

void DijWorker(int arr[][102], int sy, int sx)
{
	priority_queue<DATA> pq;
	pq.push({ 0,sy,sx });
	arr[sy][sx] = 0;

	int w, y, x;

	while (!pq.empty()) //다익스트라 꿀팁
	{
		w = pq.top().w;
		y = pq.top().y;
		x = pq.top().x;
		pq.pop();

		if (w > arr[y][x]) continue; //다익스트라 꿀팁

		for (int i = 0; i < 4; i++)
		{
			int ny = y + dy[i]; int nx = x + dx[i]; int nw;
			if (isrange(ny, nx) && map[ny][nx] != WALL && (nw = w + weight[ny][nx]) < arr[ny][nx])
			{
				arr[ny][nx] = nw;
				pq.push({ nw,ny,nx });
			}
		}
	}
	
	//printDij(arr);
}

void init(void)
{
	for (int i = 0; i <= h + 1; i++)
	{
		for (int j = 0; j <= w + 1; j++)
		{
			DijForA[i][j] = INF;
			DijForB[i][j] = INF;
			DijForS[i][j] = INF;
			weight[i][j] = 0;
			map[i][j] = EMPTY;
			ans = INF;
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> TC;

	for (int tc = 0; tc < TC; tc++)
	{	
		/* input */
		cin >> h >> w;

		init();
		bool AisSet = false;
		for (int i = 1; i <= h; i++)
		{
			for (int j = 1; j <= w; j++)
			{
				cin >> map[i][j];

				if (map[i][j] == PRISONER)
				{
					if (AisSet == false)
					{
						A = { i,j };
						AisSet = true;
					}
					else					
						B = { i,j };
					
					weight[i][j] = 0;
				}

				else if (map[i][j] == DOOR)
					weight[i][j] = 1;

				else if (map[i][j] == EMPTY)
					weight[i][j] = 0;
				
				else			
					weight[i][j] = INF;							
			}
		}

		/* Dij for prisoner A */	
		DijWorker(DijForA, A.first, A.second);

		/* Dij for prisoner B */
		DijWorker(DijForB, B.first, B.second);

		/* Dij for 상근 */		
		DijWorker(DijForS, 0, 0);

		int temp;
		for (int i = 0; i <= h + 1; i++)
		{
			for (int j = 0; j <= w + 1; j++)
			{
				temp = DijForA[i][j] + DijForB[i][j] + DijForS[i][j];
				if (map[i][j] == DOOR)
					temp -= 2;
				ans = min(temp, ans);
			}
		}

		/* output */
		cout << ans << '\n';
	}
}