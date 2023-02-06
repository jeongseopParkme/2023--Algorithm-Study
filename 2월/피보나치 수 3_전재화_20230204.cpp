/*
*	피사노 주기(https://www.acmicpc.net/problem/9471)
*	+ DP
*/

#include <iostream>
using namespace std;

#define PERIOD 1500000

long long n;
int fibo[PERIOD];

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	fibo[0] = 0;
	fibo[1] = 1;
	for (int i = 2; i < PERIOD; i++)
	{
		fibo[i] = (fibo[i - 1] + fibo[i - 2]) % 1000000;
	}

	cin >> n;
	n = n % PERIOD;
	
	cout << fibo[n] << '\n';
}
