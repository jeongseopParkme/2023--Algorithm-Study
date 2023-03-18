/*
*	풀이 : 구현 + 시뮬레이션
*	=> 발상하기까지 오래걸렸으나, 구현은 그렇게 오래걸리지 않았음 --> 가스가 흐르는 방향은 중요하지 않음
*	불필요한 블록이 없고, 흐름이 유일하므로 블록이 연결되는 경계선에 마킹을 해주면 마킹된 모양에 따라 사라진 블록을 알아낼 수 있다.
*	마킹을 해주는 함수 mark와 마킹된 것을 보고 검사하는 함수 check를 살펴보면 된다. 
*/
#include <iostream>
using namespace std;

struct DATA
{
	bool up, down, left, right;
};

int R, C;
char map[25][25];
DATA gas[25][25];

void mark(int y, int x)
{
	char block = map[y][x];
	
	if (block == '|')
	{
		gas[y][x].up = true;		gas[y][x].down = true;
		gas[y - 1][x].down = true;	gas[y + 1][x].up = true;
	}
	else if (block == '-')
	{
		gas[y][x].left = true;		gas[y][x].right = true;
		gas[y][x - 1].right = true;	gas[y][x + 1].left = true;
	}
	else if (block == '+')
	{
		gas[y][x].up = true;		gas[y][x].down = true;		gas[y][x].left = true;		gas[y][x].right = true;
		gas[y - 1][x].down = true;	gas[y + 1][x].up = true;	gas[y][x - 1].right = true;	gas[y][x + 1].left = true;
	}
	else if (block == '1')
	{
		gas[y][x].down = true;		gas[y][x].right = true;
		gas[y + 1][x].up = true;	gas[y][x + 1].left = true;
	}
	else if (block == '2')
	{
		gas[y][x].up = true;		gas[y][x].right = true;
		gas[y - 1][x].down = true;	gas[y][x + 1].left = true;
	}
	else if (block == '3')
	{
		gas[y][x].up = true;		gas[y][x].left = true;
		gas[y - 1][x].down = true;	gas[y][x - 1].right = true;
	}
	else if (block == '4')
	{
		gas[y][x].down = true;		gas[y][x].left = true;
		gas[y + 1][x].up = true;	gas[y][x - 1].right = true;
	}
}

bool inline IsFlow(int y, int x)
{
	return gas[y][x].up || gas[y][x].down || gas[y][x].left || gas[y][x].right;
}

void check(int y, int x)
{
	if (map[y][x] != '.' || !IsFlow(y, x))
		return;

	cout << y + 1 << ' ' << x + 1 << ' ';
	if (gas[y][x].up && gas[y][x].down && !gas[y][x].left && !gas[y][x].right)
		cout << '|' << '\n';

	else if (!gas[y][x].up && !gas[y][x].down && gas[y][x].left && gas[y][x].right)
		cout << '-' << '\n';

	else if (gas[y][x].up && gas[y][x].down && gas[y][x].left && gas[y][x].right)
		cout << '+' << '\n';

	else if (!gas[y][x].up && gas[y][x].down && !gas[y][x].left && gas[y][x].right)
		cout << '1' << '\n';

	else if (gas[y][x].up && !gas[y][x].down && !gas[y][x].left && gas[y][x].right)
		cout << '2' << '\n';

	else if (gas[y][x].up && !gas[y][x].down && gas[y][x].left && !gas[y][x].right)
		cout << '3' << '\n';

	else if (!gas[y][x].up && gas[y][x].down && gas[y][x].left && !gas[y][x].right)
		cout << '4' << '\n';
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> R >> C;

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
			cin >> map[i][j];
	}

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
			mark(i, j);
	}

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
			check(i, j);
	}
}