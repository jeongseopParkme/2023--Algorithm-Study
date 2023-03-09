/*
*	������ �о���� ��, brute force�ۿ� ����� ���� ���̶��� ����������, ��Ʈ��ŷ�� �������� ���ߴ�.
*	��Ʈ��ŷ ������ ��Ǭ�� �����ż� �׷� �� ����...
*	��Ʈ��ŷ�� �����ϸ� ���� Ǯ �� �ִ� ��������. => visit�迭 �����Ҷ�, �迭 ũ�� �߸� �����ؼ� Ʋ�Ⱦ���.
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
bool visit[11][1000001]; //���̴� 10����, ���ڴ� 1,000,000���� ���� �ϴ� +1�� �� �־���� �Ѵ�!

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