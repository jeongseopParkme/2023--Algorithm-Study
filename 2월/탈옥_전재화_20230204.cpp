/*
*	Ǫ�� ��� ã�°͵� �������, ����� �͵� ���Ҵ� ����
*	
*	Ǫ�� ��� :
*		3���� ���ͽ�Ʈ��(or ��� ��ǥ�� ���������� �ϴ� BFS)�� ������. �̶� �ٱ� �������� ������ �ϴ� ��쵵 �����Ƿ�
*		padding�� ����� �Ѵ�. ������ ���ͽ�Ʈ�� ������� ���ؼ� ���� ���� �ش� �������� ������ ����ؾ��ϴ� ���� �����̴�(�ߺ�����)
*		Ư�� ��ǥ���� ���� �� �ߺ��Ǵ� ���� ���� ������ ����Ƿ� �ּ� ���� ���� �ȴ�
* 
*	����� �� :
*		1. �켱���� ť���� ����ü ���� operator�� �����ϰ� ��������(��������)���� �����ϴ� ���
*		2. ���ͽ�Ʈ�� ���� �� �����ϰ� ¥�� ���
*		3. �ʱ�ȭ�� �׻� ������ �� => Ư�� padding�� �ʿ��� ������ ��� ��� 2���� �迭�� �ʱ�ȭ ���ִ� ���� �����ϴ�!!!	
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

	bool operator<(const DATA& x) const { return w > x.w; } //https://wannabe-gosu.tistory.com/7 -> ���϶� ���� �÷��ش�
};

int TC, h, w;
int ans = INF;
int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0,0,-1,+1 };
char map[102][102];
int weight[102][102];
int DijForA[102][102]; //�˼� A
int DijForB[102][102]; //�˼� B
int DijForS[102][102]; //���
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

	while (!pq.empty()) //���ͽ�Ʈ�� ����
	{
		w = pq.top().w;
		y = pq.top().y;
		x = pq.top().x;
		pq.pop();

		if (w > arr[y][x]) continue; //���ͽ�Ʈ�� ����

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

		/* Dij for ��� */		
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