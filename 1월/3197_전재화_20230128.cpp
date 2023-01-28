/*
*	�ð��� �귶�� �� �ؾ��� ���� ������ �����Ƿ� Q�� NextQ�� ����Ѵ�.
*	�������� ������ NextQ�� Q�� �ű��.
*	BFS�� �ذ�
*	������ : �ʱ⿡ ������ �ִ� ��ġ���� ���� �ִ� ������ ����ؾ� �Ѵ�.
*/

#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;

#define SWAN0 0
#define WATER 1

struct Coor
{
	int y, x;
};

int R, C, Time = 0;
char map[1500][1500];
bool visited[2][1500][1500]; //Q�� �� ��ǥ�� visited�� ��� -> [0]�� for swan [1]�� for water
bool finish = false;
Coor swan0, swan1;
queue<Coor> waterQ;
queue<Coor> waterNextQ;
queue<Coor> swan0Q;
queue<Coor> swan0NextQ;

int dy[4] = { -1,+1,0,0 };
int dx[4] = { 0,0,-1,+1 };

bool inline isequal(Coor X, Coor Y)
{
return (X.y == Y.y) && (X.x == Y.x);
}

bool isrange(Coor now)
{
	return (now.y >= 0 && now.y < R&& now.x >= 0 && now.x < C);
}
/* Q�ű�� */
void moveQ(queue<Coor>& dest, queue<Coor>& src)
{
	while (!src.empty())
	{
		dest.push(src.front());
		src.pop();
	}
}

void moveSwan()
{
	moveQ(swan0Q, swan0NextQ);

	while (!finish && !swan0Q.empty())
	{
		Coor nowCoor = swan0Q.front();
		swan0Q.pop();

		for (int i = 0; i < 4; i++)
		{
			Coor next = { nowCoor.y + dy[i],nowCoor.x + dx[i] };
			if (isrange(next) && visited[SWAN0][next.y][next.x] == false)
			{
				if (map[next.y][next.x] == '.')
				{
					visited[SWAN0][next.y][next.x] = true;
					swan0Q.push(next);
				}
				else if (map[next.y][next.x] == 'X')
				{
					visited[SWAN0][next.y][next.x] = true;
					swan0NextQ.push(next);
				}
				else if (isequal(next, swan1))
				{
					finish = true;
					break;
				}
			}
		}
	}
}

void meltIce()
{
	moveQ(waterQ, waterNextQ);

	while (!finish && !waterQ.empty())
	{
		Coor nowCoor = waterQ.front();
		waterQ.pop();

		for (int i = 0; i < 4; i++)
		{
			Coor next = { nowCoor.y + dy[i],nowCoor.x + dx[i] };
			if (isrange(next) && visited[WATER][next.y][next.x] == false && map[next.y][next.x] == 'X')
			{
				visited[WATER][next.y][next.x] = true;
				map[next.y][next.x] = '.';
				waterNextQ.push(next);
			}
		}
	}
}
/* debugging �� */
void print()
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cout << map[i][j];
		}
		cout << '\n';
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	/* �Է� ó�� */
	cin >> R >> C;
	bool swan0Find = false;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'L')
			{
				if (swan0Find == false)
				{
					swan0 = { i,j };
					swan0Find = true;
					visited[SWAN0][i][j] = true;
					visited[WATER][i][j] = true; //������
					swan0Q.push({ i,j });
					waterQ.push({ i,j }); //������
				}
				else
				{
					swan1 = { i,j };
					visited[WATER][i][j] = true;
					waterQ.push({ i,j });
				}
			}
			else if (map[i][j] == '.')
			{
				waterQ.push({ i,j });
				visited[WATER][i][j] = true;
			}
		}
	}
	/* �۾� ���� */
	while (1)
	{
		moveSwan();

		if (finish)
		{
			cout << Time << '\n';
			break;
		}

		meltIce();

		Time++;
	}
}