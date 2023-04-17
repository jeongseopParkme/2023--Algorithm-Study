/*
*	풀이 : 메모이제이션 + dfs
*	
*	구조자체는 '외판원 순회'문제와 동일하지만, 세부구현에 있어서 수학적 지식이 필요했다.
*	=> https://degurii.tistory.com/201
*	=> https://velog.io/@gidskql6671/%EB%82%98%EB%A8%B8%EC%A7%80Modulo-%EC%97%B0%EC%82%B0-%EB%B6%84%EB%B0%B0%EB%B2%95%EC%B9%99
*	
*	A*B mod C = (A mod C) * (B mod C)와 동일한 성질은 유용할 듯 하다.
*	너무 어려웠다...
*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

typedef long long ll;
#define NaN -1

int N, K;
ll memo[1 << 16][100];
int rem[15];
int len[15];
int ten_rem[51];
string num[15];
ll cnt, all = 1, g;

ll dfs(int visit, int now_rem)
{
	if (visit == (1 << N) - 1)
		return now_rem % K == 0;

	if (memo[visit][now_rem] != NaN)
		return memo[visit][now_rem];

	memo[visit][now_rem] = 0;
	for (int i = 0; i < N; i++)
	{
		if (visit & (1 << i))
			continue;
		int next_rem = (now_rem * ten_rem[len[i]] + rem[i]) % K;
		memo[visit][now_rem] += dfs(visit | (1 << i), next_rem);
	}

	return memo[visit][now_rem];
}

ll gcd(ll a, ll b)
{
	if (b == 0) return a;
	return gcd(b, a % b);
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	memset(memo, NaN, sizeof(memo));

	cin >> N;
	for (ll i = 0; i < N; i++)
	{
		cin >> num[i];

		all *= (i + 1);
	}

	cin >> K;
	
	int ten_mod = 10 % K;
	ten_rem[0] = 1 % K;
	for (int i = 1; i < 51; i++)
	{
		ten_rem[i] = (ten_rem[i - 1] * ten_mod) % K;
	}

	for (int i = 0; i < N; i++)
	{
		len[i] = num[i].size();
		for (int j = 0; j < len[i]; j++)
		{
			rem[i] = (rem[i] * ten_mod + (num[i][j] - '0')) % K;
		}
	}

	cnt = dfs(0, 0);
	g = gcd(all, cnt);
	cout << cnt / g << '/' << all / g << '\n';
}