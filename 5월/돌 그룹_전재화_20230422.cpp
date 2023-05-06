/*
*	넓이 우선 탐색 + 수학적 직관
* 
*	3개 숫자의 합이 항상 일정하다는 것을 파악하지 못해, 답지를 보게됐다 ㅠㅠ
* 
*	풀이방법은 두가지가 있는데, 
*	1. 중복을 허용하는 경우와 (https://comyoung.tistory.com/245) -> 20ms
*	2. 중복을 허용하지 않는 경우이다. -> 4ms
* 
*	아래 코드는 중복을 허용하지 않는 경우로 작성했는데, q와 visit배열에 두 개의 값을 넣을 때, 
*	항상 {min, mid, max} 중 [min][mid]로 indexing을 해 순서가 바뀌어도 다른 것으로 취급하지 못하게 했다.
*	이렇게 정렬을 해서 들어가면, for문을 순열대신 조합으로 돌려도 된다는 장점도 있다(이미 순서가 정해져 있으므로).
*	단, 자잘한 계산의 overhead가 있다.
*/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

queue<pair<int, int>> q;
int sum, Min, Max, Mid;
bool visit[1501][1501];


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	int a, b, c;
	cin >> a >> b >> c;
	sum = a + b + c;

	if (sum % 3 != 0)
	{
		cout << 0 << '\n';
		exit(0);
	}

	Min = min({ a,b,c });
	Max = max({ a,b,c });
	q.push({ Min, (Mid = sum - Min - Max) });
	visit[Min][Mid] = true;

	while (!q.empty())
	{
		pair<int, int> now = q.front();
		q.pop();

		if (now.first == sum / 3 && now.second == sum / 3)
		{
			cout << 1 << '\n';
			exit(0);
		}

		int temp[3] = { now.first, now.second, sum - now.first - now.second };
		for (int i = 0; i < 3; i++)
		{
			for (int j = i + 1; j < 3; j++)
			{
				if (temp[i] != temp[j])
				{
					int num0 = temp[i] * 2;
					int num1 = temp[j] - temp[i];
					Min = min({ num0, num1, sum - num0 - num1 });
					Max = max({ num0, num1, sum - num0 - num1 });
					if (visit[Min][(Mid = sum - Min - Max)] == false)
					{
						q.push({ Min, Mid });
						visit[Min][Mid] = true;
					}
				}
			}
		}
	}

	cout << 0 << '\n';
}