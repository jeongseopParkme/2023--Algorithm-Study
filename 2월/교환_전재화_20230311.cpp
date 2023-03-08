/*
*	문제를 읽어봤을 때, brute force밖에 방법이 없을 것이라고는 생각했으나, 백트랙킹을 생각하지 못했다.
*	백트랙킹 문제를 안푼지 오래돼서 그런 것 같다...
*	백트랙킹만 생각하면 쉽게 풀 수 있는 문제였다. => visit배열 선언할때, 배열 크기 잘못 선언해서 틀렸었다.
*/
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

struct DATA
{
	char num[10];
	int cnt;
};

int K;
int ans = -1;
queue<DATA> q;
bool visit[11][1000001]; //깊이는 10까지, 숫자는 1,000,000까지 들어가야 하니 +1씩 더 넣어줘야 한다!

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	char temp[10];
	cin >> temp >> K;
	
	DATA data;
	strcpy(data.num, temp);
	data.cnt = 0;
	q.push(data);

	size_t len;
	while (!q.empty())
	{		
		DATA now = q.front();
		q.pop();

		if(now.cnt == K)
			ans = max(ans, stoi(now.num));

		else {
			len = strlen(now.num);
			for (int i = 0; i < len; i++)
			{
				for (int j = i + 1; j < len; j++)
				{
					if (i==0 && now.num[j] == '0')
						continue;
					strcpy(data.num, now.num);
					data.cnt = now.cnt + 1;
					swap(data.num[i], data.num[j]);

					int num = stoi(data.num);
					if (visit[data.cnt][num] == false)
					{
						q.push(data);
						visit[data.cnt][num] = true;
					}
				}
			}
		}
	}

	cout << ans << '\n';
}