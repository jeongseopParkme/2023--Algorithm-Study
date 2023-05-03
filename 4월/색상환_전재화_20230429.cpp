/*
*	DP(��ȭ��)
* 
*	ó������ �ռ� �޸������̼� ����ó�� Ǯ���� ������ �ð��ʰ��� Ǯ�� ���ߴ� (dp[���� ��][�� ��° ����])
*	������ for�� * �Լ� ���� for�� * K = N^2K�� �ż� �ſ� ū ���� �ȴ�.
* 
*	=> �ռ� �޸������̼��� ��Ʈ����ŷ�� ���� dp�� index��ü�� visitüũ�� �� �� �ְ� �Ǿ�, dp�� ä��µ���
*	�ߺ��� ����������, �� ������ �ߺ��� ����Եȴ�(�ѹ� �湮�ߴ� ���� ����ȯ�� ���� �� ���ٸ� �ٽ� �湮�ؾ� ��)
*/
#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int dp[1001][1001]; //dp[i][j] i���� ������ k���� ������ �� �ִ� ����� ��
const int mod = 1000000003;

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	cin >> N >> K;

	for (int i = 0; i <= N; i++)
	{
		dp[i][0] = 1;
		dp[i][1] = i;
	}

	int end;
	for (int i = 2; i <= N; i++)
	{
		end = min(K, i);
		for (int j = 2; j <= end; j++)
		{
			dp[i][j] = (dp[i - 1][j] + dp[i - 2][j - 1]) % mod; //i��° color�� ĥ���� ���� �� + i��° color�� ĥ�� ��
		}
	}

	dp[N][K] = (dp[N - 1][K] + dp[N - 3][K - 1]) % mod;
	
	cout << dp[N][K] << '\n';
}